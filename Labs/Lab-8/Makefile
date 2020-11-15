# Write the make file here
bingo: main.o lab8.o 
	g++ main.o lab8.o -o bingo

main.o: main.cpp lab8.h
	g++ -c main.cpp

lab8.o: lab8.cpp lab8.h
	g++ -c lab8.cpp

clean:
	rm *.o bingo