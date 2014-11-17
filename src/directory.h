#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

struct fileRecord {

uint8_t name[10];
uint8_t attr;
uint16_t highCluster;
uint16_t lowCluster;
uint32_t fileSize;

};

class Directory{
    
public:



private:

    
};

#endif