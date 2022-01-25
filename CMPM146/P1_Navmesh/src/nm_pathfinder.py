# Usage: python nm_interactive.py ../input/homer.png ../input/homer.png.mesh.pickle 1
import sys
import math
import heapq

from DijkstraForwardSearch import Dijkstra_forward_search as Dijk
box_data = {}
# Global reference to mesh
g_mesh = None
queue = []
# A list of boxes explored by the algorithm
explored_boxes = []

def find_path (source_point, destination_point, mesh):
    global g_mesh
    g_mesh = mesh
    queue.clear()
    explored_boxes.clear()
    box_data.clear()

    """
    Searches for a path from source_point to destination_point through the mesh

    Args:
        source_point: starting point of the pathfinder
        destination_point: the ultimate goal the pathfinder must reach
        mesh: pathway constraints the path adheres to

    Returns:

        A path (list of points) from source_point to destination_point if exists
        A list of boxes explored by the algorithm
    """

    # Unpacking source_point into x and y
    sx, sy = source_point
    # Unpacking destination_point into x and y
    dx, dy = destination_point
    # Box the source point is in
    source_box = None
    # Box the destination point is in
    destination_box = None

    # Create data for search algo for every nav mesh box
    for box in mesh.get("boxes"):
        box_data[box] = {"parent": None}
        if sx >= box[0] and sx <= box[1] and sy >= box[2] and sy <= box[3]:
            source_box = box
        if dx >= box[0] and dx <= box[1] and dy >= box[2] and dy <= box[3]:
            destination_box = box

    # Check if source and destination valid
    if source_box is None or destination_box is None:
        print("No path!")
        return [], []

    # Pre-search algo data
    set_visited(source_box)

    # A path (list of points) from source_point to destination_point if exists
    # Main search algo loop
    heapq.heappush(queue, (getDist(source_point, destination_point), source_box))
    # print(queue)
    set_cost(source_box, 0)
    set_point(source_box, source_point)
    # explored_boxes = []
    while queue:
        curr_node = queue.pop(0)[1]
        curr_point = get_point(curr_node)
        currCost = get_cost(curr_node)
        explored_boxes.append(curr_node)
        # print(i, end=" ")

        if curr_node == destination_box:
            break

        if currCost is None:
            print("No path!")
            return [], []

        adj_nodes = mesh.get("adj")[curr_node]
        for adj in adj_nodes:
            if adj not in explored_boxes:
                if get_point(adj) is None or getDist(curr_point, get_closest(adj, curr_point)) + get_cost(curr_node) < get_cost(adj):
                    set_cost(adj, getDist(curr_point, get_closest(adj, curr_point)) + get_cost(curr_node))
                    set_point(adj, get_closest(adj, curr_point))
                    set_parent(adj, curr_node)
                # adjCost = get_cost(adj)
                # if adjCost is None or adjCost > currCost:
                #     set_cost(adj, currCost + 1)
                #     set_parent(adj, curr_node)
                heapq.heappush(queue, (getDist(get_point(adj) , destination_point) + get_cost(adj), adj))
                # queue.append(adj)

    # create path by reading boxes
    # current = destination_box
    # path = []
    # while current != source_box:
    #     path.append(current)
    #     current = boxes[current]
    # path.append(source_box)
    # path.reverse()
    # Check if destination was successfully visited
    if not check_visited(destination_box):
        print("No path!")
        return [], []

    path = []
    currPar = get_parent(destination_box)
    while currPar is not None:
        path.insert(0, get_point(currPar))
        currPar = get_parent(currPar)
    path.append(get_point(destination_box))
    path.append(destination_point)
    return path, explored_boxes


def boxData(box):
    return box_data.get(box)


def adj_list(box):
    return g_mesh.get("adj").get(box)


def check_visited(box):
    return box in explored_boxes


def set_visited(box):
    explored_boxes.append(box)


def set_point(box, pt):
    boxData(box)["point"] = pt


def get_point(box):
    return boxData(box).get("point")


def get_cost(box):
    return boxData(box).get("cost")


# Set cost from start to node
def set_cost(box, cost):
    boxData(box)["cost"] = cost


def get_parent(box):
    return boxData(box).get("parent")


def set_parent(box, parent):
    boxData(box)["parent"] = parent


# TODO: Given a box and a point, return the closest point on the box's edge to the point ignoring obstruction
def get_closest(box, point):
    newPoint = []
    # point is (x, y)
    ptX, ptY = point
    maxX = max(box[0], box[1])
    minX = min(box[0], box[1])
    maxY = max(box[2], box[3])
    minY = min(box[2], box[3])
    # Grab closest X point
    if ptX > maxX:
        newPoint.append(maxX)
    elif ptX < minX:
        newPoint.append(minX)
    else:
        newPoint.append(ptX)
    # Grab closest Y point
    if ptY > maxY:
        newPoint.append(maxY)
    elif ptY < minY:
        newPoint.append(minY)
    else:
        newPoint.append(ptY)
    return newPoint

def getDist(pt1, pt2):
    return math.sqrt(abs(((pt1[0] - pt2[0])^2) + ((pt1[1] - pt2[1])^2)))