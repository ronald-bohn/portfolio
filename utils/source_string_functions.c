
/* //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * 
 * NAME: String Functions Library
 * AUTHOR: Ronald Bohn
 * PURPOSE: A set of functions for manipulating strings in C more easily
 * STATUS: Completed, working, and tested with valgrind. Works in conjunction with Memory Manager library
 *
 *///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>
#include "useful_definitions.h"

//FUNCTION: numSubstrings
//PURPOSE: Counts the number of substrings separated by a particular delimiter in a string.
//STATUS: Complete and tested.
int numSubstrings(char* inThis,char separatedByThis)
{
	char* input = inThis;
	char delimiter = separatedByThis;
	int substring_count = 0;
	
	int input_len = strlen(input);
	int function_index;
	int lastCharWasDelimiter = 1;
	
	for (function_index = 0;function_index < input_len;function_index++)
	{
		if (input[function_index] == delimiter) lastCharWasDelimiter = 1;
		else
		{
			if (lastCharWasDelimiter != 0) substring_count++;
			lastCharWasDelimiter = 0;
		}
	}
	
	return substring_count;
}


//FUNCTION: countOcurrances
//PURPOSE: Counts the number of ocurrances of a character in a string.
//STATUS: Complete and tested.
int countOcurrances(char ofThis, char* inThis)
{
	char* input = inThis;
	char delimiter = ofThis;
	int sf_co_index;
	int sf_co_strlen = strlen(input);
	int sf_co_count = 0;
	for (sf_co_index = 0;sf_co_index < sf_co_strlen;sf_co_index++)
	{
		if (input[sf_co_index] == delimiter) sf_co_count++;
	}
	return sf_co_count;
}


//FUNCTION: strAttributes
//PURPOSE: Takes a string as input, breaks the string into substrings separated by the given delimiter, and then returns
// an integer array containing the number of substrings as the first element, and the length of each substring in each
// subsequent element. Does not clobber the original string.
//STATUS: Complete and tested.
int* strAttributes(char* input,char delimiter,int* buffer)
{
	int* return_array = buffer;

	int substring_count = 0;
	int input_len = strlen(input);
	int function_index;
	int lastCharWasDelimiter = 1;

	for (function_index = 0;function_index < input_len;function_index++)
	{
		if (input[function_index] == delimiter) lastCharWasDelimiter = 1;
		else
		{
			if (lastCharWasDelimiter != 0) substring_count++;
			lastCharWasDelimiter = 0;
		}
	}
	return_array = malloc((substring_count+1)*sizeof(int));
	return_array[0] = substring_count;
	
	int currentSubstring = 0;
	int currentSubstringLength;
	lastCharWasDelimiter = 1;
	
	for (function_index = 0;function_index < input_len;function_index++)
	{
		if (input[function_index] == delimiter) 
		{
			if (lastCharWasDelimiter == 0) //Substring End
			{
				return_array[currentSubstring+1] = currentSubstringLength;
				lastCharWasDelimiter = 1;
				currentSubstring++;
			}
		}
		else
		{
			if (lastCharWasDelimiter != 0) //New Substring
			{
				currentSubstringLength = 0;
				lastCharWasDelimiter = 0;
			}
			currentSubstringLength++;
		}
	}

	if (lastCharWasDelimiter == 0) return_array[currentSubstring+1] = currentSubstringLength;
	return return_array;
}



//FUNCTION: tokenize
//PURPOSE: Breaks up a string into substrings separated by the delimiter and returns an array containing those 
// substrings. Does not clobber the original string. Also does not handle freeing the array, that is the user's
// responsibility.
//STATUS: Complete and tested.
char** tokenize(char* input, char delimiter,char** buffer)
{
	char** tokenized_str = buffer;
	int* str_attributes = strAttributes(input,delimiter,str_attributes);
	int substring_count = str_attributes[0];
	int input_len = strlen(input);
	int substring_index = 0;
	
	tokenized_str = malloc((substring_count+1)*sizeof(char*));
	
	int function_index;
	for (function_index = 0;function_index < substring_count;function_index++)
	{
		tokenized_str[function_index] = malloc((str_attributes[function_index+1]+1)*sizeof(char));
	}
	tokenized_str[function_index] = NULL;
	
	int current_substring = 0;
	int current_substring_index;
	int lastCharWasDelimiter = 1;
	
	//Copying process
	for (function_index = 0;function_index < input_len;function_index++)
	{
		if (input[function_index] == delimiter) 
		{
			if (lastCharWasDelimiter == 0) //Substring End
			{
				current_substring++;
				lastCharWasDelimiter = 1;
			}
		}
		else
		{
			if (lastCharWasDelimiter != 0) //New Substring
			{
				current_substring_index = 0;
				lastCharWasDelimiter = 0;
			}
			tokenized_str[current_substring][current_substring_index] = input[function_index];
			current_substring_index++;
		}
	}
	
	//Append a null byte to every string
	for (function_index = 0;function_index < substring_count;function_index++)
	{
		tokenized_str[function_index][str_attributes[function_index+1]] = '\0';
	}
	
	free(str_attributes);
	return tokenized_str;
}

//FUNCTION: int replaceChar
//PURPOSE: Replace the first instance of "this" character with second character in the given string
//STATUS: Complete and tested.
int replaceChar(char this, char with, char* in)
{
	int length = strlen(in);
	int i;
	for (i=0;i<length;i++) if (in[i] == this) 
	{
		in[i] = with;
		return 0;
	}
	return -2;
}

//FUNCTION: int replaceAll
//PURPOSE: Replace the first instance of "this" character with second character in the given string
//STATUS: Complete and tested.
int replaceAll(char this, char with, char* in)
{
	int length = strlen(in);
	int i;
	for (i=0;i<length;i++) if (in[i] == this) in[i] = with;
	return 0;
}

//FUNCTION: int nextIndexOfSubstring
//PURPOSE: Get the index in a string of the next occurrance of a particular substring. 
//STATUS: Complete, needs testing.
int nextIndexOfsubstring(char* this, char* in,int from)
{
	if ((strlen(this)+from)>strlen(in)) return -3;
	int a,b,c;
	for (a=from;a<strlen(in);a++) for (b=0;c==0;) 
	{
		c=0;
		if (this[b] == in[a+b]) 
		{
			if (b == (strlen(this)-1)) return a;
			else b++;
		}
		else c++;
	}
	return -2;
}

//FUNCTION: int firstIndexOfSubstring
//PURPOSE: Get the index in a string of the first occurrance of a particular substring
//STATUS: Complete, needs testing.
int firstIndexOfSubstring(char* this, char* in)
{
	if (strlen(this)>strlen(in)) return -3;
	int a,b,c;
	for (a=0;a<strlen(in);a++) for (b=0;c==0;) 
	{
		c=0;
		if (this[b] == in[a+b]) 
		{
			if (b == (strlen(this)-1)) return a;
			else b++;
		}
		else c++;
	}
	return -2;
} 

//FUNCTION: int firstIndexOf
//PURPOSE: Return the first index in a string of a particular character
//STATUS: Complete and tested.
int firstIndexOf(char this, char* in)
{
	int length = strlen(in);
	int i;
	for (i=0;i<length;i++) if (in[i] == this) return i;
	return -3;
}

//FUNCTION: int lastIndexOf
//PURPOSE: Return the last index in a string of a particular character
//STATUS: Complete and tested.
int lastIndexOf(char this, char* in)
{
	int length = strlen(in);
	int i;
	for (i=length-1;i>-1;i--) if (in[i] == this) return i;
	return -3;
}




//FUNCTION: int string_functions_test
//PURPOSE: Test the other functions in this source file
//STATUS: Complete and tested for the aforementioned tested functions. A few more tests need to be added.
int string_functions_test()
{
	int string_index;
	char* test_string = malloc(sizeof(char)*100);
	test_string = strcpy(test_string,"B um Sbm. Sbm B bm.");
 	
	string_index = firstIndexOf('B',test_string);
	test_string[string_index] = 'I';
 	
	string_index = lastIndexOf('B',test_string);
	test_string[string_index] = 'I';
	
	replaceChar('u','a',test_string);
	replaceAll('b','a',test_string);

	int x = countOcurrances(' ',test_string);
	int y = countOcurrances('.',test_string);
	int z = numSubstrings("   I am Sam. Sam I am.",' ');
	int w = numSubstrings("I am Sam. Sam I am.",'.');
	
	char** s = tokenize("  I am Sam. Sam I am.",' ',s);
	char** t = tokenize("I am Sam. Sam I am.",'.',t);
	
		
	if (strcmp(test_string,"I am Sam. Sam I am.")==0) 
	if (x == 5 && y == 2 && z == 6 && w == 2)
	if (strcmp(s[0],"I") == 0 && strcmp(s[2],"Sam.") == 0 && strcmp(t[1]," Sam I am")==0)
	printf("Program test was a success!\n");
	else {printf("\nProgram test failed, the returned string was:\n\"%s\"\nbut should have been: \n\"I am Sam. Sam I am.\"\n",test_string);}

	free(test_string);
	freec(s);
	freec(t);

	return 0;
}

//MAIN
//NOTES: In my C libraries, I use main almost exclusively for testing purposes, and thus reduce it to one line so that I can
// easily comment it out when using it in applications. Its only code is to get the exit code of the test function and 
// print it.
int main(int argc,char* argv[]) { int errC = string_functions_test(); printf("\nProgram exited with code: %d\n",errC); return 0; }
