#ifndef FILEHANDLER
#define FILEHANDLER

#include "../header/FileHandler.h"
#include <stdio.h>
#include <string.h>

int GetFileData(char* filename);
int print_file(FILE* datafile);
FILE* OpenFile(char* filename);
int IfFileEndCottract(char* filename);

#endif  