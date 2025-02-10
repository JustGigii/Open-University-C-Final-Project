#ifndef FILEHANDLER
#define FILEHANDLER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/NodeData.h"
#include "../header/PublicDef.h"
## define AddExtensionToFileName( FileName, Extension ) FileName##Extension /*to create extension to file */

int GetFileData(char* filename, LinePtr* head);
FILE* OpenFile(char* filename,char* mode);
int IfFileEndContract(char* filename);
LinePtr InitData(FILE* datafile);

#endif  