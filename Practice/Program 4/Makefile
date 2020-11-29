SRCS	= $(shell /bin/ls *.cpp)
PROGS	= $(SRCS:.cpp=)

all:	$(PROGS)

.cpp:
	g++ -std=c++11 -o $@ $<

clean:
	/bin/rm -f $(PROGS) *~
