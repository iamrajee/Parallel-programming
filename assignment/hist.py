import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

for i in range(4):
    df2 = pd.DataFrame(np.random.rand(6, 2), columns=['a', 'b'])
    print(np.random.rand(6, 2))
    ax = df2.plot(kind='bar')#, xticks=['1', '2', '4', '6', '8', '10' ])
    ax.set_xticklabels(['1', '2', '4', '6', '8', '10' ])
    # plt.savefig(str(i)+'.png')
    plt.title(str(i))
    plt.xlabel('x'+str(i))
    plt.ylabel('y'+str(i))
plt.show()
'''
fig = plt.figure()
ax = fig.add_subplot(111)

## the data
N = 5
menMeans = [18, 35, 30, 35, 27]
menStd =   [2, 3, 4, 1, 2]
womenMeans = [25, 32, 34, 20, 25]
womenStd =   [3, 5, 2, 3, 3]

## necessary variables
ind = np.arange(N)                # the x locations for the groups
width = 0.35                      # the width of the bars

## the bars
rects1 = ax.bar(ind, menMeans, width,
                color='black',
                yerr=menStd,
                error_kw=dict(elinewidth=2,ecolor='red'))

rects2 = ax.bar(ind+width, womenMeans, width,
                    color='red',
                    yerr=womenStd,
                    error_kw=dict(elinewidth=2,ecolor='black'))

# axes and labels
ax.set_xlim(-width,len(ind)+width)
ax.set_ylim(0,45)
ax.set_ylabel('Scores')
ax.set_title('Scores by group and gender')
xTickMarks = ['Group'+str(i) for i in range(1,6)]
ax.set_xticks(ind+width)
xtickNames = ax.set_xticklabels(xTickMarks)
plt.setp(xtickNames, rotation=45, fontsize=10)

## add a legend
ax.legend( (rects1[0], rects2[0]), ('Men', 'Women') )

plt.show()
'''