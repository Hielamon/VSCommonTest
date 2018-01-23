'''
==============
3D scatterplot
==============

Demonstration of a basic scatterplot in 3D.
'''

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

def read3DPairs(filename):
    file = open(filename, 'r')
    line = file.readline()
    spt1 = []
    spt2 = []
    while line:
        line = line.replace('\n', ' ')
        line = line.split(' ')
        if len(line) < 6:
            break
        tmp1 = [float(line[0]), float(line[1]), float(line[2])]
        spt1.append(tmp1)
        tmp2 = [float(line[3]), float(line[4]), float(line[5])]
        spt2.append(tmp2)
        line = file.readline()
    return spt1, spt2


fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

n = 100

spt1, spt2 = read3DPairs('spherePts.txt')

# For each set of style and range settings, plot n random points in the box
# defined by x in [23, 32], y in [0, 100], z in [zlow, zhigh].
for i in range(0, len(spt1)):
    pt1 = spt1[i]
    pt2 = spt2[i]
    ax.scatter(pt1[0], pt1[1], pt1[2], c='r', marker='o')
    ax.scatter(pt2[0], pt2[1], pt2[2], c='b', marker='^')

ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

plt.show()