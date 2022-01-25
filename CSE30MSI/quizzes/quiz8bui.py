# Simple pygame program

# Import and initialize the pygame library
import pygame
import random
pygame.init()

# Set up the drawing window
screen = pygame.display.set_mode([500, 500])

# Run until the user asks to quit
running = True


class Dot:
  def position(self, x = 250, y = 250):
    self.positions(x,y)
  def color(self, r = 0, g = 0 , b = 255):
    self.colors = (r, g, b)
  def size(self, z = 75):
    self.size = z

a = Dot()

x = random.randint(0,499)
y = random.randint(0,499)
r = random.randint(0,255)
g = random.randint(0,255)
b = random.randint(0,255)
z = random.randint(2,75)

while running:

    # Did the user click the window close button?
    for event in pygame.event.get():
      if event.type == pygame.QUIT:
        running = False

      # default color
    screen.fill((255, 255, 255))

      # Draw a solid blue circle in the center
      # pygame.draw.circle(screen, (red, green, blue), (positionx, positiony), size)
    pygame.draw.circle(screen, a.colors, a.positions, a.size)
      
      # Flip the display
    pygame.display.flip()

  # Done! Time to quit.
pygame.quit()