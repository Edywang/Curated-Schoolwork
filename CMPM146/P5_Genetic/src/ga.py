import copy
import heapq
import metrics
import multiprocessing.pool as mpool
import os
import random
import shutil
import time
import math

# python ga.py
# ./test.bat

width = 200
height = 16

options = [
    "-",  # an empty space
    "X",  # a solid wall
    "?",  # a question mark block with a coin
    "M",  # a question mark block with a mushroom
    "B",  # a breakable block
    "o",  # a coin
    # "|",  # a pipe segment
    "T",  # a pipe top
    "E",  # an enemy
    # "f",  # a flag, do not generate
    # "v",  # a flagpole, do not generate
    # "m"  # mario's start position, do not generate
]


# option_dict = {
#     "empty_space": "-",
#     "solid_wall": "X",
#     "question_mark_block_with_coin": "?",
#     "question_mark_block_with_mushroom": "M",
#     "breakable_block": "B",
#     "coin": "o",
#     "pipe": "|",
#     "pipe_top": "T",
#     "enemy": "E",
#     "flag": "f",
#     "flagpole": "v",
#     "mario": "m"
# }


def _make_logical_genome(genome):
    g = genome
    for y in range(height - 1):
        for x in range(width - 1):
            # If a block is in a spot and it's not a pipe, clear the two blocks above it
            if y >= 2 and g[y][x] != "-" and g[y][x] != "|":
                g[y - 2][x] = "-"
                g[y - 1][x] = "-"
            # Put pipes below pipe tops
            if g[y][x] == "T":
                for y1 in range(y+1, height):
                    g[y1][x] = "|"
            # # Check for walls below pipes then remove them
            # if g[y][x] == "|" and g[y + 1][x] != "|":
            #     g[y+1][x] = "|"
            # Check if any enemies are not on solid ground and remove them
            if g[y][x] == "E" and not (
                    g[y + 1][x] == "X" or g[y + 1] == "?" or g[y + 1] == "M" or g[y + 1] == "B" or g[y + 1] == "T"):
                g[y][x] = "-"
            # Make sure nothing except enemies or empty space is on top of a pipe top
            if g[y][x] == "T" and g[y - 1][x] != "-" and g[y - 1][x] != "E":
                g[y-1][x] = "-"
            # If a pipe is not under a pipe or a pipe top, replace it with a pipe top
            if g[y][x] == "|" and g[y - 1][x] != "T" and g[y - 1][x] != "|":
                g[y-1][x] = "T"
            # Check for breakable blocks on the height above the floor
            if y == height - 2 and x != 0 and (
                    g[y][x] == "B" or g[y][x] == "M" or g[y][x] == "?" or g[y][x] == "X"):
                if random.random() < 0.05 and g[y + 1][x] == "X" and g[y][x - 1] == "-":
                    g[y][x] = "E"
                elif random.random() < 0.9:
                    g[y][x] = "-"
                else:
                    g[y][x] = "X"
    # Remove anything in the floor that isn't empty space, a wall, or a pipe
    y = height - 1
    for x in range(width):
        if g[y][x] != "-" and g[y][x] != "X" and g[y][x] != "|" and g[y][x] != "T":
            g[y][x] = "-"
        if g[y][x] == "|" and g[y - 1][x] != "T" and g[y - 1][x] != "|":
            g[y-1][x] = "T"
    g[height - 2][width - 1] = "X"
    g[7][-1] = "v"
    for col in range(8, 14):
        g[col][-1] = "f"
    return g


# The level as a grid of tiles


class Individual_Grid(object):
    __slots__ = ["genome", "_fitness"]

    def __init__(self, genome):
        self.genome = copy.deepcopy(genome)
        self._fitness = None

    # Update this individual's estimate of its fitness.
    # This can be expensive so we do it once and then cache the result.
    def calculate_fitness(self):
        measurements = metrics.metrics(self.to_level())
        # Print out the possible measurements or look at the implementation of metrics.py for other keys:
        # print(measurements.keys())
        # Default fitness function: Just some arbitrary combination of a few criteria.  Is it good?  Who knows?
        # DONE: Modify this, and possibly add more metrics.  You can replace this with whatever code you like.
        coefficients = dict(
            meaningfulJumpVariance=0.5,
            negativeSpace=0.1,
            pathPercentage=1.0,
            emptyPercentage=0.4,
            linearity=-0.1,
            leniency=.01,
            solvability=10,
            decorationPercentage=.1,
        )
        self._fitness = sum(map(lambda m: coefficients[m] * measurements[m],
                                coefficients))
        return self

    # Return the cached fitness value or calculate it as needed.
    def fitness(self):
        if self._fitness is None:
            self.calculate_fitness()
        return self._fitness

    # Mutate a genome into a new genome.  Note that this is a _genome_, not an individual!
    def mutate(self, genome):
        # DONE: consider weighting the different tile types so it's not uniformly random
        # consider putting more constraints on this to prevent pipes in the air, etc

        left = 1
        right = width - 1
        for y in range(height):
            for x in range(left, right):
                # Mutate a single tile to another random one with a chance
                if genome[y][x] != "v" and genome[y][x] != "f" and random.random() < 0.05:
                    # Mutate the tile with constraints
                    # Set a selector to a random float
                    # selector = random.random()
                    # # Weighted selection using selector of options
                    # if selector < 0.01:
                    #     genome[y][x] = "X"
                    # elif selector < 0.06:
                    #     genome[y][x] = "-"
                    # elif selector < 0.07:
                    #     genome[y][x] = "?"
                    # elif selector < 0.08:
                    #     genome[y][x] = "M"
                    # elif selector < 0.09:
                    #     genome[y][x] = "B"
                    # elif selector < 0.1:
                    #     genome[y][x] = "o"
                    # # elif selector < 0.8:
                    # #     genome[y][x] = "T"
                    # elif selector < 0.07:
                    #     genome[y][x] = "E"
                    # else:
                    #     genome[y][x] = "|"
                    genome[y][x] = random.choice(options)
                    while height - y >= 4 and (genome[y][x] == "|" or genome[y][x] == "T"):
                        genome[y][x] = random.choice(options)
                    if genome[y][x] == "|" or genome[y][x] == "T":
                        genome[y][x] = random.choice(options)
        genome = _make_logical_genome(genome)
        return genome

    # Create zero or more children from self and other
    def generate_children(self, other):
        new_genome = copy.deepcopy(self.genome)
        # Leaving first and last columns alone...
        # do crossover with other
        left = 1
        right = width - 1
        crossover_pt = random.randint(left, right)
        for y in range(height):
            if random.random() < 0.5:
                for x in range(crossover_pt, right):
                    # DONE: Which one should you take?  Self, or other?  Why?
                    # consider putting more constraints on this to prevent pipes in the air, etc
                    # Grab the tile from the other genome
                    new_genome[y][x] = other.genome[y][x]
                    # if random.random() < 0.5:
                    #     new_genome[y][x] = other.genome[y][x]
            else:
                for x in range(left, crossover_pt):
                    new_genome[y][x] = other.genome[y][x]
        # do mutation; note we're returning a one-element tuple here
        new_genome = _make_logical_genome(self.mutate(new_genome))
        return (Individual_Grid(new_genome),)

    # Turn the genome into a level string (easy for this genome)
    def to_level(self):
        return self.genome

    # These both start with every floor tile filled with Xs
    # Can change these
    @classmethod
    def empty_individual(cls):
        g = [["-" for col in range(width)] for row in range(height)]
        g[15][:] = ["X"] * width
        g[14][0] = "m"
        g[7][-1] = "v"
        for col in range(8, 14):
            g[col][-1] = "f"
        for col in range(14, 16):
            g[col][-1] = "X"
        return cls(g)

    # "empty_space": "-",
    # "solid_wall": "X",
    # "question_mark_block_with_coin": "?",
    # "question_mark_block_with_mushroom": "M",
    # "breakable_block": "B",
    # "coin": "o",
    # "pipe": "|",
    # "pipe_top": "T",
    # "enemy": "E",
    # "flag": "f",
    # "flagpole": "v",
    # "mario": "m"

    @classmethod
    def random_individual(cls):
        # TODO: consider putting more constraints on this to prevent pipes in the air, etc
        # also consider weighting the different tile types so it's not uniformly random
        g = [random.choices(options, k=width) for row in range(height)]
        # Logical checks
        g = _make_logical_genome(g)
        # For array slicing, the second index is exclusive where the first is inclusive
        # Fill the floor in
        g[15][:] = ["X"] * width
        # Mario always starts in the first column
        g[14][0] = "m"
        # Flag always at the end
        g[7][-1] = "v"
        g[8:14][-1] = ["f"] * 6
        # In the bottom right, put an extra block below the flag
        g[14:16][-1] = ["X", "X"]
        return cls(g)


def offset_by_upto(val, variance, min=None, max=None):
    val += random.normalvariate(0, variance ** 0.5)
    if min is not None and val < min:
        val = min
    if max is not None and val > max:
        val = max
    return int(val)


def clip(lo, val, hi):
    if val < lo:
        return lo
    if val > hi:
        return hi
    return val


# Inspired by https://www.researchgate.net/profile/Philippe_Pasquier/publication/220867545_Towards_a_Generic_Framework_for_Automated_Video_Game_Level_Creation/links/0912f510ac2bed57d1000000.pdf


class Individual_DE(object):
    # Calculating the level isn't cheap either so we cache it too.
    __slots__ = ["genome", "_fitness", "_level"]

    # Genome is a heapq of design elements sorted by X, then type, then other parameters
    def __init__(self, genome):
        self.genome = list(genome)
        heapq.heapify(self.genome)
        self._fitness = None
        self._level = None

    # Calculate and cache fitness
    def calculate_fitness(self):
        measurements = metrics.metrics(self.to_level())
        # Default fitness function: Just some arbitrary combination of a few criteria.  Is it good?  Who knows?
        # TODO: Add more metrics?
        # TODO: Improve this with any code you like
        coefficients = dict(
            meaningfulJumpVariance=0.5,
            negativeSpace=0.6,
            pathPercentage=0.5,
            emptyPercentage=0.6,
            linearity=-0.1,
            solvability=2.0
        )
        penalties = 0
        # TODO: For example, too many stairs are unaesthetic.  Let's penalize that
        if len(list(filter(lambda de: de[1] == "6_stairs", self.genome))) > 5:
            penalties -= 2
        # TODO: If you go for the FI-2POP extra credit, you can put constraint calculation in here too and cache it in a new entry in __slots__.
        self._fitness = sum(map(lambda m: coefficients[m] * measurements[m],
                                coefficients)) + penalties
        return self

    def fitness(self):
        if self._fitness is None:
            self.calculate_fitness()
        return self._fitness

    def mutate(self, new_genome):
        # DONE: How does this work?  Explain it in your writeup.
        # consider putting more constraints on this, to prevent generating weird things
        if random.random() < 0.1 and len(new_genome) > 0:
            to_change = random.randint(0, len(new_genome) - 1)
            de = new_genome[to_change]
            new_de = de
            x = de[0]
            de_type = de[1]
            choice = random.random()
            if de_type == "4_block":
                y = de[2]
                breakable = de[3]
                if choice < 0.33:
                    x = offset_by_upto(x, width / 8, min=1, max=width - 2)
                elif choice < 0.66:
                    y = offset_by_upto(y, height / 2, min=0, max=height - 1)
                else:
                    breakable = not breakable
                new_de = (x, de_type, y, breakable)
            elif de_type == "5_qblock":
                y = de[2]
                has_powerup = de[3]  # boolean
                if choice < 0.33:
                    x = offset_by_upto(x, width / 8, min=1, max=width - 2)
                elif choice < 0.66:
                    y = offset_by_upto(y, height / 2, min=0, max=height - 1)
                else:
                    has_powerup = not has_powerup
                new_de = (x, de_type, y, has_powerup)
            elif de_type == "3_coin":
                y = de[2]
                if choice < 0.5:
                    x = offset_by_upto(x, width / 8, min=1, max=width - 2)
                else:
                    y = offset_by_upto(y, height / 2, min=0, max=height - 1)
                new_de = (x, de_type, y)
            elif de_type == "7_pipe":
                h = de[2]
                if choice < 0.5:
                    x = offset_by_upto(x, width / 8, min=1, max=width - 2)
                else:
                    h = offset_by_upto(h, 2, min=2, max=height - 4)
                new_de = (x, de_type, h)
            elif de_type == "0_hole":
                w = de[2]
                if choice < 0.5:
                    x = offset_by_upto(x, width / 8, min=1, max=width - 2)
                else:
                    w = offset_by_upto(w, 4, min=1, max=width - 2)
                new_de = (x, de_type, w)
            elif de_type == "6_stairs":
                h = de[2]
                dx = de[3]  # -1 or 1
                if choice < 0.33:
                    x = offset_by_upto(x, width / 8, min=1, max=width - 2)
                elif choice < 0.66:
                    h = offset_by_upto(h, 8, min=1, max=height - 4)
                else:
                    dx = -dx
                new_de = (x, de_type, h, dx)
            elif de_type == "1_platform":
                w = de[2]
                y = de[3]
                madeof = de[4]  # from "?", "X", "B"
                if choice < 0.25:
                    x = offset_by_upto(x, width / 8, min=1, max=width - 2)
                elif choice < 0.5:
                    w = offset_by_upto(w, 8, min=1, max=width - 2)
                elif choice < 0.75:
                    y = offset_by_upto(y, height, min=0, max=height - 1)
                else:
                    madeof = random.choice(["?", "X", "B"])
                new_de = (x, de_type, w, y, madeof)
            elif de_type == "2_enemy":
                pass
            new_genome.pop(to_change)
            heapq.heappush(new_genome, new_de)
        return new_genome

    def generate_children(self, other):
        # DONE: How does this work?  Explain it in your writeup.
        pa = random.randint(0, len(self.genome))
        pb = random.randint(0, len(other.genome))
        a_part = self.genome[:pa] if len(self.genome) > 0 else []
        b_part = other.genome[pb:] if len(other.genome) > 0 else []
        ga = a_part + b_part
        b_part = other.genome[:pb] if len(other.genome) > 0 else []
        a_part = self.genome[pa:] if len(self.genome) > 0 else []
        gb = b_part + a_part
        # do mutation
        return Individual_DE(self.mutate(ga)), Individual_DE(self.mutate(gb))

    # Apply the DEs to a base level.
    def to_level(self):
        if self._level is None:
            base = Individual_Grid.empty_individual().to_level()
            for de in sorted(self.genome, key=lambda de: (de[1], de[0], de)):
                # de: x, type, ...
                x = de[0]
                de_type = de[1]
                if de_type == "4_block":
                    y = de[2]
                    breakable = de[3]
                    base[y][x] = "B" if breakable else "X"
                elif de_type == "5_qblock":
                    y = de[2]
                    has_powerup = de[3]  # boolean
                    base[y][x] = "M" if has_powerup else "?"
                elif de_type == "3_coin":
                    y = de[2]
                    base[y][x] = "o"
                elif de_type == "7_pipe":
                    h = de[2]
                    base[height - h - 1][x] = "T"
                    for y in range(height - h, height):
                        base[y][x] = "|"
                elif de_type == "0_hole":
                    w = de[2]
                    for x2 in range(w):
                        base[height - 1][clip(1, x + x2, width - 2)] = "-"
                elif de_type == "6_stairs":
                    h = de[2]
                    dx = de[3]  # -1 or 1
                    for x2 in range(1, h + 1):
                        for y in range(x2 if dx == 1 else h - x2):
                            base[clip(0, height - y - 1, height - 1)][clip(1, x + x2, width - 2)] = "X"
                elif de_type == "1_platform":
                    w = de[2]
                    h = de[3]
                    madeof = de[4]  # from "?", "X", "B"
                    for x2 in range(w):
                        base[clip(0, height - h - 1, height - 1)][clip(1, x + x2, width - 2)] = madeof
                elif de_type == "2_enemy":
                    base[height - 2][x] = "E"
            self._level = base
        return self._level

    @classmethod
    def empty_individual(_cls):
        # TODO: Maybe enhance this
        g = []
        return Individual_DE(g)

    @classmethod
    def random_individual(_cls):
        # TODO: Maybe enhance this
        elt_count = random.randint(8, 128)
        g = [random.choice([
            (random.randint(1, width - 2), "0_hole", random.randint(1, 8)),
            (random.randint(1, width - 2), "1_platform", random.randint(1, 8), random.randint(0, height - 1),
             random.choice(["?", "X", "B"])),
            (random.randint(1, width - 2), "2_enemy"),
            (random.randint(1, width - 2), "3_coin", random.randint(0, height - 1)),
            (random.randint(1, width - 2), "4_block", random.randint(0, height - 1), random.choice([True, False])),
            (random.randint(1, width - 2), "5_qblock", random.randint(0, height - 1), random.choice([True, False])),
            (random.randint(1, width - 2), "6_stairs", random.randint(1, height - 4), random.choice([-1, 1])),
            (random.randint(1, width - 2), "7_pipe", random.randint(2, height - 4))
        ]) for i in range(elt_count)]
        return Individual_DE(g)


Individual = Individual_Grid


# Individual = Individual_DE


def generate_successors(population):
    results = []
    # DONE: DESIGN AND IMPLEMENT THIS
    # Hint: Call generate_children() on some individuals and fill up results.

    # Tournament Selection

    tournament_size = 50
    tournament_num = len(population) - 1
    for _ in range(tournament_num):
        # First tournament to grab first parent
        tournament_competitors = []
        for _ in range(tournament_size):
            tournament_competitors.append(random.choice(population))
        tournament_winner1 = max(tournament_competitors, key=lambda individual: individual.fitness())
        # Second tournament to grab second parent
        tournament_competitors = []
        for _ in range(tournament_size):
            tournament_competitors.append(random.choice(population))
        tournament_winner2 = max(tournament_competitors, key=lambda individual: individual.fitness())

        generated_children_tup1 = tournament_winner1.generate_children(tournament_winner2)
        for child1 in generated_children_tup1:
            results.append(child1)

    # Roulette Selection

    # maximum = max([indiv.fitness() for indiv in population])
    # minimum = min([indiv.fitness() for indiv in population])
    # for parent1 in population:
    #     fitness_req = random.uniform(minimum, maximum)
    #     for parent2 in population:
    #         if parent2.fitness() > fitness_req:
    #             generated_children_tup2 = parent1.generate_children(parent2)
    #             for child2 in generated_children_tup2:
    #                 results.append(child2)
    #             break

    # print(type(child))
    return results


def ga():
    # TODO: Feel free to play with this parameter
    pop_limit = 300  # Changed to 300 from 480 because that's the limit of VSCode debugger
    # Code to parallelize some computations
    batches = os.cpu_count()
    if pop_limit % batches != 0:
        print("It's ideal if pop_limit divides evenly into " + str(batches) + " batches.")
    batch_size = int(math.ceil(pop_limit / batches))
    with mpool.Pool(processes=os.cpu_count()) as pool:
        init_time = time.time()
        # TODO: (Optional) change population initialization
        population = [Individual.random_individual() if random.random() < 0.9
                      else Individual.empty_individual()
                      for _g in range(pop_limit)]
        # But leave this line alone; we have to reassign to population because we get a new population that has more cached stuff in it.
        population = pool.map(Individual.calculate_fitness,
                              population,
                              batch_size)
        init_done = time.time()
        print("Created and calculated initial population statistics in:", init_done - init_time, "seconds")
        generation = 0
        start = time.time()
        now = start
        print("Use ctrl-c to terminate this loop manually.")
        try:
            while True:
                now = time.time()
                best = None
                # Print out statistics
                if generation > 0:
                    best = max(population, key=Individual.fitness)
                    print("Generation:", str(generation))
                    print("Max fitness:", str(best.fitness()))
                    print("Average generation time:", (now - start) / generation)
                    print("Net time:", now - start)
                    with open("levels/last.txt", 'w') as f:
                        for row in best.to_level():
                            f.write("".join(row) + "---\n")
                generation += 1
                # DONE: Determine stopping condition
                if best and best.fitness() >= 12:
                    break
                elif generation >= 15:
                    break

                # TODO: Also consider using FI-2POP as in the Sorenson & Pasquier paper
                gentime = time.time()
                next_population = generate_successors(population)
                gendone = time.time()
                print("Generated successors in:", gendone - gentime, "seconds")
                # Calculate fitness in batches in parallel
                next_population = pool.map(Individual.calculate_fitness,
                                           next_population,
                                           batch_size)
                popdone = time.time()
                print("Calculated fitnesses in:", popdone - gendone, "seconds")
                population = next_population
        except KeyboardInterrupt:
            pass
    return population


if __name__ == "__main__":
    final_gen = sorted(ga(), key=Individual.fitness, reverse=True)
    best = final_gen[0]
    print("Best fitness: " + str(best.fitness()))
    now = time.strftime("%m_%d_%H_%M_%S")
    # TODO: You can change this if you want to blast out the whole generation, or ten random samples, or...
    for k in range(0, 10):
        with open("levels/" + now + "_" + str(k) + ".txt", 'w') as f:
            for row in final_gen[k].to_level():
                f.write("".join(row) + "---\n")
                # print("".join(row) + "---\n")
            f.close()
