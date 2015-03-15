hotpotato: main.o random.o
	g++ -g main.o random.o -o hotpotato

main.o: main.cpp RevList.h random.h
	g++ -g -c main.cpp

random.o: random.cpp random.h
	g++ -g -c random.cpp

clean: 
	rm *.o -f
