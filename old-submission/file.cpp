#include "file.h"

/*
Converts the string to uppercase and trims the proper character
*/
string File::normalizeToUppercase(string valueToNormalize, char characterToRemove){
    
    //cout << "first character of User input String " << (char)valueToNormalize[0] << endl;
    //cout << "first character of User input String " << (char)valueToNormalize[1] << endl;
    // Trim the character to remove if one is passed in
	  
      //if(valueToNormalize[0] != '.' || valueToNormalize[1] != '.'){
          valueToNormalize.erase(remove(valueToNormalize.begin(), valueToNormalize.end(), characterToRemove), valueToNormalize.end());   
      //}
      
		
		// Uppercase record
		if(valueToNormalize[0] != '.' || valueToNormalize[1] != '.')
    transform(valueToNormalize.begin(), valueToNormalize.end(), valueToNormalize.begin(),::toupper);
		
		return valueToNormalize;
}