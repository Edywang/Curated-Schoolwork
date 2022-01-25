# Simple pygame program to move a dot from point A to point B

# sound clip: beep-07.wav is from
# https://www.soundjay.com/beep-sounds-1.html


# Import and initialize the pygame library
import pygame
import quiz10

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0,0,255)
# Set up the drawing window
pygame.init()
screen = pygame.display.set_mode([500, 500])
timer  = pygame.time.Clock()
effect = pygame.mixer.Sound('beep-07.wav')  # set up the sound cliip

# create a dot object


ball = quiz10.Dot(WHITE, 10, 10)
ball.rect.x = 0
ball.rect.y = 0
ball2= quiz10.Dot(BLUE, 10 ,10)
ball2.rect.x = 400
ball2.rect.y = 500


all_sprites_list = pygame.sprite.Group()


all_sprites_list.add(ball)
all_sprites_list.add(ball2)
# Fill the background with white


#Run until the user asks to quit
running = True
while running:

    # Did the user click the window close button?
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    all_sprites_list.update()



    if ball.rect.x >= 500:
        ball.velocity[0] = -ball.velocity[0]
    if ball.rect.x <= 0:
        ball.velocity[0] = -ball.velocity[0]
    if ball.rect.y > 500:
        ball.velocity[1] = -ball.velocity[1]
    if ball.rect.y < 0:
        ball.velocity[1] = -ball.velocity[1]

    if ball2.rect.x >= 500:
        ball2.velocity[0] = -ball2.velocity[0]
    if ball2.rect.x <= 0:
        ball2.velocity[0] = -ball2.velocity[0]
    if ball2.rect.y > 500:
        ball2.velocity[1] = -ball2.velocity[1]
    if ball2.rect.y < 0:
        ball2.velocity[1] = -ball2.velocity[1]

    # Returns a boolean as to whether the two balls are colliding
    collisions = pygame.sprite.collide_rect(ball,ball2)
    if collisions == True:
      vel1 = ball.velocity
      vel2 = ball2.velocity
      ball.velocity = vel2
      ball2.velocity = vel1

    screen.fill(BLACK)
        #effect.play()   # play the sound clip each time the dot moves

    # Flip the display
    all_sprites_list.draw(screen)
    pygame.display.flip()
    timer.tick(60)       # slowed down to 1fps so beep is not too annoying

# Done! Time to quit.
pygame.quit()