
import pylab
import numpy as np
from setfont import *
import pdb
from scipy.optimize import curve_fit


def plot_size_v_time(ax,data):

    ax.plot(data[0][0],data[0][1],label='blocking')
    ax.plot(data[0][0],data[0][2],label='nonblocking')
    ax.plot(data[0][0],data[0][3],label='headtohead')
    line, = ax.plot(data[1][0],data[1][1],label='blocking')
    line.set_dashes([10, 5])
    line, = ax.plot(data[1][0],data[1][2],label='nonblocking')
    line.set_dashes([10, 5])
    line, = ax.plot(data[1][0],data[1][3],label='headtohead')
    line.set_dashes([10, 5])
    line, = ax.plot(data[2][0],data[2][1],label='blocking')
    line.set_dashes([2, 2])
    line, = ax.plot(data[2][0],data[2][2],label='nonblocking')
    line.set_dashes([2, 2])
    line, = ax.plot(data[2][0],data[2][3],label='headtohead')
    line.set_dashes([2, 2])

    ax.set_ylim(1e-4,1e0)
    ax.set_yscale('log')
    ax.set_xscale('log')
    setticks(ax,xlog=True,ylog=True)
    ax.legend(loc='upper left', prop={'size':9})

def plot_time_matrix_size(ax,data,ndatum,xlabel='NxN Matrix Size [dword]',ylabel='Time [s]',labeltoken=""):
    for nproc in set(data[:,1]):
        pylab.plot([np.sqrt(x) for i,x in enumerate(data[:,0]) if data[i,1]==nproc],[x for i,x in enumerate(data[:,ndatum]) if data[i,1] == nproc], label = labeltoken+"-n"+str(nproc))
        print [np.sqrt(x) for i,x in enumerate(data[:,0]) if data[i,1]==nproc],[x for i,x in enumerate(data[:,ndatum]) if data[i,1] == nproc]
    ax.set_yscale('log')
    ax.set_ylabel(ylabel)
    ax.set_xlabel(xlabel)
    setticks(ax,xlog=True,ylog=True)
    ax.legend(loc='upper left', prop={'size':9})
    pylab.savefig('./'+labeltoken+'.pdf')



if __name__ =="__main__":
    setfont()
    data = []
    fig = pylab.figure(figsize=(5.5,5))
    ax = pylab.subplot(1,1,1)

    # matrixsize = []
    # nprocs = []
    # t_ag = []
    # t_ring = []
    # tcomm_ag = []
    # tcomm_ring = []
    # perf_ag = []
    # perf_ring = []
    # data = []

    matsize,nprocs,t_ag,t_ring,tcomm_ag,tcomm_ring,perf_ag,perf_ring = [0 for x in range(0,8)]
    for i,line in enumerate(open("./bluewaters.dat")):
        line = line.split()
        if len(line) == 0:
            continue
        if len(line) == 4:
            if i != 0:
                data.append([matsize,nprocs,t_ag,t_ring,tcomm_ag,tcomm_ring,perf_ag,perf_ring])
            matsize = float(line[0])
            nprocs = float(line[1])
            t_ag = float(line[2])
            t_ring = float(line[3])
        if 'Perf' in line[0]:
            perf_ag = float(line[3])
            perf_ring = float(line[4])
        elif len(line) == 2:
            tcomm_ag = float(line[0])
            tcomm_ring = float(line[1])

    data = np.asarray(data)
    #print data[:,0]



    #plot_time_matrix_size(ax,data,2,xlabel="Matrix Size [dword]",ylabel="Time [s]",labeltoken="Tag")
    #plot_time_matrix_size(ax,data,3,xlabel="Matrix Size [dword]",ylabel="Time [s]",labeltoken="Tring")
    #plot_time_matrix_size(ax,data,5,xlabel="Matrix Size [dword]",ylabel="Time [s]",labeltoken="Tcomm-ring")
    plot_time_matrix_size(ax,data,7,xlabel="Matrix Size [dword]",ylabel=" Operations [1/thread/sec]",labeltoken="Ops-ring")
    #pylab.savefig("./bluewaters_fit.pdf")
    #pylab.show()
