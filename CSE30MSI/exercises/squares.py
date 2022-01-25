import turtle

def draw_square(corners, color):
    ''' draws a single square and fills with color.
        assumes corners is list of 4 tuples representing the corners. '''

    turtle.fillcolor( color )                   # specify fillcolor
    turtle.penup()                              # don't draw anything yet
    turtle.begin_fill()                         # start of shape to fill
    turtle.goto( corners[0][0], corners[0][1] ) # starting point of shape
    turtle.pendown()                            # start drawing
    for i in range(len(corners)):               # draw to each corner & back
        turtle.goto( corners[(i+1)%4][0], corners[(i+1)%4][1] )
    turtle.end_fill()                           # end of shape to fill

# 2d Array, x, y

colors = [(255,0,0),        # red
          (0,255,0),        # green
          (0,0,255),        # blue
          (128,128,128),    # gray
          (132, 31,  1),    # rand1
          ( 21, 12,122),    # rand2
          (123, 41,232),    # rand3
          ( 32,121, 49)]    # rand4

pt1=(-100, 100)
pt2=( 100, 100)
pt3=( 100,-100)
pt4=(-100,-100)

square=[pt1,pt2,pt3,pt4]    # outermost square

turtle.setup()              # setup canvas using default params
turtle.colormode(255)       # colors are defined as triples of 0..255 each
turtle.speed(5)             # draw as fast as you can
bob = turtle.Turtle()       # create drawing turtle

draw_square( square, colors[0] )

ts = turtle.getscreen()

dim = 100
dim2 = 80
for i in range(0, 7):
    pt1 = (-dim, dim2)
    pt2 = (dim2, dim)
    pt3 = (dim, -dim2)
    pt4 = (-dim2, -dim)
    square = [pt1, pt2, pt3, pt4]
    draw_square(square, colors[i + 1])
    dim *= 0.8
    dim2 *= 0.8
    

turtle.done()