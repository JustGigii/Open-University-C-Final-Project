#include "../header/NodeData.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/StringUtils.h"

typedef struct
{
    char *name;
    LinePtr start;
} macrostruct, *macroPtr;

int sizeofmacroarray = 0;

macroPtr *InitMacro(LinePtr head)
{
    LinePtr temp = head;
    LinePtr add = NULL;
    macroPtr *macroarray = NULL; // (macroPtr*)malloc((sizeofmacroarray+1) * sizeof(macroPtr));
    while (temp)
    {
        add = ExistMacro(macroarray, temp->line);
        if (add)
        {
            
        }
        if (strstr(temp->line, "mcro"))
            temp = addmacrotolist(macroarray, head,temp);
        
        
    }
}
LinePtr ExistMacro(macroPtr macros[], char *name){
    LinePtr macrosstart = NULL;
    int index;
    for (index=0; index<sizeofmacroarray; index++)
    {
       if(strcmp(name,macros[index]->name)==0)
        macrosstart = macros[index];
        index = sizeofmacroarray;
    }
    return macrosstart;
}
LinePtr addmacrotolist(macroPtr *macroarray, LinePtr head, LinePtr temp)
{
    char **linearray = NULL;
    char *macroName;
    LinePtr remove = NULL;
    int sizeofmacroarray = 0;
    linearray = Split(temp->line, " ", &sizeofmacroarray);
    macroName = getmacroname(linearray, sizeofmacroarray);
    if (macroName == NULL)
        return NULL;
    macroarray = (macroPtr *)realloc(macroarray, (sizeofmacroarray + 1) * sizeof(macroPtr));
    macroarray[sizeofmacroarray]->start = NULL;
    macroarray[sizeofmacroarray]->name = malloc(strlen(macroName) + 1);
    strcpy(macroarray[sizeofmacroarray]->name, macroName);
    freeIneersplit(linearray,sizeofmacroarray);
    remove = temp;
    temp = temp->next;
    head = RemoveLine(head, remove->lineNum);
    while (temp && strcmp(temp->line, "mcroend"))
    {
    if(AddLine(macroarray[sizeofmacroarray]->start ,temp->line)==-1)
    return NULL;
    remove = temp;
    temp = temp->next;
    head = RemoveLine(head, remove->lineNum);
    }
    if (!temp)
    return NULL;
    return temp->next;
}

char *getmacroname(char **linearray, int size)
{
    if (size < 2 && size > 3)
    {
        printf("error: Macro's definition is invalid\n");
        return NULL;
    }
    if (size == 2 && strcmp(linearray[1], "mcro"))
        return linearray + 1;
    if (size == 3 && strcmp(linearray[2], "mcro"))
        return linearray + 2;
    return NULL;
}
int addmacrotoprogram(LinePtr head,LinePtr temp, LinePtr list)
{


}