import pygame
import random
# import numpy
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

class Dot(pygame.sprite.Sprite): # Inherits from pygame's Sprite class
    # Class attributes
    total_dots = 0
    total_healthy = 0
    total_infected = 0
    total_sick = 0
    total_dead = 0
    total_rec = 0

    def __init__(self, start=(0,0), end=(0,0), color=(0,0,255), size=5):        
        super().__init__()
    
        self.start = start  # Permanent start position
        # self.gps   = start  # position along the line
        self.goal  = end    # Temporary goal position
        self.end   = end    # Permanent end position
        self.color = color
        self.size  = size
        
        self.moving = True
        self.sd6 = False
        self.sip = False
        self.state = None
        
        # Creating the sprite; This will be a circular dot drawn onto a transparent
        # rectangular hitbox. The circle is drawn onto the center of the rectangle.
        # For now, the size of the rectangular hitbox is set to 20x20
        self.image = pygame.Surface([20, 20]) # Creates the sprite surface hitbox (rectangle)
        self.image.fill(WHITE) # Makes it transparent (same color as background)
        self.image.set_colorkey(WHITE)
        
        # Draws a circle onto the rectangle surface of the sprite
        pygame.draw.circle(self.image, self.color, [10,10], self.size)
        
        self.rect = self.image.get_rect() # rect contains the actual rectangle
        self.rect.x = start[0] # X position of rect
        self.rect.y = start[1] # Y position of rect
        
        Dot.total_dots += 1
        
    """
    def move(self):        
        # For moving the dot back and forth
        # Check if the current x and y coordinate of the dot is within +/-50 of the end position
        # This means that the dot is near/at its ending position so we'll need to send it to start again
        if self.end[0] - 50 <= self.rect.x <= self.end[0] + 50 and self.end[1] - 50 <= self.rect.y <= self.end[1] + 50:
            self.goal = self.start
        # Check if the current x and y coordinate of the dot is within +/-50 of the start position 
        # This means that the dot is near/at its starting position so we'll need to send it to end again
        elif self.start[0] - 50 <= self.rect.x <= self.start[0] + 50 and self.start[1] - 50 <= self.rect.y <= self.start[1] + 50:
            self.goal = self.end
            
        # Moves the dot in a straight line
        if self.moving:
          dx = self.goal[0]-self.rect.x
          nx = round(self.rect.x + 0.02*dx)
          dy = self.goal[1]-self.rect.y
          ny = round(self.rect.y + 0.02*dy)
          self.rect.x = int(nx)
          self.rect.y = int(ny)
    """

    def move(self):
        # write code to move in straight line
        dx = self.goal[0]-self.start[0]
        #sx = numpy.sign(dx)  # returns -1,0,1
        nx = round(self.gps[0] + 0.1*dx)
        
        dy = self.goal[1]-self.start[1]
        #sy = numpy.sign(dy)
        ny = round(self.gps[1] + 0.1*dy)
        self.gps = (int(nx), int(ny))
