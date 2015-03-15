CPPFLAGS=-g -O3

dijkstra: Graph.h main.o
	g++ $(CPPFLAGS) main.o -o dijkstra

main.o: main.cpp Graph.h
	g++ $(CPPFLAGS) -c main.cpp

clean:
	rm *.o -f
