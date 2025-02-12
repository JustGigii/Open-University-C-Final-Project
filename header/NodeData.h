#ifndef NODEDATA
#define NODEDATA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/StringUtils.h"
#include "../header/PublicDef.h"
#include "../header/NodeData.h"
typedef struct linestruct
{
    short lineNum;
    char* line;
    unsigned int* assemblyCode;
    int assemblyCodeCount;
    struct linestruct* next;
} Line, * LinePtr; 

LinePtr InitLine( char* line,short lineNum);
int addBetweenline(LinePtr head, char* line);
void RecountLine(const LinePtr head, short number);
int AddLine(LinePtr head, char* line);
LinePtr RemoveLine(LinePtr head, int number);
int PrintLines(LinePtr head);
int freeLine(LinePtr Line);

#endif