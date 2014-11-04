#include "Filesystem.h"
#include <iostream>
#include <fstream>

Filesystem::Filesystem(string name){

	fname = name;
	init();
}

void Filesystem::init()
{
	ofstream imageFile;
	imageFile.open(fname);
	if (imageFile == NULL)
	{
		cout << "could not open file: " << fname << endl;
	}
	
	imageFile.close();
}