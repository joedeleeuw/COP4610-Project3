#include "filesystem.h"
#include <iostream>
#include <fstream>
using namespace std;


Filesystem::Filesystem(string name)
{
	fname = name;
	init();
}

void Filesystem::init()
{
	ofstream imageFile;
	imageFile.open(fname);
	if(!imageFile.is_open())
	{
		cout << "could not open file: " << fname << endl;
	}
	
}