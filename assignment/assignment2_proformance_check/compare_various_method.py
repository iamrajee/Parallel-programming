import sys
import numpy as np
import matplotlib.pyplot as plt
from show_graph import data_clean
import pandas as pd

filelist = ['busywait','mutex_simple', 'mutex_overhead', 'barrier_busywait_and_mutex', 'barrier_condvar', 'barrier_sem', 'rwlock']


filename_s = 'report/serial/serial.txt'
(ui_s,ui_x_s,ui_y_s,ut_s,ut_x_s,ut_y_s) = data_clean(filename_s)
ts = ut_y_s[0]

tplist = []
for file in filelist:
    filename_p = 'report/'+file+'/'+file+'.txt'
    (ui_p,ui_x_p,ui_y_p,ut_p,ut_x_p,ut_y_p) = data_clean(filename_p)
    tplist.append(ut_y_p)

ef = []
for i,tp_df in enumerate(tplist):
    file = filelist[i]
    ef_df = []
    for j,tp_df_dt in enumerate(tp_df):
        t = ut_p[j]
        ef_df_dt = []
        for k,tp_df_dt_di in enumerate(tp_df_dt):
            ef_df_dt_di = ts[k]/tp_df_dt_di
            # if ef_df_dt_di >= 1:
                # print(i,j,k,"warning")
            ef_df_dt.append(ef_df_dt_di)
        ef_df.append(ef_df_dt)
    ef.append(ef_df)

for i,ele in enumerate(np.transpose(ef)):
    df2 = pd.DataFrame(np.array(ele), columns=filelist)
    ax = df2.plot(kind='bar')
    ax.set_xticklabels(ut_p)
    plt.title('for iteration = ' + str(ui_s[i]))
    plt.xlabel("NUM_THREAD")
    plt.ylabel('efficiency')
    plt.savefig('report/efficiency/'+'iteration_'+str(ui_s[i]).split(".")[0]+'.png')
# plt.show()