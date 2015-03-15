CPPFLAGS=-g -O3 -Wall

eulercircuit: Graph.h main.o
	g++ $(CPPFLAGS) Graph.o main.o -o eulercircuit

main.o: main.cpp Graph.h
	g++ $(CPPFLAGS) -c main.cpp

clean:
	rm *.o -f
