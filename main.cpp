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
	while(while input != "x")
    {
        
         input = handleCommand(argc, argv);
    }
    return 0;
}

char handleCommand(char *argv[], int argc)
{
    string userArg = argv[0];
    char type_of_command;
    
	 if (userArg.compare("fsinfo"))
	{

	}
	else if (userArg.compare("open") == 0)
	{
		
		{
			fprintf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("close") == 0)
	{
	
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("create") == 0)
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("read") == 0)
	{
		if (argc != 3)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("write") == 0)
	{
		if (argc != 3)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("rm")== 0)
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("cd") == 0)
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("ls") == 0)
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("mkdir") == 0)
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("rmdir") == 0)
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("size") == 0)
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("undelete") == 0)
	{

	}
    else if (userArg.compare("quit") == 0)
    {
        type_of_command = 'x'
    }

}

















