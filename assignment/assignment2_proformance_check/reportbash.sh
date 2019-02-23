echo ""
echo "--------------------------------------------------------------------------"
echo -n "Making reports..."
iter_list=(10 100 1000 10000 100000 1000000 10000000)
thread_list=(1 2 4 10 20 50 100)

echo -n "" > report/mutex/mutex_simple.txt
for i in ${iter_list[*]}
do
	for n in ${thread_list[*]}
	do
		echo -n "iters, NUM_THREAD, value, Execution time = [" ${i} ", " ${n} ", ">> report/simple/simple.txt
		echo -n "iters, NUM_THREAD, value, Execution time = [" ${i} ", " ${n} ", ">> report/busywait/busywait.txt
        echo -n "iters, NUM_THREAD, value, Execution time = [" ${i} ", " ${n} ", ">> report/mutex/mutex_simple.txt
		echo -n "iters, NUM_THREAD, value, Execution time = [" ${i} ", " ${n} ", ">> report/mutex/mutex_overhead.txt
		./compute_mutex_simple ${i} ${n} >> report/simple/simple.txt
		./compute_mutex_overhead ${i} ${n} >> report/busywait/busywait.txt
		./compute_mutex_simple ${i} ${n} >> report/mutex/mutex_simple.txt
		./compute_mutex_overhead ${i} ${n} >> report/mutex/mutex_overhead.txt
    done
	echo -n "."
done
echo ""
echo "Report successfully create in /report folder"
echo "--------------------------------------------------------------------------"
echo ""
