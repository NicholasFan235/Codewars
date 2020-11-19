#from math import *

#y = sqrt(r**2 - (1/4)*((b[0]-a[0])**2+(b[1]-a[1])**2))
"""
circleIntersection = lambda a, b, r: \
    int(2*(r**2)*m.asin(m.sqrt(1 - (1/4)*(((b[0]-a[0])/r)**2+((b[1]-a[1])/r)**2))) -\
         2*m.sqrt(r**2 - (1/4)*((b[0]-a[0])**2+(b[1]-a[1])**2))*m.sqrt((1/4)*((b[0]-a[0])**2+(b[1]-a[1])**2))) \
             if (a[0]-b[0])**2 + (a[1]-b[1])**2 < 4*r**2 else 0
"""

#circleIntersection = lambda a, b, r, (y:=1) : y + y * r
"""
circleIntersection = lambda a,b,r:\
    (lambda d,r:\
        (lambda y,r:r*(m.asin(y**0.5)-y*m.sqrt(1/y-1))//2)(1-d/r,r) if d<r else 0)((a[0]-b[0])**2+(a[1]-b[1])**2,4*r**2)
"""
#from math import *;circleIntersection=lambda a,b,r:(lambda d:acos(d)-d*(1-d*d)**.5)(min(hypot(a[0]-b[0],a[1]-b[1])/2,r)/r)*r*r//.5


#def circleIntersection(a,b,r):from math import*;d=min(hypot(a[0]-b[0],a[1]-b[1])/2,r)/r;return(acos(d)-d*(1-d*d)**.5)*r*r//.5

from numpy import*;circleIntersection=lambda a,b,r:(lambda d:arccos(d)-d*(1-d*d)**.5)(min(hypot(*subtract(b,a))/2,r)/r)*r*r//.5

#print(circleIntersection([0,0], [5,0], 4))

print(circleIntersection([0,0],[0,7], 5))
print(circleIntersection([5, 6], [5, 6],3))
