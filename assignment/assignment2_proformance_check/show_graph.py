import sys
import matplotlib.pyplot as plt
filename = sys.argv[1]
f = open(filename, "r")
data = f.read()
splitdata = data.split("\n")
l = len(splitdata) - 1
splitdata = splitdata[:l]
tuplelist = []
for ele in splitdata:
    t = [float(b.strip()) for b in ((ele.split("[")[1]).split("]")[0]).split(",")]
    tuplelist.append([t[0],t[1],t[3]])

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

plt.figure(0)
tstr = "".join([str(i) for i in range(len(unique_iter))])
for i,ele in enumerate(unique_iter):
    plt.plot(unique_iter_x[i],unique_iter_y[i],label="Const_iter="+str(unique_iter[i]).split(".")[0] )
    plt.title("Using "+filename.split("/")[1]+ " method, and "+"for const iter=" + str(unique_iter[i]))
    plt.ylabel('cpu_time')
    plt.xlabel('Num_thread')
    plt.legend(tstr)
    plt.savefig('report/'+filename.split("/")[1] + '/'+'const_iter_'+str(unique_iter[i]).split(".")[0]+'.png')

plt.figure(1)
tstr = "".join([str(i) for i in range(len(unique_no_thread))])
for i,ele in enumerate(unique_no_thread):
    plt.plot(unique_no_thread_x[i],unique_no_thread_y[i] )
    plt.title("Using "+filename.split("/")[1]+ " method, and "+"for const NUM_THREAD=" + str(unique_no_thread[i]))
    plt.ylabel('cpu_time')
    plt.xlabel('Num_iters')
    plt.legend(tstr)
    plt.savefig('report/'+filename.split("/")[1] + '/'+'const_thread_'+str(unique_no_thread[i]).split(".")[0]+'.png')