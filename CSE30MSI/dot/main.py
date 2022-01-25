# Simple pygame program to move a dot from point A to point B

# Import and initialize the pygame library
import pygame
import dot

# Set up drawing window
pygame.init()
screen = pygame.display.set_mode([500, 500])
timer = pygame.time.Clock()

# TODO: Create as many dot objects as wanted

# Run until the user quits
running = True
while running:
  # Did the user click the window close button?
  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      running = False
  
  # Fill the background with white
  screen.fill((255, 255, 255))

  # TODO: Move each dot in the list

  # Flip the display
  pygame.display.flip()
  timer.tick(120)