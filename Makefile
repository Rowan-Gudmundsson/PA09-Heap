CPP_FLAGS = -Wall -O2 -std=c++98
all: test testpq sim

sim: ossim PriorityQueue
	g++ $(CPP_FLAGS) -o ossim ossim.o PriorityQueue.o

ossim: ossim.cpp
	g++ $(CPP_FLAGS) -c ossim.cpp

test: test11 Heap
	g++ $(CPP_FLAGS) -o test11 test11.o Heap.o

testpq: test11pq PriorityQueue
	g++ $(CPP_FLAGS) -o test11pq test11pq.o PriorityQueue.o Heap.o

PriorityQueue: PriorityQueue.cpp PriorityQueue.h Heap.h
	g++ $(CPP_FLAGS) -c PriorityQueue.cpp

test11pq: test11pq.cpp
	g++ $(CPP_FLAGS) -c test11pq.cpp

test11: test11.cpp
	g++ $(CPP_FLAGS) -c test11.cpp

Heap: Heap.cpp Heap.h
	g++ $(CPP_FLAGS) -c Heap.cpp
