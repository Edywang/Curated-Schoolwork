import turtle
import math

height = 500
width = 500
turtle.screensize(height, width)

VERTICES = [(200, 200, 200), (200, 200, -200), (200, -200, 200), (200, -200, -200), (-200, 200, 200), (-200, 200, -200), (-200, -200, 200), (-200, -200, -200)]
TRIANGLES = [(0, 1, 3, 2), (0, 1, 5, 4), (0, 2, 6, 4), (4, 5, 7, 6), (2, 3, 7, 6), (1, 3, 7, 5)]
# Triangles = positive x, positive y, positive z, negative x, negative y, negative z

def transform(x, y, z, angle, tilt):
    #Animation control (around y-axis)
    s, c = math.sin(angle), math.cos(angle)
    x, y = x * c - y * s, x * s + y * c

    #Camera tilt  (around x-axis)
    s, c = math.sin(tilt), math.cos(tilt)
    z, y = z * c - y * s, z * s + y * c

    # Setting up View Parameters
    y += 2500 #Fixed Distance from top
    FOV = 1000 #Fixed Field of view
    f = FOV / y
    sx, sy = x * f, z * f
    return sx, sy

def main():
    # Create terrain using turtle
    terrain = turtle.Turtle()
    terrain.pencolor("blue")
    terrain.pensize(2)

    # Turn off move time for instant drawing
    turtle.tracer(0, 0)
    terrain.up()
    angle = 0
    
    while True:
        # Clear the screen
        terrain.clear()
        
        # Transform the terrain
        VERT2D = []
        for vert3D in VERTICES:
            x, y, z = vert3D
            sx, sy = transform(x, y, z, angle, 0.25)
            VERT2D.append((sx, sy))

        # Draw the terrain
        for triangle in TRIANGLES:
            points = []
            points.append(VERT2D[triangle[0]])
            points.append(VERT2D[triangle[1]])
            points.append(VERT2D[triangle[2]])
            points.append(VERT2D[triangle[3]])

            # Draw the trangle
            terrain.goto(points[0][0], points[0][1])
            terrain.down()

            terrain.goto(points[1][0], points[1][1])
            terrain.goto(points[2][0], points[2][1])
            terrain.goto(points[3][0], points[3][1])
            terrain.goto(points[0][0], points[0][1])
            terrain.up()

        # Update screen
        turtle.update()

        # Control the speed of animation
        angle += 0.0005

if __name__ == "__main__":
    main()


turtle.done()