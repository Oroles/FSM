libs: module tranzition fsm

module:
	g++ -std=c++11 -c -pthread module.cpp
	ar rvs module.a module.o

tranzition:
	g++ -std=c++11 -c -pthread tranzition.cpp
	ar rvs tranzition.a tranzition.o

fsm:
	g++ -std=c++11 -c -pthread fsm.cpp
	ar rvs fsm.a fsm.o

clean:
	rm *.o
	rm *.a