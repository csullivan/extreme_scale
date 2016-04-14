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

def plot_size_v_time_fit(ax,data):



    postal_time = lambda n,s,r: s+r*n
    # popt,pcov = curve_fit(postal_time,data[0][0],data[0][1])
    # fit = lambda n: postal_time(n,popt[0],popt[1])
    # ax.plot(data[0][0],[fit(x) for x in data[0][0]],label='s+rn')
    x = []
    y = []
    for i,n in enumerate(data[0][0]):
        if n < 8193 and n > 4:
            x.append(n)
            y.append(data[0][1][i])
    x = np.asarray(x)
    y = np.asarray(y)

    ax.plot(x,y,label='blocking',color='black')
    popt,pcov = curve_fit(postal_time,x,y)
    fit = lambda n: postal_time(n,popt[0],popt[1])
    print popt
    ax.plot(x,[fit(xi) for xi in x],label='s1+r1*n',color='red')

    x = []
    y = []
    for i,n in enumerate(data[0][0]):
        if n > 8000:
            x.append(n)
            y.append(data[0][1][i])
    x = np.asarray(x)
    y = np.asarray(y)

    ax.plot(x,y,label='blocking',color='black')
    popt,pcov = curve_fit(postal_time,x,y)
    fit = lambda n: postal_time(n,popt[0],popt[1])
    print popt
    ax.plot(x,[fit(xi) for xi in x],label='s2+r2*n',color='blue')


    ax.set_ylim(1e-4,1e0)
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
    for i,line in enumerate(open("./bluewaters.dat")):
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


    plot_size_v_time_fit(ax,data)
    pylab.savefig("./bluewaters_fit.pdf")
    #pylab.show()
