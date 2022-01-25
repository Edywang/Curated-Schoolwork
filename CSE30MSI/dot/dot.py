import numpy

class Dot:
  count = 0 # Number of dots in population

  def move(self): # "Diagonal" move 1 step closer to goal
    sx = numpy.sign(self.goal[0]-self.gps[0]) # Returns -1, 0, or 1
    nx = self.gps[0] + sx
    sy = numpy.sign(self.goal[1]-self.gps[1]) # Returns -1, 0, or 1
    nx = self.gps[1] + sy
    self.gps = (nx, ny)

  def __init__(self, start=(0, 0), end=(0, 0), color=(0, 0, 255)):
    # TODO: Initialize our dot with the parameters and a size