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
        return midpointDisplacement(vertices1, vert_dis, level-1) + midpointDisplacement(vertices2, vert_dis, level-1) + midpointDisplacement(vertices3, vert_dis, level-1) + midpointDisplacement(vertices4, vert_dis, level-1)
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

print(len(VERTICES))
print(VERTICES)