#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <fstream>
#include <cstdlib>
#include <uniistd.h>
#include <stdio.h>
#include "Filesystem.h"
#define FOUT sdout 
void handleCommand(char*[], int);

int main (int argc, char* argv[])
{
	bool input = true;
	char input = '\0';
	if (argc < 2)
	{
		fprintf(FOUT, "%s\n", "No image file was provided");
		fprintf(FOUT, "%s\n", "Usage: 'fatmod <image_name>'");
		exit(0);
	}
	
	Filesystem fs(argv[1]);
	
	while(while input != "x")
    {
      input = handleCommand(argc, argv);
    }
    
    return 0;
}

char handleCommand(char *argv[], int argc)
{
    char type_of_command;
    string userCommand;
    string commandBuffer;
    getline(cin, userCommand);
	string userArgs[5];
    stringstream commandStream(userCommand);
    
    for(int i=0; i < 5; i++)
    {
    	commandStream >> commandBuffer
    	userArgs[i] = commandBuffer;
    }
    
    if (userArgs[0].compare("fsinfo") == 0)
	{
		
	}
	else if (userArgs[0].compare("open") == 0)
	{
	 	if (userArgs[2] == NULL)
		fprintf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("close") == 0)
	{
		if (userArgs[1] == NULL)
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("create") == 0)
	{
		if (userArgs[1] == NULL)
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("read") == 0)
	{
		if (userArgs[3] == NULL)		
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("write") == 0)
	{
		if (userArgs[3] == NULL)
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("rm")== 0)
	{
		if (userArgs[1] == NULL)
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("cd") == 0)
	{
		if (userArgs[1] == NULL)
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("ls") == 0)
	{
		if (userArgs[1] == NULL)
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("mkdir") == 0)
	{
		if (userArgs[1] == NULL)
		printf("%s\n", "wrong amount of arguments supplied");
		
	}
	else if (userArgs[0].compare("rmdir") == 0)
	{
		if (userArgs[1] == NULL)
		printf("%s\n", "wrong amount of arguments supplied");
	}
	else if (userArgs[0].compare("size") == 0)
	{
		if (userArgs[1] == NULL)
		printf("%s\n", "wrong amount of arguments supplied");
	}
	else if (userArgs[0].compare("undelete") == 0)
	{

	}
    else if (userArgs[0].compare("quit") == 0)
    {
        type_of_command = 'x'
    	return type_of_command;
    }

}

















