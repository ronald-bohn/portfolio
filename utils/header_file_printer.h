#include <string.h>

#define FILE_PRINTER_LINE_BUFFER_SIZE 1024
#define FILE_PRINTER_FILENAME_SIZE 256

extern int setTarget(char* filename);
extern int closeAll();
extern void printTo(char* filename,char* input);
extern void println(char* input);
extern void fprint(char* input);
