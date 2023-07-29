import cv2
import numpy as np
import math
import queue

class circle:
    pass

class node:
    pass

circles = []
lines = []
nodes = []

#sx, sy, ex, ey = [float(s) for s in input().split(" ")]
n = int(input())
for i in range(n):
    c = circle()
    cx, cy, r = [float(s) for s in input().split(" ")]
    c.position = (cx, cy)
    c.radius = r
    c.intersections = []
    ni = int(input())
    for ii in range(ni):
        ss, se = [float(s) for s in input().split(" ")]
        c.intersections.append((ss, se))
    c.links = []
    nl = int(input())
    for il in range(nl):
        ss, se = [float(s) for s in input().split(" ")]
        c.links.append((ss, se))
    circles.append(c)

n = int(input())
for i in range(n):
    ix,iy, jx,jy = [float(s) for s in input().split(" ")]
    lines.append(((ix, iy), (jx, jy)))

n  = int(input())
#print(n)
for i in range(n):
    _node = node()
    _node.index = int(input())
    px, py = [float(s) for s in input().split(" ")]
    nl = int(input())
    _node.position = (px, py)
    _node.links = []
    for il in range(nl):
        link = [s for s in input().split(" ")]
        assert len(link)==2
        _node.links.append((int(link[0]), float(link[1])))
    s = input()
    print(s)
    _node.cost = float(s)
    nodes.append(_node)


width = 10000
height = 10000
image = np.ones((height, width, 3), np.uint8)*255

zoom = 200

for c in circles:
    position = (math.floor(c.position[0]*zoom + width/2), math.floor(c.position[1]*zoom + height/2))
    radius =  math.floor(c.radius*zoom)
    image = cv2.circle(image, position, radius, (0, 255, 255), -1)
for c in circles:
    position = (math.floor(c.position[0]*zoom + width/2), math.floor(c.position[1]*zoom + height/2))
    radius =  math.floor(c.radius*zoom)
    image = cv2.circle(image, position, radius, (0, 0, 0), 1)
    #for i in c[3]:
    #    if i[1]>i[0]:
    #        image = cv2.ellipse(image, position, (radius, radius), 0, i[0]*180/math.pi, i[1]*180/math.pi, (255, 0, 0), 2)
    #    else:
    #        image = cv2.ellipse(image, position, (radius, radius), 0, i[0]*180/math.pi, i[1]*180/math.pi+360, (255, 0, 0), 2)
    for l in c.links:
        if l[1]>l[0]:
            image = cv2.ellipse(image, position, (radius, radius), 0, l[0]*180/math.pi, l[1]*180/math.pi, (0, 255, 0), 2)
        else:
            image = cv2.ellipse(image, position, (radius, radius), 0, l[0]*180/math.pi, l[1]*180/math.pi+360, (0, 255, 0), 2)


for l in lines:
    p1 = (math.floor(l[0][0]*zoom + width/2), math.floor(l[0][1]*zoom + height/2))
    p2 = (math.floor(l[1][0]*zoom + width/2), math.floor(l[1][1]*zoom + height/2))
    image = cv2.line(image, p1, p2, (0, 255, 0), 2)

for n in nodes:
    position = (math.floor(n.position[0]*zoom + width/2), math.floor(n.position[1]*zoom + height/2))
    image = cv2.circle(image, position, 5, (0, 0, 255), -1)
    image = cv2.putText(image, str(n.index), position, cv2.FONT_HERSHEY_PLAIN, 2, (0,0,0))

for i in range(len(nodes)):
    #print(nodes[i].cost)
    pass

'''
nodes[14].cost = 0
checkQueue = queue.Queue()
checkQueue.put(14)
while not checkQueue.empty():
    item = checkQueue.get()
    for i in range(len(nodes[item].links)):
        newCost = nodes[item].cost + nodes[item].links[i][1]
        if nodes[nodes[item].links[i][0]].cost > newCost:
            nodes[nodes[item].links[i][0]].cost = newCost
            checkQueue.put(nodes[item].links[i][0])
print(nodes[17].cost)
'''

cv2.imwrite('outputs/test.jpg', image)