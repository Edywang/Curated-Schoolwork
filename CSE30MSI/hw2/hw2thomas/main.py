import dot
import pygame
import random
import itertools

pygame.init()
screen = pygame.display.set_mode([500, 500]) # 500x500 pixel screen
timer  = pygame.time.Clock() # Controls how fast screen updates

# Generates 100 dot objects with random start/end points(range 0-500)
dead_dots = []

start = []
end = []
#random.seed(103)
all_sprites_list = pygame.sprite.Group()
for i in range(20): 
    pt_start = (random.randint(0,500), random.randint(0,500))
    pt_end = (random.randint(0,500), random.randint(0,500))
    
    new_dot = dot.Dot(pt_start, pt_end)
    all_sprites_list.add(new_dot)    

# Main program loop
running = True # Run until the user asks to quit
while running:

    # Did the user click the window close button?
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Fill the background with white
    screen.fill((255, 255, 255))
    
    all_sprites_list.draw(screen)
    # Move each dot on the list
    for i in all_sprites_list: # Moves each sprite
        i.move()
        i.moving = True
            # If a collision is detected, we'll need to call avoid
        for d1, d2 in itertools.combinations(all_sprites_list, 2):
          if pygame.sprite.collide_mask(d1,d2):
            #rand = random.randint(0,1)
            #if rand == 0:
            d1.moving = False
            #else:
            #  d2.moving = False

        # Find sprites in a group that intersect another sprite.
        # Returns a list of sprits that collided with current sprite 'i'

    # Flip the display; Updates screen
    pygame.display.flip() # Every time flip is called is 1 frame
    timer.tick(20) # 20 frames per second

# Done! Time to quit.
pygame.quit()