import sys
sys.path.insert(0, '../')
from planet_wars import issue_order
import logging


# Helper method to return whether the target planet is mine
def _is_my_planet(state, planet_ID):
    return state.planets[planet_ID] == 1


# Helper method to return whether I have a fleet in flight to the target planet
def _fleet_in_flight(state, planet_ID):
    for my_fleet in state.my_fleets():
        if planet_ID == my_fleet.destination_planet:
            return True
    return False


# Helper method to return whether the planet is my planet and I don't have a fleet in flight to it
def _my_planet_no_fleet(state, planet_ID):
    return _is_my_planet(state, planet_ID) and not _fleet_in_flight(state, planet_ID)

# Helper method to return a list of enemy fleets attacking a specific planet
def planet_under_attack_by(state, planet_ID):
    attacking_list = []
    for enemy_fleet in state.enemy_fleets():
        if planet_ID == enemy_fleet.destination_planet:
            attacking_list.append(enemy_fleet)
    return attacking_list

def _planet_units_after_turns(state, planet_ID, turns):
    return state.planets[planet_ID].growth_rate * turns + state.planets[planet_ID].num_ships


def attack_weakest_enemy_planet(state):
    # (1) If we currently have a fleet in flight, abort plan.
    if len(state.my_fleets()) >= 1:
        return False

    # print(state.my_fleets())

    # (2) Find my strongest planet.
    strongest_planet = max(state.my_planets(), key=lambda t: t.num_ships, default=None)

    # (3) Find the weakest enemy planet.
    weakest_planet = min(state.enemy_planets(), key=lambda t: t.num_ships, default=None)

    if not strongest_planet or not weakest_planet:
        # No legal source or destination
        return False
    else:
        # (4) Send an appropriate amount of ships from my strongest planet to the weakest enemy planet.
        if strongest_planet.num_ships > weakest_planet.num_ships:
            return issue_order(state, strongest_planet.ID, weakest_planet.ID, 1 + weakest_planet.num_ships + (weakest_planet.growth_rate * state.distance(strongest_planet.ID, weakest_planet.ID)))


def reinforce_planet(state):
    # Value to be returned
    return_value = False
    # (1) Add any attacking a planet with more ships it into the attacking_me queue with prio num_ships
    # List of attacked on an allied planet
    attack_list = []
    for enemy_fleet in state.enemy_fleets():
        if _my_planet_no_fleet(state, enemy_fleet.destination_planet) and enemy_fleet.num_ships > state.planets[enemy_fleet.destination_planet].num_ships + (enemy_fleet.turns_remaining * state.planets[enemy_fleet.destination_planet].growth_rate):
            if attack_list:
                for index, attacking in attack_list:
                    if enemy_fleet.num_ships > attacking.num_ships:
                        attack_list.insert(index, enemy_fleet)
                        break
            else:
                attack_list.append(enemy_fleet)
    # (2) Find a defensible [We have more ships and are closer] planet and defend it
    while attack_list:
        curr_attack = attack_list.pop(0)
        under_attack_id = curr_attack.destination_planet
        if not _fleet_in_flight(state, under_attack_id):
            # For each of our planets
            for ally_planet in state.my_planets():
                if ally_planet.ID != under_attack_id:
                    # Get a list of all fleets are attacking it
                    attacking_list = planet_under_attack_by(state, ally_planet.ID)
                    # Amount of ships attacking a planet
                    attack_size = 0
                    if attacking_list:
                        for attack in attacking_list:
                            # Figure out how many total ships are attacking it
                            attack_size += attack.num_ships
                    # Check if curr_attack can be fended off by sending reinforcements from ally_planet
                    required_ships = curr_attack.num_ships - _planet_units_after_turns(state, under_attack_id, curr_attack.turns_remaining)
                if ally_planet.num_ships - attack_size >=  required_ships and state.distance(ally_planet.ID, under_attack_id) < curr_attack.turns_remaining:
            # if strongest_planet.num_ships > attacking_me.num_ships and state.distance(strongest_planet.ID, attacking_me.destination_planet) < attacking_me.total_trip_length:
                    issue_order(state, ally_planet.ID, under_attack_id, required_ships)
                    return_value = True
                    break
    return return_value


def spread(state):
    my_planets = iter(sorted(state.my_planets(), key=lambda p: p.num_ships))

    neutral_planets = [planet for planet in state.neutral_planets()
                       if not any(fleet.destination_planet == planet.ID for fleet in state.my_fleets())]
    neutral_planets.sort(key=lambda p: p.num_ships)

    target_planets = iter(neutral_planets)

    try:
        my_planet = next(my_planets)
        target_planet = next(target_planets)
        while True:
            required_ships = 0
            attacking_list = planet_under_attack_by(state, target_planet.ID)
            if attacking_list:
                for attack in attacking_list:
                    dist_diff = state.distance(my_planet.ID, target_planet.ID) - attack.turns_remaining
                    if dist_diff > 0:
                        required_ships = dist_diff * state.planets[target_planet.ID].growth_rate
                    if dist_diff == 0:
                        required_ships = target_planet.num_ships + 2
            if required_ships == 0:
                required_ships = target_planet.num_ships + 1

            if my_planet.num_ships > required_ships:
                issue_order(state, my_planet.ID, target_planet.ID, required_ships)
                my_planet = next(my_planets)
                target_planet = next(target_planets)
            else:
                my_planet = next(my_planets)

    except StopIteration:
        return


def attack(state):
    my_planets = iter(sorted(state.my_planets(), key=lambda p: p.num_ships))

    enemy_planets = [planet for planet in state.enemy_planets()
                      if not any(fleet.destination_planet == planet.ID for fleet in state.my_fleets())]
    enemy_planets.sort(key=lambda p: p.num_ships)

    target_planets = iter(enemy_planets)

    try:
        my_planet = next(my_planets)
        target_planet = next(target_planets)
        while True:
            required_ships = target_planet.num_ships + \
                                 state.distance(my_planet.ID, target_planet.ID) * target_planet.growth_rate + 1

            if my_planet.num_ships > required_ships:
                issue_order(state, my_planet.ID, target_planet.ID, required_ships)
                my_planet = next(my_planets)
                target_planet = next(target_planets)
            else:
                my_planet = next(my_planets)

    except StopIteration:
        return


# def spread_to_weakest_neutral_planet(state):
#     # (1) If we currently have a fleet in flight, just do nothing.
#     if len(state.my_fleets()) >= 1:
#         return False

#     # (2) Find my strongest planet.
#     strongest_planet = max(state.my_planets(), key=lambda p: p.num_ships, default=None)

#     # (3) Find the weakest neutral planet.
#     weakest_planet = min(state.neutral_planets(), key=lambda p: p.num_ships, default=None)

#     if not strongest_planet or not weakest_planet:
#         # No legal source or destination
#         return False
#     else:
#         # (4) Send half the ships from my strongest planet to the weakest enemy planet.
#         return issue_order(state, strongest_planet.ID, weakest_planet.ID, strongest_planet.num_ships / 2)



# def defend(state):
#     my_planets = [planet for planet in state.my_planets()]
#     if not my_planets:
#         return

#     def strength(p):
#         return p.num_ships \
#                + sum(fleet.num_ships for fleet in state.my_fleets() if fleet.destination_planet == p.ID) \
#                - sum(fleet.num_ships for fleet in state.enemy_fleets() if fleet.destination_planet == p.ID)

#     avg = sum(strength(planet) for planet in my_planets) / len(my_planets)

#     weak_planets = [planet for planet in my_planets if strength(planet) < avg]
#     strong_planets = [planet for planet in my_planets if strength(planet) > avg]

#     if (not weak_planets) or (not strong_planets):
#         return

#     weak_planets = iter(sorted(weak_planets, key=strength))
#     strong_planets = iter(sorted(strong_planets, key=strength, reverse=True))

#     try:
#         weak_planet = next(weak_planets)
#         strong_planet = next(strong_planets)
#         while True:
#             need = int(avg - strength(weak_planet))
#             have = int(strength(strong_planet) - avg)

#             if have >= need > 0:
#                 issue_order(state, strong_planet.ID, weak_planet.ID, need)
#                 weak_planet = next(weak_planets)
#             elif have > 0:
#                 issue_order(state, strong_planet.ID, weak_planet.ID, have)
#                 strong_planet = next(strong_planets)
#             else:
#                 strong_planet = next(strong_planets)

#     except StopIteration:
#         return