program: main.o todo.o given.o
	g++ -std=c++11 main.o todo.o given.o -o program

main.o: main.cpp todo.h given.h
	g++ -std=c++11 -c main.cpp

todo.o: todo.cpp todo.h given.h
	g++ -std=c++11 -c todo.cpp

given.o: given.cpp todo.h given.h
	g++ -std=c++11 -c given.cpp

clean:
	rm *.o program