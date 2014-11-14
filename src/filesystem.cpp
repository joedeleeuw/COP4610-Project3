#include "filesystem.h"

// FATENTRY
/*
	Pass in the cluster number and it finds the FAT entry
	
	Example implementation -
	   FatEntry FATEntry = fs->findFatEntry(2);
    	cout << FATEntry.FATOffset << endl;
    	cout << FATEntry.FATsecNum << endl;
    	
    clusterNumber 2 should be the root
*/
FatEntry Filesystem::findFatEntry(uint32_t clusterNumber )
{
	FatEntry entry;
	uint32_t fatOffset = clusterNumber * 4;

	div_t result;

	result = div(fatOffset,BPB_BytsPerSec);
	/*FATsecNum is the sector number of the FAT sector that contains the entry 
	  for cluster N in the first FAT. If you want the sector number in the second 
	  FAT, you add FATSz to ThisFATSecNum; for the third FAT, you add 2*FATSz, 
	  and so on.
	*/
	entry.FATsecNum = BPB_ResvdSecCnt + (fatOffset / BPB_BytsPerSec );
	entry.FATOffset = result.rem;

	return entry;
}


// FILESYSTEM

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
void Filesystem::init()
{
	int offset = 0;
	unsigned len = 67108864; // Length of the file reading
	image_fd = open(fname, O_RDWR);
	if (image_fd < 0)
	{
		cout << "error while opening the file" << endl;
		exit(EXIT_FAILURE);
	}
	fdata = (uint8_t*)mmap(0, len, PROT_READ, MAP_PRIVATE, image_fd, offset);
	
	BPB_RootClus = parseInteger<uint32_t>(fdata + 44);
	BPB_NuMFATs = parseInteger<uint8_t,2>(fdata + 16 );
	BPB_BytsPerSec = parseInteger<uint16_t, 512, 1024, 2048, 4096>(fdata+ 11);
	BPB_SecPerClus = parseInteger<uint8_t, 1, 2, 4, 8, 16, 32, 64, 128> (fdata + 13);
	BPB_FATz32 = parseInteger<uint32_t>(fdata + 36);
	BPB_TotSec32 = parseInteger<uint32_t>(fdata + 32);
	FSI_Free_Count = parseInteger<uint32_t>(fdata + 488);
	BPB_ResvdSecCnt = parseInteger<uint32_t>(fdata + 14);

	FirstDataSector = BPB_ResvdSecCnt + (BPB_NuMFATs * BPB_FATz32);
	
	RootClusterSector = ((BPB_RootClus - 2) * BPB_SecPerClus) + FirstDataSector;
	fprintf(stdout,"First Data Sector %u ",RootClusterSector);
	
	// Gets the FATEntry information
	FATEntryRCluster = this->findFatEntry(RootClusterSector);
}

/*
		We go to ThisFASecNum and start reading it
		at offset ThisFATEntOffset. FAT will then give us
		the next cluster number in the directory or the End
		of Cluster Chain.
*/
void Filesystem::findRootDirectory()
{
	for(int i = 0; i < 32; i++){
		for(int v = 0; v < 11; v++)
		{
			cout << (char)*(fdata + (FirstDataSector * BPB_BytsPerSec) + i * 32 + v);
		}
		cout << endl;
	}
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