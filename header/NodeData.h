#ifndef NODEDATA
#define NODEDATA
#include <stdio.h>
#include <string.h>

typedef struct linestruct
{
    short lineNum;
    char* line;
    struct linestruct* next;
} Line, * LinePtr; 

LinePtr InitLine( char* line);
int AddLine(LinePtr head, char* line);
LinePtr RemoveLine(LinePtr head, int number);
int PrintLines(LinePtr head);

#endif