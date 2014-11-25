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
#include <algorithm> // For transform
#include <map>

// Custom classes
#include "file.h"
#include "directory.h" // For directory handling

using namespace std;

// Forward declaration (so Filesystem knows about File class)

struct FatEntry{

	uint32_t FATsecNum;
	uint32_t FATOffset;
	uint32_t nextCluster;
	uint32_t location;
	
};


class Filesystem : public File

{
	friend class File;
	
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
	void removeDirectory(string);
	void listDirectory(string); // ls command
	void makeDirectory(string);
	int directoryExists(string, int type = 0);
	bool directoryExistsAndChangeTo(string);
	void entrySize(string);
	void restoreFile();
	void findRootDirectory();
	void getFileSize();
	void findDirectoriesForCluster(int, int);
	void getRootDirectoryContents(int);
	bool getDirectoryClusterNumber(string);
	void readFilesystemforFile(int,string);
	void PrintCurrentDirectory(int directoryDataSector, bool store = false);
	int findFirstSectorOfCluster(int clusterIndex);
	string convertCharNameToString(unsigned int index, int numValuesToAddTogether);
	void readEntireFilesystem(int currentCluster);
	void openImage();
	int binaryAdd(int, int);
	void displayVectorContents();
	void closeImage();
	bool verifyEmptyDirectory(int);
	void Read(string,int,int);
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
	
	// File handler
	File fileHandler;
	//combination of high and low cluster for an individual record.
	
	// Maps what we've read in
	map<int, int> valuesStoredMap;
	
	int FirstDataSector;
	int bytesPerCluster;
	unsigned int currentClusterLocation;
	int firstSectorClusterRD;
	int secondSectorClusterRD;
	int RootClusterSector;
	const char* fname; // file name
	int image_fd;
	string filetoRemove;
	unsigned fileSize; // Stores file size
	uint8_t *fdata;
	string workingDirectory;
	string previousWorkingDirectory;
	unsigned int lastIFileLocation; // Contains the index value of the last file we read in
	FILE * imageFile;								// so we can check if a file exists later on
	int dataSector;
	//index for current file found in directoryExists
	int currentFileIndex;
	vector<fileRecord> files;
	vector<fileRecord> currentDir;
	map<int, int> fileTable;
};

#endif
