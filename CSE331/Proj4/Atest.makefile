CPPFLAGS=-g -O3

testree: Atest.o
	g++ $(CPPFLAGS) Atest.o -o testree

Atest.o: Atest.cpp Tree.h
	g++ $(CPPFLAGS) -c Atest.cpp

clean:
	rm *.o -f
