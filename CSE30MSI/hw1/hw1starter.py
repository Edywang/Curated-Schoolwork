# COPY THIS CODE TO CREATE A .py FILE TO RUN or COPY TO A JUPYTER (NOT COLAB) NOTEBOOK AND RUN
# -*- coding: utf-8 -*-
"""
Created on Thu Apr 15 15:04:11 2020
CSE 30 Spring 2020 Program 1 helper code
@author: Fahim
"""

import math
import turtle

# Note: For this example, we are using hardcoded points/vertices to test the functionalities of the viewer and animation. 
# For Program 1, you need to replace the code between the tags # BEGIN and # END with your code. 
# Your code should generate the VERTICES and TRIANGLES using your recursive "midpoint_displacement" function. 
# This setup is optimized for points values generated in the range -1.00 to 1.00.
# You may need the adjust the value of FOV to generate points with higher ranges.


# BEGIN
#=====================================================================
#Level 0 terrain (1 triangle)
#VERTICES = [(-1, 0, 0), ( 1, 0, 0), ( 0, 1, 0)]

#TRIANGLES = [(0, 1, 2)]

#Level 1 terrain (4 pregenerated triangles)
VERTICES = [(-1, -0.2, 0), (-0.25, 0, 0), (0, 0, 0.75),
            (0, 0, 0.75), (0.25, 1, 0.75), (-0.25, 0, 0),
            (-0.25, 0, 0), (0, 1, 0), (0.25, 1, 0.75),
            (0.25, 1, 0.75), (1, 0, 0), (0, 0, 0.75)]

TRIANGLES = [(0, 1, 2),
             (3, 4, 5),
             (6, 7, 8),
             (9, 10, 11)]

#=====================================================================
# END
    
def transform(x, y, z, angle, tilt):
    #Animation control (around y-axis). If considered as a view of earth from space, it's moving over the equator.
    s, c = math.sin(angle), math.cos(angle)
    x, z = x * c - z * s, x * s + z * c

    #Camera tilt  (around x-axis). If considered as a view of earth from space, the tilt angle is measured from the equator.
    s, c = math.sin(tilt), math.cos(tilt)
    y, z = y * c - z * s, y * s + z * c

    # Setting up View Parameters
    z += 5     #Fixed Distance from top
    FOV = 1000      #Fixed Field of view
    f = FOV / z
    sx, sy = x * f, y * f
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

            # Draw the trangle
            terrain.goto(points[0][0], points[0][1])
            terrain.down()

            terrain.goto(points[1][0], points[1][1])
            terrain.goto(points[2][0], points[2][1])
            terrain.goto(points[0][0], points[0][1])
            terrain.up()

        # Update screen
        turtle.update()

        # Control the speed of animation
        angle += 0.0005

if __name__ == "__main__":
    main()