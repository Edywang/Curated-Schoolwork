def midpoint_displacement(vertices, vertical_displacement=1, level=1):
  """
  Our midpoint_displacement function will generate vertices based off of an initial triangle
  """
  #vert 0 to 1
  mx1= (vertices[0][0]+vertices[1][0]+vertices[0][1]-vertices[1][1])/2
  my1= (vertices[1][0]+vertices[0][1]+vertices[1][1]-vertices[1][0])/2
  #mx1 = (vertices[0][0]+vertices[1][0])/2
  #my1 = (vertices[1][1]+vertices[0][1])/2
  #vert 0 to 2
  mx2= (vertices[0][0]+vertices[2][0]+vertices[0][1]-vertices[2][1])/2
  my2= (vertices[2][0]+vertices[0][1]+vertices[2][1]-vertices[0][0])/2
  #mx2 = (vertices[0][0]+vertices[2][0])/2
  #my2 = (vertices[2][1]+vertices[0][1])/2
  #vert 1 to 2
  mx3= (vertices[1][0]+vertices[2][0]+vertices[1][1]-vertices[2][1])/2
  my3= (vertices[2][0]+vertices[1][1]+vertices[2][1]-vertices[1][0])/2
  #mx3 = (vertices[1][0]+vertices[2][0])/2
  #my3 = (vertices[2][1]+vertices[1][1])/2

  m1= (mx1,my1, 0)
  m2= (mx2,my2, 0)
  m3= (mx3,my3, 0)
  if level == 0:
    newVert = [m1, m2, m3]
    return newVert
  else:
    vertices1 = [(vertices[0]), (m1), (m2)]
    vertices2 = [(m1), (m2), (m3)]
    vertices3 = [(m1), (m3), (vertices[1])]
    vertices4 = [(m2), (m3), (vertices[2])]
    return vertices1 + vertices2 + vertices3 + vertices4 + midpoint_displacement(vertices1, vertical_displacement, level-1) + midpoint_displacement(vertices2, vertical_displacement, level-1) + midpoint_displacement(vertices3, vertical_displacement, level-1) + midpoint_displacement(vertices4, vertical_displacement, level-1)

vertices = midpoint_displacement([(0, 1, 0), (-1, 0, 0), (1, 0, 0)])
for i in vertices:
    print(i)