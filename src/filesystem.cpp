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
	workingDirectory = "Root Directory";
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

	bytesPerCluster = BPB_BytsPerSec * BPB_SecPerClus;
	
	// Now we read in the root directory
	findRootDirectory();
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

void Filesystem::findRootDirectory()
{
	FirstDataSector = BPB_ResvdSecCnt + (BPB_NuMFATs * BPB_FATz32);
	firstSectorClusterRD = findFirstSectorOfCluster(BPB_RootClus);
	//fprintf(stdout,"First Sector of First RD cluster %u ",firstSectorClusterRD);
	
	// Gets the FATEntry for the location of the next Root Directory Cluster
	FATEntryRCluster = this->findFatEntry(2);

	//The second cluster number of the root directory. 
	uint32_t secondRootCluster = parseInteger<uint32_t>(fdata + FATEntryRCluster.FATOffset + FATEntryRCluster.FATsecNum * BPB_BytsPerSec);
	//fprintf(stdout,"Next RD cluster value %x\n", secondRootCluster);
	

	//First sector of the second cluster of the root directory.
	secondSectorClusterRD = findFirstSectorOfCluster(secondRootCluster);
	// Gets the FATEntry for the location of the next Root Directory Cluster(EOC)
	//FatEntry temp = this->findFatEntry(secondRootCluster);

	//uint32_t EoC = parseInteger<uint32_t>(fdata + temp.FATOffset + temp.FATsecNum * BPB_BytsPerSec);
	//fprintf(stdout,"EOC Marker hit %x\n", EoC);
	getRootDirectoryContents(firstSectorClusterRD);
	getRootDirectoryContents(secondSectorClusterRD);

}

/*
	Finds the first sector based on the cluster we pass in
*/
int Filesystem::findFirstSectorOfCluster(int clusterIndex){
	// Contains the local sector we're reading in NYI
	return ((clusterIndex - 2) * BPB_SecPerClus) + FirstDataSector;
}

/*Pass this function a cluster number, it will find the first data sector for the cluster
as well as check to see if there is another cluster associated with it in the FAT
Call function to read from data sector in this function.
*/

void Filesystem::findDirectoriesForCluster(int clusterIndex)
{
	
	int dataSector;
	uint32_t nextCluster;
	FirstDataSector = BPB_ResvdSecCnt + (BPB_NuMFATs * BPB_FATz32);
	while(clusterIndex != 268435455)
	{
		
		dataSector = findFirstSectorOfCluster(clusterIndex);
		// Gets the FATEntry for the location of the next directory cluster
		FATEntryRCluster = this->findFatEntry(clusterIndex);
		//The second cluster number of the root directory. 
		nextCluster = parseInteger<uint32_t>(fdata + FATEntryRCluster.FATOffset + FATEntryRCluster.FATsecNum * BPB_BytsPerSec);
		clusterIndex = nextCluster;
		//this will be called for as many additional clusters there are for a directory.
		PrintCurrentDirectory(dataSector);
	}	
	
	fprintf(stdout,"EOC Marker hit %x\n", clusterIndex);

	
}

/*
	Changes the directory and checks if it exists.
	
	TODO NYI - Need to check if directory would be transformed into version of what
	we are comparing it against, SEE FAT documentation.
*/
void Filesystem::changeDirectory(string directoryName)
{
	// If the directory exists (pretty self explanatory)
	if(directoryExists(directoryName))
	{
		cout << "Working directory changed to " << directoryName  << endl;
		workingDirectory = directoryName;
	}
	else
	{
		cout << "Directory " << directoryName << " was not found" << endl;
		return;
	}
	
		//cout <<"Vector Size: " <<files.size() << endl;
}
/*
	Lists directories out.
*/
void Filesystem::listDirectory(string dir_name)
{
	getDirectoryClusterNumber(dir_name);
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


void Filesystem::getRootDirectoryContents(int FirstDataSector)
{

	 
	fileRecord record;
	
	cout << "cluster sector"<<FirstDataSector << endl;
	//number of records, had to divide by 32, because we were reading too far.
	for(int i = 0; i < BPB_BytsPerSec/32; i++)
		{
		
		// If it's a long file name, skip over the record.
			if((int)*(fdata + (FirstDataSector * BPB_BytsPerSec) + i * 32 + 11) == 15)continue;	
			//if the record is empty, then break, because we have reached the end of the sector, or cluster? does it really matter?
			if((int)*(fdata + (FirstDataSector * BPB_BytsPerSec) + i * 32 + 0) == 0)break;	
			for (int j = 0; j < 11; j++)
			{
				//fprintf(stderr,"inner counter index: %d\n", j);
				//fprintf(stderr,"name byte value: %d, at index: %d ", nameByte,j); 	
				record.name[j] = (char)parseInteger<uint8_t>(fdata + (FirstDataSector * BPB_BytsPerSec) + i * 32 + j);
				fprintf(stdout,"%c", record.name[j]);
				
			}
			cout << " ";
			//fprintf(stderr,"outer counter index: %d\n", i);
			if ((int)record.name[1] < 10 )continue;
			
			//refer to the filesystem spec instead of the dumb slides, the offsets were wrong, and were ORing time stamps.
			record.attr = parseInteger<uint8_t>(fdata + (FirstDataSector * BPB_BytsPerSec) + i * 32 + 11);
			record.highCluster = parseInteger<uint16_t>(fdata + (FirstDataSector * BPB_BytsPerSec) + i * 32 + 20);
			record.lowCluster = parseInteger<uint16_t>(fdata + (FirstDataSector * BPB_BytsPerSec) + i * 32 + 26);
			
			//we shift 16 bits for the or, because we are making room foor the bits in lowCluster for the addition(draw it out kid)
			record.highCluster <<= 16;
			record.fClusterLocation = record.highCluster | record.lowCluster;
			
			// Gets the number that we need to pass into findFirstSectorOfCluster
			//fClusterLocation = record.highCluster + record.lowCluster;
			
			// Get the sector for the contents of the file to read from it
			//int sectorToPass = findFirstSectorOfCluster(record.fClusterLocation);
			// Reads the file data
			//fileHandler.getFileData(sectorToPass, fdata);
			
			fprintf(stdout,"Entry Type: %x ", record.attr);
			fprintf(stdout,"next cluster location: %d", record.fClusterLocation);
			
			cout << endl;
			record.currentFolder = workingDirectory;
			files.push_back(record); 
		}

}

//this function gets the cluster number for a directory from the vector, and then calls the function to get the data sector and future clusters for the sectors.
void Filesystem::getDirectoryClusterNumber(string directory)
{
	string recordName;
	for(unsigned int i = 0; i < files.size(); i++)
		{
			if((int)files[i].attr == 16 )
			{
				// Reset recordName
				recordName = "";
				
				for(int j = 0; j < 11; j++)
				{
					char readInChar = files[i].name[j];
					if(readInChar != ' ')
						recordName.push_back(readInChar);
				}	
				
				// Trims and converts to uppercase the record and directoryname
				recordName = normalizeToUppercase(recordName, ' ');
				directory = normalizeToUppercase(directory, '.');
				
				if(recordName == directory)
				{
					findDirectoriesForCluster(files[i].fClusterLocation);
					break;
				}
			}
	}

}
/*This function takes in the data sector from a directory cluster as an argument, and then prints out the records in that cluster
this funciton is called n amount of times, where n is the amount of clusters associated with a directory.*/
void Filesystem::PrintCurrentDirectory(int directoryDataSector)
{
	fileRecord dirRecord;
	for(int i = 0; i < BPB_BytsPerSec/32; i++)
		{
		
		// If it's a long file name, skip over the record.
			if((int)*(fdata + (directoryDataSector * BPB_BytsPerSec) + i * 32 + 11) == 15)continue;	
			//if the record is empty, then break, because we have reached the end of the sector, or cluster? does it really matter?
			if((int)*(fdata + (directoryDataSector * BPB_BytsPerSec) + i * 32 + 0) == 0)break;	
			for (int j = 0; j < 11; j++)
			{
				//fprintf(stderr,"inner counter index: %d\n", j);
				//fprintf(stderr,"name byte value: %d, at index: %d ", nameByte,j); 	
				dirRecord.name[j] = (char)parseInteger<uint8_t>(fdata + (directoryDataSector * BPB_BytsPerSec) + i * 32 + j);
				fprintf(stdout,"%c", dirRecord.name[j]);
				
			}
			cout << " ";
			//fprintf(stderr,"outer counter index: %d\n", i);
			if ((int)dirRecord.name[1] < 10 )continue;
			
			//refer to the filesystem spec instead of the dumb slides, the offsets were wrong, and were ORing time stamps.
			dirRecord.attr = parseInteger<uint8_t>(fdata + (directoryDataSector * BPB_BytsPerSec) + i * 32 + 11);
			dirRecord.highCluster = parseInteger<uint16_t>(fdata + (directoryDataSector * BPB_BytsPerSec) + i * 32 + 20);
			dirRecord.lowCluster = parseInteger<uint16_t>(fdata + (directoryDataSector * BPB_BytsPerSec) + i * 32 + 26);
			
			//we shift 16 bits for the or, because we are making room foor the bits in lowCluster for the addition(draw it out kid)
			dirRecord.highCluster <<= 16;
			dirRecord.fClusterLocation = dirRecord.highCluster | dirRecord.lowCluster;
			files.push_back(dirRecord);
			
			cout << endl;
	}
}

/*
	Checks if the directory exists in the current working directory
*/
bool Filesystem::directoryExists(string directoryName){
	bool dirFound = false;
	/*
		We must note that the directory name the user enters may just be RED 
		(no spaces) but the stored value may contain spaces so we must know when
		to ignore that.
	*/
	for(unsigned int i = 0; i < files.size(); i++)
	{
		string recordName;
		
		// Go through file name one character at a time
		// and add its name to the recordName
		for(int j = 0; j < 11; j++)
		{
			char readInChar = files[i].name[j];
			recordName.push_back(readInChar);
		}	

		// cout << "Record Name: " << recordName << endl;
		// cout << "Record Name: " << recordName.length() << endl;
		
		// //fprintf()
		// cout << "Directory Name: " << directoryName << endl;
		// cout << "Directory Name: " << directoryName.length() << endl;

		// Trims and converts to uppercase the record and directoryname
		recordName = normalizeToUppercase(recordName, ' ');
		directoryName = normalizeToUppercase(directoryName, '.');
		
		if(recordName == directoryName && files[i].attr == 16 )
		{
			dirFound = true; // Directories found
			break;
		}
	
	}
	return dirFound;
}

/*
    Creates a directory with the passed in directoryName,
    also checks if the directory already exists in the current
    working directory
*/
void Filesystem::makeDirectory(string directoryName){
    // Check if the directory already exists
    if(directoryExists(directoryName)){
    	cout << "The directory " << directoryName << " already exists." << endl;
    }
    // Otherwise we create the directory
    else{
    	
    }
}