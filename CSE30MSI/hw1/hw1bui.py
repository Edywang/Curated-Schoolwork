import turtle
import math
import numpy as np
import random

# BEGIN
# =====================================================================

def midpointDisplacement(vertices,vert_dis=1,level=2):
    #vert 0 to 1
    mx1 = (vertices[0][0] + vertices[1][0]) / 2
    my1 = (vertices[1][0] + vertices[0][1]) / 2
    # vert 0 to 2
    mx2 = (vertices[0][0] + vertices[2][0]) / 2
    my2 = (vertices[2][0] + vertices[0][1]) / 2
    # vert 1 to 2
    mx3 = (vertices[1][0] + vertices[2][0]) / 2
    my3 = (vertices[2][0] + vertices[1][1]) / 2
    #midpoints x,y, z
    m1 = (mx1, my1, 0)
    m2 = (mx2, my2, 0)
    m3 = (mx3, my3, 0)
    if level == 0:
        newVert=[(m1, m2, m3),
                 (m2, m3, vertices[0]),
                 (m1, vertices[1], m3),
                 (m2, m3, vertices[2])]
        return newVert
    else:
        vertices1 = [(vertices[0]), (m1), (m2)]
        vertices2 = [(m3), (m1), (m2)]
        vertices3 = [(vertices[2]), (m3), (m1)]
        vertices4 = [(vertices[1]), (m2), (m3)]
        return midpointDisplacement(vertices1, vert_dis, level-1) + midpointDisplacement(vertices2, vert_dis, level-1) + midpointDisplacement(vertices3, vert_dis, level-1)+ midpointDisplacement(vertices4, vert_dis, level-1)
# Level 0 terrain (1 triangle)
initial_vertices = [(-1, 0, 0), (1, 0, 0), (0, 1, 0)]
level = 2

VERTICES = midpointDisplacement(initial_vertices)

# TRIANGLES = [(0, 1, 2), (3, 4, 5), ... (4^n *3 - 3, 4^n *3 - 2, 4^n *3 - 1)]
TRIANGLES = []
count = 0
myList = [-3, -2, -1]
for i in range(4**level):
  # Level is our n value 4^n, we want this to iterate once per triangle
  # On first iteration:
  myList[-1] += 3
  myList[1] += 3
  myList[0] += 3
  myTup = tuple(myList)
  TRIANGLES.append(myTup)
  count += 1

# =====================================================================
# END

def transform(x, y, z, angle, tilt):
    # Animation control (around y-axis)
    s, c = math.sin(angle), math.cos(angle)
    x, y = x * c - y * s, x * s + y * c

    # Camera tilt  (around x-axis)
    s, c = math.sin(tilt), math.cos(tilt)
    z, y = z * c - y * s, z * s + y * c

    # Setting up View Parameters
    y += 5  # Fixed Distance from top
    FOV = 1000  # Fixed Field of view
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
            sx, sy = transform(x[0],x[1],x[2], angle, 0.25)
            sx1, sy1 = transform(y[0],y[1], y[2],angle, 0.25)
            sx2, sy2 = transform(z[0],z[1], z[2],angle, 0.25)
            terrain.penup()
            terrain.goto(sx,sy)
            terrain.pendown()
            terrain.goto(sx1,sy1)
            terrain.goto(sx2,sy2)
            VERT2D.append((sx, sy))

        # Draw the terrain
        for triangle in TRIANGLES:
            points = []
            points.append(VERT2D[triangle[0]])
            points.append(VERT2D[triangle[1]])
            points.append(VERT2D[triangle[2]])




        # Update screen
        turtle.update()

        # Control the speed of animation
        angle += 0.0005


if __name__ == "__main__":
    main()
