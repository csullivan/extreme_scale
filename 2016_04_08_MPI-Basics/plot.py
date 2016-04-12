import pylab
import numpy as np
from setfont import *
import pdb

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

    ax.set_yscale('log')
    ax.set_xscale('log')
    setticks(ax,xlog=True,ylog=True)
    ax.legend(loc='upper left', prop={'size':9})


if __name__ =="__main__":
    setfont()
    data = []
    fig = pylab.figure(figsize=(5,5))
    ax = pylab.subplot(1,1,1)

    blocking = []
    nonblocking = []
    headtohead = []
    messagesize = []
    count = 0
    for i,line in enumerate(open("./output.dat")):
        if len(line.split()) == 0:
            continue
        if '####' in line:
            count += 1
            if count==1:
                continue
            blocking = np.asarray(blocking)
            nonblocking = np.asarray(nonblocking)
            headtohead = np.asarray(headtohead)
            messagesize = np.asarray(messagesize)
            data.append([messagesize, blocking, nonblocking, headtohead])
            blocking = []
            nonblocking = []
            headtohead = []
            messagesize = []
            continue
        elif 'Message' in line:
            messagesize.append(float(line.split()[4]))
        if 'Head-to-head' in line:
            headtohead.append(float(line.split()[6]))
        elif 'Non-blocking' in line:
            nonblocking.append(float(line.split()[6]))
        elif 'Blocking' in line:
            blocking.append(float(line.split()[6]))

    blocking = np.asarray(blocking)
    nonblocking = np.asarray(nonblocking)
    headtohead = np.asarray(headtohead)
    messagesize = np.asarray(messagesize)
    data.append([messagesize, blocking, nonblocking, headtohead])
    #data = np.asarray(data)

    plot_size_v_time(ax,data)
    pylab.savefig("./output.pdf")
    #pylab.show()
