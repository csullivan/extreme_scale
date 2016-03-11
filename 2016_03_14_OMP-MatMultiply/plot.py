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

def plot_time_v_thread(ax,nthreads,data):
    #data[ompthreadsnum,row,col]
    #for i,numth in enumerate(nthreads):
    #ax.plot(nthreads,data[:,0,1]) # 20
    #ax.plot(nthreads,data[:,1,1]) # 100
    ax.plot(nthreads,data[:,2,1]) # 1000
    ax.plot(nthreads,data[:,3,1]) # 1700

    ax.set_yscale('log')
    ax.set_xlim(0,32)
    #ax.set_xscale('log')
    setticks(ax,xlog=True,ylog=True)
    pylab.show()
def plot_rate_v_thread(ax,nthreads,data):
    #data[ompthreadsnum,row,col]
    #for i,numth in enumerate(nthreads):
    #ax.plot(nthreads,data[:,0,1]) # 20
    #ax.plot(nthreads,data[:,1,1]) # 100
    rate = [2*1000*1000*1.0e-6/x for x in data[:,2,1]]
    ax.plot(nthreads,rate) # 1000
    rate = [2*1700*1700*1.0e-6/x for x in data[:,3,1]]
    ax.plot(nthreads,rate) # 1700

    ax.set_yscale('log')
    ax.set_xlim(0,32)
    #ax.set_xscale('log')
    setticks(ax,xlog=True,ylog=True)
    pylab.show()

if __name__ =="__main__":
    setfont()
    data = []
    fig = pylab.figure(figsize=(5,5))
    ax = pylab.subplot(1,1,1)   
    #for line in open("./output.dat"):
    ompclass = []
    nthreads = []
    for i,line in enumerate(open("./output_parsed2.dat")):
        if '#' in line:
            continue
        if 'OMP' in line:
            nthreads.append(int(line.split()[1]))
            if i == 0:
                continue
            data = np.asarray(data)
            ompclass.append(data)
            data = []
            continue
        line = line.split()
        line = [float(x) for x in line]
        data.append(np.asarray(line))
    data = np.asarray(data)
    ompclass.append(data)
    data = np.asarray(ompclass)     #data[ompthreadsnum,row,col]

    print data
    print len(data)
    #plot_time_v_thread(ax,nthreads,data)
    plot_rate_v_thread(ax,nthreads,data)
