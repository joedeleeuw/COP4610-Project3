all: fmod

fmod: fatmod.o filesystem.o
	g++ -Wall  -std=c++11 fatmod.o filesystem.o -o fmod

fatmod.o: fatmod.cpp
	g++ -c -Wall  --std=c++11 fatmod.cpp

filesystem.o: filesystem.cpp filesystem.h
	g++ -c -Wall -std=c++11 filesystem.cpp 	

clean: 
	rm -f *.o fmod
