#ifndef FILE_H
#define FILE_H

#include <vector>
#include <string>

using namespace std;

class File: public Filesystem {

public:

    // Functions
    /*
        Gets the file data for the passed in cluster
    */
    
    void getFileData(int clusterToGet, uint8_t* fdata){
        
        int i = 0;
        // We loop through till temp becomes the end of the cluster
        while(i < 1000){
            int temp = parseInteger<uint8_t>(fdata + clusterToGet); 
            i += 8;
        
            cout << temp;
        }
        cout << endl;
        
    }

    // Variables
    vector<uint8_t> fileData;
    
private: 



};


#endif 