CC = g++
CFLAGS = -Wall -c -std=c++11 -pthread -g

all: fsm

fsm: main.o components.o xml.o utils.o variables.o
	$(CC) -std=c++11 -g -pthread main.o tranzition.o module.o fsm.o parser.o pugixml.o stringparser.o utils.o

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


clean:
	rm -f *.o
	rm -f *.out