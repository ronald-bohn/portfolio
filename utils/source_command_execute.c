
/* //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * 
 * NAME: Command Execution Library
 * AUTHOR: Ronald Bohn
 * PURPOSE: A set of functions for executing other programs within a C program. Handles forking automatically
 * STATUS: All of the methods are complete and work. Currently the library does not support redirection or pipes
 * but I would like to add these features eventually.
 *
 *///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header_command_execute.h"
#include "useful_definitions.h"


//FUNCTION: int cexe
//PURPOSE: Execute a program with the supplied name and parameters. Like with execvp, the first
//string in the array must be the name of the program and the others must be the flags and arguments,
//however, unlike execvp, no processes must be forked, and the name does not have to be redundantly
//passed to this function. It accepts only a single string array and does the rest of the work itself.
//STATUS: Complete and tested. I would like to add support for redirection and pipes in the future, though.
int cexe(char** parameter_array)
{
	
	pid_t pid1;
	pid_t pid2;
	
	pid1 = getpid();
	fork();
	pid2 = getpid();
	if (pid1 != pid2) //child
	{
		execvp(parameter_array[0],parameter_array);
		exit(1);
	}
	return 0;
}

//FUNCTION: int cexe
//PURPOSE: Test the other functions in this library.
//STATUS: Complete and tested.
int command_execute_test()
{
	char** testArray = malloc(4*sizeof(char*));
	int counter;
	for (counter=0;counter<4;counter++)
	{
		testArray[counter] = malloc(10*sizeof(char));
	}
	
	testArray[0] = "touch";	
	testArray[1] = "I";	
	testArray[2] = "am";	
	testArray[3] = "Sam";	

	cexe(testArray);

	sleep(1);
	
	testArray[0] = "rm";

	cexe(testArray);

	printf("Test completed");
	return 0;
}

//MAIN
//NOTES: In my C libraries, I use main almost exclusively for testing purposes, and thus reduce it to one line so that I can
//easily comment it out when using it in applications. Its only code is to get the exit code of the test function and 
//print it.

//int main(int argc,char* argv[]) { int test_error_code = command_execute_test(); printf("\nProgram exited with code: %d\n",test_error_code); return 0; }
