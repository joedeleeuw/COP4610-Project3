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
	int offset = 0;
	unsigned len = 4096;
	image_fd = open(fname, O_RDWR);
	if (image_fd < 0)
	{
		cout << "error while opening the file" << endl;
		exit(EXIT_FAILURE);
	}
	fdata = (char *)mmap(0, len, PROT_READ, MAP_PRIVATE, image_fd, offset);
	BPB_RootClus = parseInteger<uint32_t>(fdata);

}