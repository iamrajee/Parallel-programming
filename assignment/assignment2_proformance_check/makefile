SHELL=/bin/bash
reportlist=serial busywait mutex_simple mutex_overhead barrier_busywait_and_mutex barrier_condvar barrier_sem rwlock
all:
	make clean
	make run
clean:
	rm -f *.out
	rm -f report/efficiency/*.png
	$(foreach x,$(reportlist),rm -f report/$(x)/*.png rm -f report/$(x)/*.txt)
run:
	$(foreach x,$(reportlist),g++ compute_$(x).cpp -o compute_$(x).out -lpthread;)
	./reportbash.sh
