#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include "filesystem.h"
#define FOUT stdout 

using namespace std;
char handleCommand(int,char*[]);

int main (int argc, char* argv[])
{
	char input = '\0';
	if (argc < 2)
	{
		fprintf(FOUT, "%s\n", "No image file was provided");
		fprintf(FOUT, "%s\n", "Usage: 'fatmod <image_name>'");
		exit(0);
	}
	
	Filesystem fs(argv[1]);
	
	while (input != 'x')
    {
      input = handleCommand(argc, argv);
    }
    
    return 0;
}

char handleCommand(int argc,char *argv[])
{
    char type_of_command;
   	int i = 0; 
    string userCommand;
    string commandBuffer;
    getline(cin, userCommand);
    string userArgs[5];
    istringstream commandStream(userCommand);
    while( commandStream >> commandBuffer)
    {
    	userArgs[i] = commandBuffer;
    	i++;
    }
   
    if (userArgs[0].compare("fsinfo") == 0)
	{
		
	}
	else if (userArgs[0].compare("open") == 0)
	{
	 	if (userArgs[1] == "")
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("close") == 0)
	{
		if (userArgs[1] == "")
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("create") == 0)
	{
		if (userArgs[1] == "")
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("read") == 0)
	{
		if (userArgs[3] == "")		
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("write") == 0)
	{
		if (userArgs[3] == "")
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("rm")== 0)
	{
		if (userArgs[1] == "")
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("cd") == 0)
	{
		if (userArgs[1] == "")
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("ls") == 0)
	{
		if (userArgs[1] == "")
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("mkdir") == 0)
	{
		if (userArgs[1] == "")
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("rmdir") == 0)
	{
		if (userArgs[1] == "")
		printf("%s\n", "wrong amount of arguments supplied");
	}
	else if (userArgs[0].compare("size") == 0)
	{
		if (userArgs[1] == "")
		printf("%s\n", "wrong amount of arguments supplied");
	}
	else if (userArgs[0].compare("undelete") == 0)
	{

	}
    else if (userArgs[0].compare("quit") == 0)
    {
        type_of_command = 'x';
    	return type_of_command;
    }

}


















