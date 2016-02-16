import pylab
import numpy as np
from setfont import *

def plot_optimization(ax,data):
    opt = [0,1,2,3]
    for i in range (0,8)[1::2]:
        ax.plot(opt,data[:,i,1],color='black')        
    for i in range (0,8)[0::2]:
        ax.plot(opt,data[:,i,1],color='red')

    ax.set_yscale('log')
    setticks(ax,xlog=False,xminor=0.5,xmajor=1.0,ylog=True)
    pylab.show()

def plot_block_v_unblocked(ax,data):
    opt = [0,1,2,3]

    for i in opt:
        ax.plot(data[i,0::2,0],data[i,0::2,1],color='red')   # unblocked
        ax.plot(data[i,1::2,0],data[i,1::2,1],color='black') # blocked
        print data[i,0::2,1]
    ax.plot(data[0,0::2,0],data[0,0::2,2],color='blue') # model 1
    ax.plot(data[0,0::2,0],data[0,0::2,3],color='green') # model 2
    ax.set_yscale('log')
    ax.set_xscale('log')
    setticks(ax,xlog=True,ylog=True)
    pylab.show()
    
    
if __name__ =="__main__":
    setfont()
    data = []
    fig = pylab.figure(figsize=(5,5))
    ax = pylab.subplot(1,1,1)   
    #for line in open("./output.dat"):
    optclass = []
    for i,line in enumerate(open("./output_parsed.dat")):
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
    optclass.append(data)
    data = np.asarray(optclass)     #data[optimization,row,col]


    #plot_optimization(ax,data)
    plot_block_v_unblocked(ax,data)
