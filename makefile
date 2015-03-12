CC = g++-4.9
CFLAGS = -Wall -c -std=c++11 -pthread

all: fsm

debug: CFLAGS += -DDEBUG -g
debug: fsm

release: CFLAGS += -O3
release: fsm

fsm: main.o components.o xml.o utils.o variables.o expressions.o
	$(CC) -std=c++11 -g -pthread main.o tranzition.o module.o fsm.o expression.o chan.o clock.o parser.o pugixml.o stringparser.o utils.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

components.o:
	$(CC) $(CFLAGS) components/fsm.cpp components/module.cpp components/tranzition.cpp

xml.o:
	$(CC) $(CFLAGS) pugixml/*.cpp

utils.o:
	$(CC) $(CFLAGS) utils/*.cpp

variables.o:
	$(CC) $(CFLAGS) components/variables/*.cpp

expressions.o:
	$(CC) $(CFLAGS) components/expressions/*.cpp

clean:
	rm -f *.o
	rm -f *.out