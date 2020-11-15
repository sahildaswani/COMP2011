OBJS	= even.o main.o odd.o
PROG	= odd-even

$(PROG): $(OBJS)
	g++ -o odd-even $(OBJS)

main.o: main.cpp
	g++ -c main.cpp

odd.o: odd.cpp
	g++ -c odd.cpp

even.o: even.cpp
	g++ -c even.cpp


clean:
	/bin/rm -f *.o *~ $(PROG)
