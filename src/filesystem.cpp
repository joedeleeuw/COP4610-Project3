#include "filesystem.h"
#include "directory.h"
#include <vector>

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
	// Get the file size first
	getFileSize();
	
	int offset = 0;
	unsigned len = fileSize; // Length of the file reading
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
	
	BPB_ResvdSecCnt = parseInteger<uint32_t>(fdata + 14);

	FirstDataSector = BPB_ResvdSecCnt + (BPB_NuMFATs * BPB_FATz32);
	
	RootClusterSector = ((BPB_RootClus - 2) * BPB_SecPerClus) + FirstDataSector;
	fprintf(stdout,"First Data Sector %u ",RootClusterSector);
	
	// Gets the FATEntry information
	FATEntryRCluster = this->findFatEntry(RootClusterSector);

	
	uint32_t tempNextCluster = parseInteger<uint32_t>(fdata +FATEntryRCluster.FATOffset + FATEntryRCluster.FATsecNum);
	
	fprintf(stdout,"Next possible cluster value %u\n", tempNextCluster);
}

/*
	Finds the file passed in by the user in fatmod.cpp and
	stores the size in fileSize
*/
void Filesystem::getFileSize(){
  FILE * file;

  file = fopen (fname,"rb");
  // If file not found
  if (file==NULL){
  	perror ("Error opening file");
  }
  else
  {
    fseek(file, 0, SEEK_END); // Goes through the file
    fileSize = ftell(file);
    fclose (file); // Close file we don't need it anymore
  }
}

/*
		We go to ThisFASecNum and start reading it
		at offset ThisFATEntOffset. FAT will then give us
		the next cluster number in the directory or the End
		of Cluster Chain.
*/
void Filesystem::findRootDirectory()
{
	/*struct to hold file entries.*/
	int tempNextCluster;
	fileRecord record;
	std::vector<fileRecord> files;
	for(int i = 0; i < 100; i++)
		{
		
		// If it's a long file name
			if((int)*(fdata + (FirstDataSector * BPB_BytsPerSec) + i * 32 + 11) == 15)continue;	
			for (int j = 0; j < 11; j++)
			{
				//fprintf(stderr,"inner counter index: %d\n", j);
				//fprintf(stderr,"name byte value: %d, at index: %d ", nameByte,j); 	
				record.name[j]= parseInteger<uint8_t>(fdata + (FirstDataSector * BPB_BytsPerSec) + i * 32 + j);
				fprintf(stdout,"%c", (char)record.name[j]);
				
			}
			cout << " ";
			//fprintf(stderr,"outer counter index: %d\n", i);
			if ((int)record.name[1] < 10 )break;
			record.highCluster = parseInteger<uint16_t>(fdata + (FirstDataSector * BPB_BytsPerSec) + i * 32 + 12);
			record.lowCluster = parseInteger<uint16_t>(fdata + (FirstDataSector * BPB_BytsPerSec) + i * 32 + 14);
			//fprintf(stdout,"highCluster: %u ",record.highCluster);
			//fprintf(stdout,"lowCluster: %u",record.lowCluster);
			tempNextCluster = record.highCluster + record.lowCluster;
			fprintf(stdout,"next cluster location: %d", tempNextCluster);
			cout << endl;
			files.push_back(record); 
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

int Filesystem::binaryAdd(int firstBinary, int secondBinary)
{
	int result = 0;
	int i=0,remainder = 0,sum[20];
	while(firstBinary!=0||secondBinary!=0)
	{
         sum[i++] =  (firstBinary %10 + secondBinary %10 + remainder ) % 2;
         remainder = (firstBinary %10 + secondBinary %10 + remainder ) / 2;
         firstBinary = firstBinary/10;
         secondBinary = secondBinary/10;
    }

    if(remainder!=0)
         sum[i++] = remainder;

    --i;
    while(i>=0)result += sum[i--];

   return result;
}
