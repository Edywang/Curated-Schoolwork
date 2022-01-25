import pygame
import numpy
from random import randint

pygame.init()


class Dot():
    def __init__(self, start, end, c_pos, state):
        self.gps = start
        self.state = state
        self.goal = end
        self.c_pos = c_pos

    """
    def moveManhattan(self):
        # write code to move from start_pos to end_pos in hor/ver or ver/hor
        sx = numpy.sign(self.goal[0] - self.gps[0])  # returns -1,0,1
        if sx:
            self.gps = (self.gps[0] + sx, self.gps[1])
        else:
            sy = numpy.sign(self.goal[1] - self.gps[1])
            self.gps = (self.gps[0], self.gps[1] + sy)

    def moveLine(self):
        # write code to move in straight line
        dx = self.goal[0] - self.gps[0]
        nx = self.gps[0] + 0.1 * dx

        dy = self.goal[1] - self.gps[1]
        ny = self.gps[1] + 0.1 * dy
        self.gps = (nx, ny)
    """
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


class Ball(pygame.sprite.Sprite):
    def __init__(self, color, radius):
        # def __init__(self, color, width, height):
        # super().__init__(self, color, (radius*2, radius*2))
        super().__init__()
        

        self.image = pygame.Surface((30, 30))
        self.image.fill(WHITE)
        self.image.set_colorkey(WHITE)

        pygame.draw.circle(self.image, color, (15, 15), 5)

        self.velocity = [-1, 1]

        self.rect = self.image.get_rect()

    def update(self):
        self.rect.x += self.velocity[0]
        self.rect.y += self.velocity[1]

    def bounce(self):
        self.velocity[0] = -self.velocity[0]
        self.velocity[1] = randint(-8, 8)


# class Bubble(pygame.sprite.Sprite):


WHITE = [255, 255, 255]
DEAD = (0, 0, 0)
UNEXPOSED = (0, 0, 255)
INFECTED = (255, 165, 0)
SICK = (255, 0, 0)
IMMUNE = (0, 255, 0)

size = (500, 500)
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Ball")

# ball = Ball(WHITE, 10, 10)
# ball.rect.x = 345
# ball.rect.y = 195

all_sprites_list = pygame.sprite.Group()

for i in range(10):
    ball = Ball(UNEXPOSED, (10, 10))
    ball.rect.x = randint(0, 499)
    ball.rect.y = randint(0, 499)
    # random radius from 10 to 200

    # adding the sprites to the list
    all_sprites_list.add(ball)

    # for dots in all_sprites_list.

carryOn = True

clock = pygame.time.Clock()

while carryOn:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            carryOn = False

    all_sprites_list.update()

    # Detect collisions between the ball and the others
    for ball in all_sprites_list:
        if pygame.sprite.spritecollideany(ball, all_sprites_list):
            ball.bounce()
        if ball.rect.x > 490:
            ball.velocity[0] = -ball.velocity[0]
        if ball.rect.x <= 0:
            ball.velocity[0] = -ball.velocity[0]
        if ball.rect.y > 490:
            ball.velocity[1] = -ball.velocity[1]
        if ball.rect.y < 0:
            ball.velocity[1] = -ball.velocity[1]



    screen.fill(WHITE)

    all_sprites_list.draw(screen)

    pygame.display.flip()

    clock.tick(60)

pygame.quit()

