#ifndef MACROSYSTEM
#define MACROSYSTEM

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/StringUtils.h"
#include "../header/NodeData.h"
#include "../header/StringUtils.h"
#include "../header/PublicDef.h"
#include "../header/LineDetction.h"

typedef struct
{
    char *name;
    LinePtr start;
} macrostruct, *macroPtr;

macroPtr ExistMacro(macroPtr macros[],int size, char *name);
macroPtr * addMacroToList(macroPtr *macroarray,int size, LinePtr temp,BOOLEAN *ptrmacroflag);
LinePtr InitSingelMacro(LinePtr copy);
LinePtr AddMacroToProgram(LinePtr temp, LinePtr list);
LinePtr InitMacro(LinePtr head, BOOLEAN *ptrmacroflag);

#endif 