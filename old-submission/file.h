#ifndef FILE_H
#define FILE_H

#include <vector>
#include <string>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

class File {
    // Gives File access to Filesystem private variables, not really needed
    friend class Filesystem;
    
public:
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

    // Functions
    /*
        Gets the file data for the passed in cluster
    */
    
    void getFileData(int clusterToGet, uint8_t* fdata){
        
        int i = 0;
        // We loop through till temp becomes the end of the cluster
        while(i < 1000){
            // UNCOMMENT ME
            int temp = parseInteger<uint8_t>(fdata + clusterToGet); 
            i += 8;
        
            cout << temp;
        }
        cout << endl;
        
    }
    
	string normalizeToUppercase(string valueToNormalize, char characterToRemove = '?');

    // Variables
    vector<uint8_t> fileData;
    
private: 



};


#endif 