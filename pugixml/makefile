libs: pugixml parser

pugixml:
	g++ -std=c++11 -c pugixml.cpp
	ar rvs pugixml.a pugixml.o

parser:
	g++ -std=c++11 -c parser.cpp
	ar rvs parser.a parser.o

clean:
	rm *.a
	rm *.o
