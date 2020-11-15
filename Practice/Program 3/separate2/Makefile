OBJS	= even.o main.o odd.o
PROG	= odd-even

$(PROG): $(OBJS)
	g++ -o odd-even $(OBJS)

main.o: main.cpp global.h my_include.h
	g++ -c main.cpp

odd.o: odd.cpp extern.h my_include.h
	g++ -c odd.cpp

even.o: even.cpp extern.h my_include.h
	g++ -c even.cpp


clean:
	/bin/rm -f *.o *~ $(PROG)
