#!/usr/bin/python
import numpy as np
if __name__=="__main__":
    time = lambda N: 5e-10*2*np.power(N,3)
    time2 = lambda N: 3.84676e-10*2*np.power(N,3)
    N = [100, 200, 400, 800, 1000, 1200, 1400, 1600, 2000]
    print time(N)
    print time2(N)
    for n in N:
        print n
        print "Estimate 1 =", "%.2e" % time(n), "secs"
        print "Estimate 2 =", "%.2e" % time2(n), "secs"
        

