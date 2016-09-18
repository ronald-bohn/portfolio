

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * 
 * NAME: String Functions Library
 * AUTHOR: Ronald Bohn
 * PURPOSE: A set of functions for manipulating strings in C more easily
 * STATUS: Most of the functions have been tested and work. Only a few need testing.
 * NOTES: For my own custom programs and libraries (in general), -1 is an error code meaning a function has not been 
 * implemented, -2 means there was no match (for functions that search), -3 means that invalid parameters were 
 * given, and -4 means that the function was probably called improperly, from a source it shouldn't have been called
 * from. Additionally, it should be noted that all of the functions in this library are pass-by-reference.
 *
 *///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>
#include "header_console_input.h"
#include "header_file_printer.h"

int file_printer_constructed = 0;
int file_printer_nothingOpen;
int file_printer_newFile;
int lastLineBroken = 0;
FILE* file_printer_outfile;
char* file_printer_openFilename;
char* file_printer_line;



//FUNCTION: int file_printer_constructor
//PURPOSE: Initializes a number of variables needed for the rest of the functions in the library.
//STATUS: Complete and tested. I want to test to make absolutely sure it is called appropriately
//at a later date, but it functions fine for now. If I can bound the calls to a handful of functions
//I can keep the library very modular by using the functions I have already made in newer, more 
//powerful functions.
int file_printer_constructor(char* filename)
{
	file_printer_nothingOpen = 0;
	file_printer_newFile = 1;
	file_printer_openFilename = malloc(FILE_PRINTER_FILENAME_SIZE*sizeof(char));
	file_printer_openFilename = strcpy(file_printer_openFilename,filename);
	file_printer_outfile = fopen(filename,"a+");
	file_printer_line = malloc(sizeof(char)*FILE_PRINTER_LINE_BUFFER_SIZE);
	file_printer_constructed = 1;
	return 0;
}

//FUNCTION: int setTarget
//PURPOSE: Sets the target to write to for the other functions.
//STATUS: Complete and tested.
int setTarget(char* filename)
{
	if (file_printer_constructed == 0) return file_printer_constructor(filename);
	
	if (file_printer_nothingOpen == 0)
	{
		if (strcmp(file_printer_openFilename,filename)!=0) 
		{
			file_printer_newFile = 1;
			file_printer_openFilename = strcpy(file_printer_openFilename,filename);
		}
		else return 0;
	}
	else file_printer_nothingOpen = 0;
	file_printer_openFilename = strcpy(file_printer_openFilename,filename);
	file_printer_outfile = fopen(filename,"a+");
	return 0;
}


//FUNCTION: void printTo
//PURPOSE: Print a string to a target file. Handles boilerplate file opening for a more user-friendly format.
//STATUS: Complete and tested.
void printTo(char* filename,char* input)
{
	setTarget(filename);
	fprintf(file_printer_outfile,"%s",input);
	fflush(file_printer_outfile);
	return;
}

//FUNCTION: void println
//PURPOSE: Print a string and ensure that the string starts on a new file_printer_line and that the next printed string starts on
//on a new file_printer_line.
//STATUS: Complete and tested.
void println(char* input)
{
	lastLineBroken = 1;
	if (strlen(input) == 0) fprint("\n");
	else if (file_printer_nothingOpen != 0) 
	{
		fprint(input);
		fprint("\n");
	}
	else if (file_printer_newFile != 0 || lastLineBroken != 0) 
	{
		fprint(input);
		fprint("\n");
	}
	else
	{
		fprint("\n");
		fprint(input);
		fprint("\n");
	}
	return;
}

//FUNCTION: void fprint
//PURPOSE: Print a string to a file. If a file was previously opened, this function will print to that file. If not,
//it will prompt the user to give a file name to write to. Does not ensure file_printer_line breaks.
//STATUS: Complete and tested.
void fprint(char* input)
{
	if (file_printer_nothingOpen != 0) 
	{
		char* name = malloc(FILE_PRINTER_LINE_BUFFER_SIZE*sizeof(char));
		printf("What file would you like to write to?\n");
		name = console_input();
		setTarget(name);
	}
	printTo(file_printer_openFilename,input);
	return;
}

//FUNCTION: int closeAll
//PURPOSE: Close the open file that is being printed to. Used by other functions in this library. I am not sure yet 
//whether or not to include this function in the header file to allow users to call it themselves.
//STATUS: Complete and tested.
int closeAll()
{
	if (file_printer_constructed == 0) return -4;
	if (file_printer_nothingOpen == 1) return -2;
	fclose(file_printer_outfile);
	file_printer_nothingOpen = 1;
	lastLineBroken = 0;
	return 0;
}

//FUNCTION: int file_printer_test
//PURPOSE: Test the functions in this library.
//STATUS: Complete and tested.
int file_printer_test()
{
	printTo("example1.txt","This is a test file created by the \"file_printer.c\" program.");
	println("");
	
	int closeAll_return_code = closeAll();
	if (closeAll_return_code != 0) return closeAll_return_code;
	
	println("This is a second test file created by the \"file_printer.c\" program.");
	fprint("This is a second line in the second test file created by the \"file_printer.c\" program.");
	println("");
	
	printTo("example1.txt","This is a second line in the first test file created by the \"file_printer.c\" program.\n");

	return 0;
}


//MAIN
//NOTES: In my C libraries, I use main almost exclusively for testing purposes, and thus reduce it to one line so that 
//I can easily comment it out when using it in applications. Its only code is to get the exit code of the test function 
//and print it.

//int main(int argc,char* argv[]) { int test_error_code = file_printer_test(); printf("\nProgram exited with code: %d\n",test_error_code); return 0; }
