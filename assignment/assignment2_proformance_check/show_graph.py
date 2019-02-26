import sys
from matplotlib import pyplot as plt
import numpy as np
filename = sys.argv[1]

def data_clean(filename):
    f = open(filename, "r")
    data = f.read()
    splitdata = data.split("\n")
    l = len(splitdata) - 1
    splitdata = splitdata[:l]
    tuplelist = []
    for ele in splitdata:
        t = [float(b.strip()) for b in ((ele.split("[")[1]).split("]")[0]).split(",")]
        lt = len(t)
        i,ts = 3,0.0
        while i < lt:
            ts+=t[i]
            i+=2
        tuplelist.append([t[0],t[1],ts/((lt-2)/2)])
    unique_iter = []
    for ele in tuplelist:
        if ele[0] not in unique_iter:
            unique_iter.append(ele[0])
    unique_no_thread = []
    for ele in tuplelist:
        if ele[1] not in unique_no_thread:
            unique_no_thread.append(ele[1])
    
    unique_iter_x = []
    unique_iter_y = []
    for ele1 in unique_iter:
        templistx = []
        templisty = []
        for ele2 in tuplelist:
            if ele1 == ele2[0]:
                templistx.append(ele2[1])
                templisty.append(ele2[2])
        unique_iter_x.append(templistx)
        unique_iter_y.append(templisty)
    
    unique_no_thread_x = []
    unique_no_thread_y = []
    for ele1 in unique_no_thread:
        templistx = []
        templisty = []
        for ele2 in tuplelist:
            if ele1 == ele2[1]:
                templistx.append(ele2[0])
                templisty.append(ele2[2])
        unique_no_thread_x.append(templistx)
        unique_no_thread_y.append(templisty)

    return (unique_iter,unique_iter_x,unique_iter_y,unique_no_thread,unique_no_thread_x,unique_no_thread_y)

(unique_iter,unique_iter_x,unique_iter_y,unique_no_thread,unique_no_thread_x,unique_no_thread_y) = data_clean(filename)

if len(unique_no_thread) > 1:
    plt.figure(0)
    for i,ele in enumerate(unique_iter):
        plt.plot(unique_iter_x[i],unique_iter_y[i],label='iteration='+str(unique_iter[i]).split(".")[0])
        plt.title("Using "+filename.split("/")[1]+ " method")
        plt.ylabel('cpu_time')
        plt.xlabel('Num_thread')
    plt.legend()
    plt.savefig('report/'+filename.split("/")[1] + '/'+'const_iteration'+'.png') #_'+str(unique_iter[i]).split(".")[0]+'.png')


if len(unique_iter) > 1:
    plt.figure(2)
    for i,ele in enumerate(unique_no_thread):
        plt.plot(unique_no_thread_x[i],unique_no_thread_y[i],label='NUM_THREAD='+str(unique_no_thread[i]).split(".")[0])
        plt.title("Using "+filename.split("/")[1]+ " method")
        plt.ylabel('cpu_time')
        plt.xlabel('Num_iters')
    plt.legend()
    plt.savefig('report/'+filename.split("/")[1] + '/'+'Const_NUM_THREAD'+'.png')