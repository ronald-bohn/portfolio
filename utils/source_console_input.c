

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * 
 * NAME: Console Input Library
 * AUTHOR: Ronald Bohn
 * PURPOSE: A set of functions for getting console input in C more easily
 * STATUS: Completed and tested. All functions are working as expected. I would like to add a string array to 
 *  remember past inputs, but I will not add this until I finish the other components and spruce up the 
 *  "command execute" library first.
 *
 *///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "header_console_input.h"
#include "useful_definitions.h"

char* consoleInput_memory[100];
int consoleInput_memIndex = 0;


//FUNCTION: char* console_input
//PURPOSE: Read input from the console and return the address of the input in consoleInput_memory
//STATUS: Complete and tested. Needs some revisions to make it more space efficient and reliable.
char* console_input()
{
	consoleInput_memory[consoleInput_memIndex] = malloc(CONSOLE_INPUT_MAX_BUFFER_SIZE);
	ssize_t strLength = read(STDIN_FILENO, (void*) consoleInput_memory[consoleInput_memIndex], CONSOLE_INPUT_MAX_BUFFER_SIZE);
	consoleInput_memory[consoleInput_memIndex][(int) strLength-1] = '\0';
	consoleInput_memIndex++;
	return consoleInput_memory[consoleInput_memIndex-1];
}

//FUNCTION: int console_input_test
//PURPOSE: Test the other function(s) in this library
//STATUS: Complete and tested.
int console_input_test()
{
	printf("TYPE SOMETHING!\n");
	char* input = console_input();
	printf("\nInput from keyboard was:\n\"%s\"\n",input);
	return 0;
}

//MAIN
//NOTES: In my C libraries, I use main almost exclusively for testing purposes, and thus reduce it to one line so that I can
//easily comment it out when using it in applications. Its only code is to get the exit code of the test function and 
//print it.

//int main(int argc,char* argv) { int test_error_code = console_input_test(); printf("\nProgram exited with code: %d\n",test_error_code); return 0; }
