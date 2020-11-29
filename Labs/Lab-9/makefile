program: main.o lab9.o 
	g++ main.o lab9.o -o program

main.o: main.cpp lab9.h
	g++ -c main.cpp

lab8.o: lab9.cpp lab9.h
	g++ -c lab9.cpp

clean:
	rm *.o program