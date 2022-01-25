# Simple pygame program

# Import and initialize the pygame library
import pygame
import random

# Creating the class Dot
class Dot:
    def __init__(self, positionx = 250, positiony = 250, colorr = 0, colorg = 0, colorb = 255, size = 75):
        self.position = (positionx, positiony)
        self.color = (colorr, colorg, colorb)
        self.size = size


pygame.init()

# Set up the drawing window
screen = pygame.display.set_mode([500, 500])

# Run until the user asks to quit
running = True
while running:

    # Did the user click the window close button?
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Fill the background with white
    screen.fill((255, 255, 255))

    # pygame.draw.circle(screen, (red, green, blue), (positionx, positiony), size)
    # Draw a random circle
    myDot = Dot(random.randint(0, 500), random.randint(0, 500), random.randint(0, 255), random.randint(0, 255), random.randint(0, 255), random.randint(2, 75))
    pygame.draw.circle(screen, myDot.color, myDot.position, Dot.size)

    # Flip the display
    pygame.display.flip()

# Done! Time to quit.
pygame.quit()