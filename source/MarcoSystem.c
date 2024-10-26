#include "../header/NodeData.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    char* name;
    LinePtr start;
}macrostruct, * macroPtr;

int sizeofmacroarray = 0;
LinePtr HanelMacro(const LinePtr head)
{

}


macroPtr* InitMacro(const LinePtr head)
{
    macroPtr* macroarray =NULL;// (macroPtr*)malloc((sizeofmacroarray+1) * sizeof(macroPtr)); 
    while (head)
    {
        if(strstr(head->line,"mcro"))
        {
            
        }
    }
    

}



