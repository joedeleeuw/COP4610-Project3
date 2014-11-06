all: fatmod

fatmod: fatmod.o filesystem.o
	g++ -std=c++11 fatmod.o filesystem.o -o fatmod

fatmod.o: fatmod.cpp
	g++ -c --std=c++11 fatmod.cpp

filesystem.o: filesystem.cpp filesystem.h
	g++ -c -Wall -std=c++11 filesystem.cpp 	

clean: 
	rm -f *.o fatmod
