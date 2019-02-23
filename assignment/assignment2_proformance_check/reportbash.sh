iter_list=(10 100 1000 10000 100000 1000000 10000000)
thread_list=(1 2 4 10 20 50 100)

echo "" > report/mutex/mutex_simple.txt
for i in ${iter_list[*]}
do
	for n in ${thread_list[*]}
	do
        echo "iters:" ${i} ${n} >> report/mutex/mutex_simple.txt
		./compute_mutex ${i} ${n} >> report/mutex/mutex_simple.txt
        echo "" >> report/mutex/mutex_simple.txt
    done
done
echo ""
echo ""
echo ""