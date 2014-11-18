#ifndef FILESYSTEM_H
#define FILESYSTEM_H

/*
	Contains code for calling out commands from the userspace (ls etc.)
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sys/mman.h>
#include "directory.h" // For directory handling

using namespace std;

struct FatEntry{

	uint32_t FATsecNum;
	uint32_t FATOffset;
	uint32_t nextCluster;
	uint32_t location;
	
};


class Filesystem 

{

public: 

	Filesystem(const char*);
	FatEntry findFatEntry(uint32_t);
	

	void init();
	void fsinfo();
	void openFile(string, string);
	void closeFile(string);
	void createFile(string);
	void readfromFile(string,unsigned int, unsigned int);
	void writetoFile(string, unsigned int, string);
	void removeFile(string);
	void changeDirectory(string);
	void listDirectory(string); // ls command
	void makeDirectory(string);
	void removeDirectory(string);
	void entrySize(string);
	void restoreFile();
	void findRootDirectory();
	void getFileSize();

	/*
		Parses the integer by taking in a posiion
	*/
	template<typename T, const T...validArgs>
	T parseInteger(unsigned char* const bitPosition)
	{
		T val = 0;

		for (size_t i =0; i < sizeof(T); i++)
		{
			val |= static_cast<T>(static_cast<T>(bitPosition[i]) << (i*8));
		}

		constexpr auto comparable_values = initializer_list<T>({validArgs...});

		if(comparable_values.size() == 0)
		{ 
			return val;
		}
		else 
		{
			for (auto &x: comparable_values)
			if (x == val)
				{
					return val;
				}
				//throw exception.
		}
		
		// We should never reach this point but supresses errors
		return val;

	}


//private:

	/* The cluster number of the first cluster of the root directory.*/
	uint32_t BPB_RootClus;
	/* the count of fAT data structures on the volime, only acceptable value should be 2 */
	uint8_t BPB_NuMFATs;
	/* only acceptable values: 512, 1024, 2048, 4096 */
	uint16_t BPB_BytsPerSec;
	/* only acceptable values: 1,2,4,8,16,32,64, 128*/
	uint8_t BPB_SecPerClus;
	/*32 bit count of sectors occupied by one FAT.*/
	uint32_t BPB_FATz32;
	/* total count of sectors on the volume.*/
	uint32_t BPB_TotSec32;
	/* Number of reserved sector on the volume */
	uint16_t BPB_ResvdSecCnt;
	/*Contains the last known free cluster count on the volume*/
	uint32_t FSI_Free_Count;
	
	// Custom storage
	uint32_t nextClusterNum;

	// FATEntr info
	FatEntry FATEntryRCluster;

	int FirstDataSector;
	int RootClusterSector;
	const char* fname; // file name
	int image_fd;
	unsigned fileSize; // Stores file size
	uint8_t *fdata;

	unordered_map< string, string> fileTable;
};



#endif
