#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <fstream>
#include <cstdlib>
#include <uniistd.h>
#include <stdio.h>

void handleCommand(char*[], int);

int main (int argc, char* argv[])
{
	bool input = true;
	handleCommand(argc, argv);
	return 0;
}

void handleCommand(char *argv[], int argc)
{
    string userArg = argv[0];
    
    if (argc == 0)
    {
        printf("%s\n","not enoguh arguments supplied");
        
    }
	else if (userArg.compare("fsinfo"))
	{

	}
	else if (userArg.compare("open"))
	{
		if (argc != 2)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("close"))
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("create"))
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("read"))
	{
		if (argc != 3)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("write"))
	{
		if (argc != 3)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("rm"))
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("cd"))
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("ls"))
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("mkdir"))
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("rmdir"))
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("size"))
	{
		if (argc != 1)
		{
			printf("%s\n", "wrong amount of arguments supplied");
		}
	}
	else if (userArg.compare("undelete"))
	{

	} 

}