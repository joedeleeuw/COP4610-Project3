#ifndef FILESYSTEM_H
#define FILESYSTEM_H

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

using namespace std;

class Filesystem {

public: 

	Filesystem(const char*);
	void init();
	void fsinfo();
	void openFile(string, string);
	void closeFile(string);
	void createFile(string);
	void readfromFile(string,unsigned int, unsigned int);
	void writetoFile(string, unsigned int, string);
	void removeFile(string);
	void changeDirectory(string);
	void listDirectory(string);
	void makeDirectory(string);
	void removeDirectory(string);
	void entrySize(string);
	void restoreFile();

private:


	template<typename T, const T...validArgs>
	T parseInteger(const char* const bitPosition)
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

	int FirstDataSector;
	int RootClusterSector;
	const char* fname;
	int image_fd;
	char *fdata;

	unordered_map< string, string> fileTable;
};



#endif