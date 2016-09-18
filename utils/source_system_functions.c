
/* //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * 
 * NAME: System Functions Library
 * AUTHOR: Ronald Bohn
 * PURPOSE: A set of functions which serve as revised system calls that are easier to use and manage.
 * STATUS: All of the functions are tested and work, but there are very few present. I would like to add more as
 * I develop a need for them.
 *
 *///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "header_system_functions.h"
#include "useful_definitions.h"


//FUNCTION: int system_functions_constructor
//PURPOSE: Initializes a number of variables needed for the rest of the functions in the library.
//STATUS: Complete and tested. This may get bigger and more complex as more functions are added, but
//for now it serves it's purpose just fine.
int system_functions_constructed = 0;
char* system_functions_wd;
size_t system_functions_wdSize;

int system_functions_constructor()
{
	system_functions_wd = malloc(sizeof(char)*SYSTEM_FUNCTIONS_PATH_SIZE);
	system_functions_wdSize = sizeof(char)*SYSTEM_FUNCTIONS_PATH_SIZE;
	system_functions_constructed = 1;
	return 0;
}

//FUNCTION: char* wd
//PURPOSE: Gets the working directory which a program is called from. Alleviates the need to allocate space for
//a buffer and the need to make a size_t variable whenever the working directory is needed.
//STATUS: Complete and tested.
char* wd()
{
	if (system_functions_constructed == 0) system_functions_constructor();
	system_functions_wd = malloc(sizeof(char)*SYSTEM_FUNCTIONS_PATH_SIZE);
	system_functions_wd = getcwd(system_functions_wd,system_functions_wdSize);
	return system_functions_wd;
}

//FUNCTION: int system_functions_test
//PURPOSE: Test the functions in this library.
//STATUS: Complete and tested.
int system_functions_test()
{
	printf("Your working directory is:\n%s\n",wd());
	return 0;
}

//MAIN
//NOTES: In my C libraries, I use main almost exclusively for testing purposes, and thus reduce it to one line so that 
//I can easily comment it out when using it in applications. Its only code is to get the exit code of the test function 
//and print it.
//int main(int argc,char* argv[]) { int test_error_code = system_functions_test(); printf("\nProgram exited with code: %d\n",test_error_code); return 0; }
