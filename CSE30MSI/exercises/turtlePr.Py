import turtle

star = turtle.Turtle() # creating a Turtle object and naming it star
star.color('red', 'yellow')
# Setter, sets variable color within our object star to 'red' and 'yellow'
star.begin_fill() # We want to fill in this shape we're gonna draw
while True: # Infinite loop
    star.forward(200)
    star.left(170)
    if abs(star.pos()) < 1: # Loop invariant
        break
star.end_fill()
turtle.done()

# If pip is not installed use easy_install
# easy_install turtle
# pip install turtle
# pip uninstall turtle
# pip install turtle