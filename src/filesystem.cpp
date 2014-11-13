#include "filesystem.h"
#include <iostream>
#include <fstream>
#include <sys/mman.h>
using namespace std;

/*
	Constructor for filesystem
*/
Filesystem::Filesystem(const char* name)
{
	fname = name;
	init();
}

/* Called by constructor to set up required fields
   for Filesystem
*/

/*
	Pass in the cluster number and it finds the FAT entry
*/
FatEntry Filesystem::findFatEntry(uint32_t clusterNumber)
{
	FatEntry entry;
	uint32_t fatOffset = clusterNumber * 4;

	div_t result;

	result = div(fatOffset,BPB_BytsPerSec);

	entry.FATsecNum = BPB_ResvdSecCnt + (fatOffset / BPB_BytsPerSec );
	entry.FATOffset = result.rem;

	return entry;
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
	BPB_NuMFATs = parseInteger<uint8_t,2>(fdata + 16 );
	BPB_BytsPerSec = parseInteger<uint16_t, 512, 1024, 2048, 4096>(fdata+ 11);
	BPB_SecPerClus = parseInteger<uint8_t, 1, 2, 4, 8, 16, 32, 64, 128> (fdata + 13);
	BPB_FATz32 = parseInteger<uint32_t>(fdata + 36);
	BPB_TotSec32 = parseInteger<uint32_t>(fdata + 32);
	FSI_Free_Count = parseInteger<uint32_t>(fdata + 488);

	FirstDataSector = BPB_ResvdSecCnt + (BPB_NuMFATs * BPB_FATz32);
	
	RootClusterSector = ((BPB_RootClus - 2) * BPB_SecPerClus) + FirstDataSector;
	fprintf(stdout,"First Data Sector %u ",RootClusterSector);
	
}

/*
	Lists directories out.
*/
void Filesystem::listDirectory(string dir_name)
{
	
}

/*
	Prints out file system information
*/
void Filesystem::fsinfo()
{
	fprintf(stdout,"%u Root Cluster\n",BPB_RootClus);
	fprintf(stdout,"%u Bytes per sector\n",BPB_BytsPerSec);
	fprintf(stdout,"%u Sectors per cluster\n",BPB_SecPerClus);
	fprintf(stdout,"%u Toal sectors\n",BPB_TotSec32);
	fprintf(stdout, "%u Number of FATs\n", BPB_NuMFATs);
	fprintf(stdout, "%u Sectors per FAT\n", BPB_FATz32);
}

void Filesystem::openFile(string file_name, string mode)
{

	fileTable[file_name] = mode;

}

