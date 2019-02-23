SHELL=/bin/bash
i = 1000000#act as default value if no values passed to make
n = 4
all:
	make clean
	make run
clean:
	rm -f compute_mutex compute compute_busywait 
run:
	g++ compute.cpp -o compute -lpthread
	g++ compute_busywait.cpp -o compute_busywait -lpthread
	g++ compute_mutex.cpp -o compute_mutex -lpthread
	g++ compute_mutex_overhead.cpp -o compute_mutex_overhead -lpthread
	# ./bash.sh $(i) $(n)
	./reportbash.sh