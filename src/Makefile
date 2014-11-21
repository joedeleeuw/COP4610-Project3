FLAGS = -Wall --std=c++11

all: fmod

fmod: fatmod.o filesystem.o directory.o file.o
	g++ $(FLAGS) fatmod.o filesystem.o file.o -o fmod

fatmod.o: fatmod.cpp
	g++ -c $(FLAGS) fatmod.cpp

filesystem.o: filesystem.cpp filesystem.h  
	g++ -c $(FLAGS) filesystem.cpp
	
file.o: file.cpp file.h
	g++ -c $(FLAGS) file.cpp

#directory.o: directory.cpp directory.h
#	g++ -c Wall -std=c++11 directory.cpp 	

# For cleaning the fmod
clean: 
	rm -f *.o fmod
