#ifndef BIOSBLOCK_H
#define BIOSBLOCK_H

#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

// REFACTOR ME!!

// Struct for getting fsinfo
struct BPB_Summary {
    uint16_t BytesPerSector;
    uint8_t SectorsPerCluster;
    uint32_t TotalSectors;
    uint8_t NumberOfFATs;
    uint32_t SectorsPerFAT;
    uint32_t NumFreeSectors;
};

struct FSInfo {
    uint32_t LeadSig;           // 0, 4
    uint8_t Reserved1[480];     // 4, 480
    uint32_t StrucSig;          // 484, 4
    uint32_t FreeCount;         // 488, 4
    uint32_t NxtFree;           // 492, 4
    uint8_t Reserved2[12];      // 496, 12
    uint32_t TrailSig;          // 508, 4
} __attribute__((packed));

struct FATEntry {
    uint32_t FATSecNum;
    uint32_t FATOffset;
    uint32_t nextCluster;
    uint32_t location;
};

struct mByte {
    union {
        unsigned char buffer[8];
        uint32_t num;
    };
};

//~ ................................//

class BiosParameterBlock
{
    friend class FileSystem;
    friend class FATClusterChain;
    friend class FATDirectory;

    public:
        BiosParameterBlock(FILE* img);
        ~BiosParameterBlock();

        //~ Finders
        FATEntry FindFATEnt(uint32_t clusterNumber);

        // Locators
        uint32_t getRootDirectoryOffset();
        uint32_t firstSectorOfCluster(uint32_t clusterNumber);

        inline uint32_t getSectorOffset(uint32_t sector) { return sector * _BytsPerSec; }

        // Utility
        BPB_Summary getSummary();

    private:
        mByte* getAsByte(FILE* handle, int offset, int size) const;

        // Given Parameters
        uint16_t _BytsPerSec;
        uint8_t _SecPerClus;
        uint16_t _RsvdSecCnt;   // reserved sector count
        uint8_t _NumFATs;       // number of FATs
        uint32_t _TotSec32;
        uint32_t _FATSz32;      // FAT size?
        uint32_t _RootClus;     // Cluster number of the root directory BPB_RootClus(44, 4)
        uint16_t _RootEntCnt;
        uint16_t _FSInfo;

        // Derived Parameters
        uint32_t _RootDirSectors;
        uint32_t _FirstDataSector;
        uint32_t _DataSecCnt;
        uint32_t _CountOfClusters;

        // A bit of both.
        FSInfo _fsInfoEntry;
};

#endif