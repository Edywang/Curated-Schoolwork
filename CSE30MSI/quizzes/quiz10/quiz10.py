# Simple pygame program

# Import and initialize the pygame library
import pygame
import numpy
from random import randint
BLACK = (0, 0, 0)


class Dot(pygame.sprite.Sprite):
    # Setters for each of the values

    def __init__(self, color, width, height, screen = None):
        super().__init__()
        # Pass in the color of the car, and its x and y position, width and height.
        # Set the background color and set it to be transparent
        if screen == None:
          self.image = pygame.Surface([width, height])
        else:
          self.image = screen
        self.image.fill(BLACK)
        self.image.set_colorkey(BLACK)

        pygame.draw.rect(self.image, color, [10, 10, width, height])

        self.velocity = [randint(4, 8), randint(-8, 8)]

        # Fetch the rectangle object that has the dimensions of the image.
        self.rect = self.image.get_rect()

    def move(self): # "diagonal" move 1 step closer to goal
        sx = numpy.sign(self.goal[0]-self.gps[0])  # returns -1,0,1
        nx = self.gps[0] + sx
        sy = numpy.sign(self.goal[1]-self.gps[1])
        ny = self.gps[1] + sy
        self.gps = (nx,ny)

    def moveManhattan( self ):
        # write code to move from start_pos to end_pos in hor/ver
        sx = numpy.sign(self.goal[0]-self.gps[0])  # returns -1,0,1
        if sx:
            self.gps = (self.gps[0] + sx, self.gps[1])
        else:
            sy = numpy.sign(self.goal[1]-self.gps[1])
            self.gps = (self.gps[0], self.gps[1] + sy) 

    def moveLine( self ):
        # write code to move in straight line
        dx = self.goal[0]-self.start[0]
        #sx = numpy.sign(dx)  # returns -1,0,1
        nx = round(self.gps[0] + 0.1*dx)
        
        dy = self.goal[1]-self.start[1]
        #sy = numpy.sign(dy)
        ny = round(self.gps[1] + 0.1*dy)
        self.gps = (int(nx), int(ny))

    def update(self):
        self.rect.x += self.velocity[0]
        self.rect.y += self.velocity[1]

    def bounce(self):
        self.velocity[0] = -self.velocity[0]
        self.velocity[1] = randint(-8, 8)


