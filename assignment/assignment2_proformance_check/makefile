SHELL=/bin/bash
i = 1000000#act as default value if no values passed to make
n = 4
all:
	make clean
	make run
clean:
	rm -f compute_simple compute_busywait compute_mutex_simple compute_mutex_overhead
run:
	g++ compute_simple.cpp -o compute_simple -lpthread
	g++ compute_busywait.cpp -o compute_busywait -lpthread
	g++ compute_mutex_simple.cpp -o compute_mutex_simple -lpthread
	g++ compute_mutex_overhead.cpp -o compute_mutex_overhead -lpthread
	./reportbash.sh
	python show_graph.py
