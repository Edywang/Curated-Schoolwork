import turtle

def drawC(x1, y1, x2, y2, color, level):
    turtle.pencolor(color)
    if level == 0:
        turtle.penup()
        turtle.goto(x1, y1)
        turtle.pendown()
        turtle.goto(x2, y2)
    else:
        mx = (x1 + x2 + y1 - y2)/2
        my = (x2 + y1 + y2 - x1)/2
        drawC(x1, y1, mx, my, color, level-1)
        drawC(mx, my, x2, y2, color, level-1)

turtle.setup() # We're creating our Turtle object
turtle.bgcolor("#aa9922") # BG Color
turtle.speed(8) # Turtle speed
turtle.colormode(255) # Turtle alpha
turtle.width(4) # Width of the line we're drawing
color = (12, 50, 231) # color = (red, green, blue), (255, 0, 0)
drawC(-100, -100, 0, 100, color, 6) # We're calling our function x1 = -100, y1 = -100, x2 = 0, y2 = 100, color, 6
turtle.done() # This leaves the turtle window on screen