

def if_neutral_planet_available(state):
  strongest_planet = max(state.my_planets(), key=lambda t: t.num_ships, default=None)
  for elem in state.neutral_planets():
    if strongest_planet.num_ships > elem.num_ships:
      return True
  return False


def have_largest_fleet(state):
  return sum(planet.num_ships for planet in state.my_planets()) \
            + sum(fleet.num_ships for fleet in state.my_fleets()) \
          > sum(planet.num_ships for planet in state.enemy_planets()) \
            + sum(fleet.num_ships for fleet in state.enemy_fleets())


def if_counter_fleet_possible(state):
  return_val = False
  if state.enemy_fleets():
    for enemy_fleet in state.enemy_fleets():
      for my_planet in state.my_planets():
        if state.planets[enemy_fleet.destination_planet] == my_planet:
          pass
        if state.planets[enemy_fleet.destination_planet].num_ships * enemy_fleet.turns_remaining + my_planet.num_ships > enemy_fleet.num_ships and state.distance(enemy_fleet.destination_planet, my_planet.ID):
          return_val = True
          break
  return return_val


def if_enemy_planet_available(state):
  for my_planet in state.my_planets():
    for enemy_planet in state.enemy_planets():
      if my_planet.num_ships > enemy_planet.growth_rate * state.distance(my_planet.ID, enemy_planet.ID) + enemy_planet.num_ships:
        return True
  return False

def if_still_playing(state):
  return bool(state.my_planets() and state.enemy_planets())
