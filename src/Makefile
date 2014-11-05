all: fatmod

fatmod: fatmod.o filesystem.o
	g++ fatmod.o filesystem.o -o fatmod

fatmod.o: fatmod.cpp
	g++ -c fatmod.cpp

filesystem.o: filesystem.cpp filesystem.h
	g++ -c filesystem.cpp 	

clean: 
	rm -f *.o fatmod
