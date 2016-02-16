import pylab
import numpy as np
from setfont import *

if __name__ =="__main__":
    setfont()
    data = []
    fig = pylab.figure(figsize=(5,5))
    ax = pylab.subplot(1,1,1)   
    #for line in open("./output.dat"):
    for line in open("./tableO0.dat"):
        if '#' in line:
            continue
        line = line.split()
        line = [float(x) for x in line]
        data.append(np.asarray(line))
    data = np.asarray(data)
    ax.plot(data[:,0],data[:,1])
    #ax.plot(data[:,0],data[:,2])
    #ax.plot(data[:,0],data[:,3])
    ax.plot(data[:,0],data[:,4])
    ax.plot(data[:,0],data[:,5])
    ax.set_xscale('log')
    ax.set_yscale('log')
    setticks(ax,xlog=True,ylog=True)
    pylab.show()
