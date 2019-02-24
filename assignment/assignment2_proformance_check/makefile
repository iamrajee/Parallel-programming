SHELL=/bin/bash
all:
	make clean
	make run
clean:
	rm -f compute_simple compute_busywait compute_mutex_simple compute_mutex_overhead
	rm -f report/simple/*.png
	rm -f report/simple/*.txt
	rm -f report/busywait/*.png
	rm -f report/busywait/*.txt
	rm -f report/mutex_simple/*.png
	rm -f report/mutex_simple/*.txt
	rm -f report/mutex_overhead/*.png
	rm -f report/mutex_overhead/*.txt
run:
	g++ compute_simple.cpp -o compute_simple -lpthread
	g++ compute_busywait.cpp -o compute_busywait -lpthread
	g++ compute_mutex_simple.cpp -o compute_mutex_simple -lpthread
	g++ compute_mutex_overhead.cpp -o compute_mutex_overhead -lpthread
	./reportbash.sh
