#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>

struct twoInts
{
	int firstInt;
	int secondInt;
}myInts;

struct twoChars
{
	char firstChar;
	char secondChar;

}myChars;

class Filesystem {

public: 

Filesystem(string filename);
void init();


};

private:

string fname;
FILE* image;

#endif
