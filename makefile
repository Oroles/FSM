CC = g++
CFLAGS = -Wall -c -std=c++11

all: fsm

fsm: main.o components.o xml.o
	$(CC) -std=c++11 main.o tranzition.o module.o fsm.o parser.o pugixml.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

components.o:
	$(CC) $(CFLAGS) components/fsm.cpp components/module.cpp components/tranzition.cpp

xml.o:
	$(CC) $(CFLAGS) pugixml/*.cpp


clean:
	rm -f *.o
	rm -f *.out