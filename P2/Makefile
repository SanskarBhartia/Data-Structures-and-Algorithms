CC=g++
DEV=-Wall -g -std=c++14
OPT=-O3 -std=c++14

JSON=json.hpp

all: consistentresultverification sortedverification timealgorithms

consistentresultverification: consistentresultverification.cxx
	g++ -std=c++14 consistentresultverification.cxx -o consistentresultverification

sortedverification: sortedverification.cxx
	g++ -std=c++14 sortedverification.cxx -o sortedverification

timealgorithms: timealgorithms.cxx insertionsort.o mergesort.o quicksort.o
	g++ -std=c++14 timealgorithms.cxx insertionsort.o mergesort.o quicksort.o -o timealgorithms

insertionsort.o: insertionsort.cpp insertionsort.h json.hpp
	g++ -std=c++14 -c insertionsort.cpp

mergesort.o: mergesort.cpp mergesort.h json.hpp
	g++ -std=c++14 -c mergesort.cpp

quicksort.o: quicksort.cpp quicksort.h json.hpp
	g++ -std=c++14 -c quicksort.cpp

clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f consistentresultverification
	rm -f sortedverification
	rm -f timealgorithms
