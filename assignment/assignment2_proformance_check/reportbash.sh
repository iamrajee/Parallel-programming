echo ""
echo "================================================================================"
echo "|"
echo -n "|                  1) Making reports..."

#define your parameter here
iter_list=(10 100 1000 10000 100000 1000000 10000000)
thread_list=(1 2 4 6 8 10)
reportlist=(busywait mutex_simple mutex_overhead barrier_busywait_and_mutex barrier_condvar barrier_sem rwlock)
repeat=5 #How many times should i run one method and then took avg


#---------------for serial computation-------------------------#
q=serial
for i in ${iter_list[*]}
do
	echo -n "" >> report/${q}/${q}.txt
	echo -n "iters, NUM_THREAD, (value, Execution time) repetaion times pairs = [" ${i} ", 1">> report/${q}/${q}.txt
	COUNTER=0
	while [  $COUNTER -lt ${repeat} ];
	do
		./compute_${q}.out ${i} 1 >> report/${q}/${q}.txt #since no of thread passed is = 1. Hence serial
		let COUNTER=COUNTER+1
	done
	echo -e "]" >> report/${q}/${q}.txt
done
# echo "" >> report/${q}/${q}.txt



#---------------for parallel computation-------------------------#
for p in ${reportlist[*]}
do
	echo -n "" > report/${p}/${p}.txt
done

for i in ${iter_list[*]}
do
	for n in ${thread_list[*]}
	do
		for p in ${reportlist[*]}
		do
			echo -n "" >> report/${p}/${p}.txt
			echo -n "iters, NUM_THREAD, (value, Execution time) repetaion times pairs = [" ${i} ", " ${n}>> report/${p}/${p}.txt
			COUNTER=0
			while [  $COUNTER -lt ${repeat} ];
			do
				./compute_${p}.out ${i} ${n} >> report/${p}/${p}.txt
				let COUNTER=COUNTER+1
			done
			echo -e "]" >> report/${p}/${p}.txt
		done
    done
	echo -n "."
done

echo ""
echo "|                     > Report successfully create in /report folder"
echo -n "|                  2) Creating graph wait..."

reportlist=(serial busywait mutex_simple mutex_overhead barrier_busywait_and_mutex barrier_condvar barrier_sem rwlock)
#---------------for both serial and parallel computation-------------------------#
for p in ${reportlist[*]}
do
	python show_graph.py report/${p}/${p}.txt
	echo -n "."
done
python2 compare_various_method.py report/${q}/${q}.txt
echo ""
echo "|                     > Graph successfully create in /report folder"
lscpu > report/Hardware_specification.txt
echo "|                  3) Created Hardware_specification in /report folder"
echo "|"
echo "================================================================================"
echo ""