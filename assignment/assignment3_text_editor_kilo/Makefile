SHELL=/bin/bash
reportlist=kilo_threaded kilo4_non-threaded

CC=g++
CCFLAGS=-Wall -Wextra -pedantic -g -std=c++17
LIBS=-lpthread
all:
	make clean
	make compile
	make run

clean:
		rm -rf *.out

compile:
	$(foreach x,$(reportlist),$(CC) $(x).cpp -o $(x).out $(CCFLAGS) $(LIBS);)
run:
	./bash.sh
threaded:
	./bash_threaded.sh
non-threaded:
	./bash_non-threaded.sh