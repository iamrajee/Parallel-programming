all:
	make run
run:
	g++ race.cpp -o race -lpthread 
	./race