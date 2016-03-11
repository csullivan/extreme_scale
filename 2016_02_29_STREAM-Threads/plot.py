import pylab
import numpy as np
from setfont import *



def plot_rate_threads(ax,data):
    model = []
    for nt in data[:,0]:
        model.append(data[0,3]*nt)
    ax.plot(data[:,0],data[:,3])
    ax.plot(data[:,0],model)
    ax.plot(data[:,0],[30 for x in data[:,0]])

    #ax.set_yscale('log')
    setticks(ax,xmajor=2,xminor=1,ymajor=2,yminor=1)
    pylab.show()
def plot_time_threads(ax,data):
    ax.plot(data[:,0],data[:,2])
    #ax.set_yscale('log')
    setticks(ax,xmajor=2,xminor=1,ylog=True)
    pylab.show()

if __name__ =="__main__":
    setfont()
    data = []
    fig = pylab.figure(figsize=(5,5))
    ax = pylab.subplot(1,1,1)   
    #for line in open("./output.dat"):
    optclass = []
    for i,line in enumerate(open("./plotdata_1e9.dat")):
        if '#' in line:
            continue
        if 'O' in line:
            if i == 1:
                continue
            data = np.asarray(data)
            optclass.append(data)
            data = []
            continue
        line = line.split()
        line = [float(x) for x in line[:-1]]
        data.append(np.asarray(line))
    data = np.asarray(data)

    plot_rate_threads(ax,data)
    #plot_time_threads(ax,data)
