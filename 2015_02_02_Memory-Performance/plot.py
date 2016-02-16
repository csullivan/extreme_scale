import pylab
import numpy as np
from setfont import *

if __name__ =="__main__":
    setfont()
    data = []
    fig = pylab.figure(figsize=(5,2))
    ax = pylab.subplot(1,1,1)   
    #for line in open("./output.dat"):
    for line in open("./runs.dat"):
        line = line.split()
        line = [float(x) for x in line]
        data.append(np.asarray(line))
    data = np.asarray(data)
    ax.scatter(data[:,0],data[:,2])
    ax.plot([1,1e9],[41.5391,41.5391])
    ax.set_xlim(1e2,1e7)    
    ax.set_xscale('log')
    #ax.set_ylim(-0.00002,0.0005)
    ax.set_ylim(1,100)
    #setticks(ax,xlog=True,ylog=False,ymajor=0.0001,yminor=0.00005)
    setticks(ax,xlog=True,ylog=False,ymajor=10,yminor=5)
    pylab.show()
