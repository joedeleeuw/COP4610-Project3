#include "filesystem.h"
#include <iostream>
#include <fstream>
#include <sys/mman.h>
using namespace std;


Filesystem::Filesystem(const char* name)
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
	BPB_RootClus = parseInteger<uint32_t>(fdata + 44);
	BPB_NuMFATs = parseInteger<uint8_t, 2>(fdata + 16 );
	BPB_BytsPerSec = parseInteger<uint8_t, 512, 1024, 2048, 4096>(fdata+ 11);
	BPB_SecPerClus = parseInteger<uint8_t, 1, 2, 4, 8, 16, 32, 64, 128> (fdata + 13);
	BPB_FATz32 = parseInteger<uint32_t>(fdata + 36);
	BPB_TotSec32 = parseInteger<uint32_t>(fdata + 32);
}