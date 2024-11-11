
#include "../header/MacroSystem.h"

int getmacroname(char **linearray, int size);
LinePtr InitMacro(LinePtr head)
{
    LinePtr temp = head;
    LinePtr tofree;
    LinePtr add = NULL;
    macroPtr *macroarray = NULL; /* (macroPtr*)malloc((sizeofmacroarray+1) * sizeof(macroPtr));*/
    int macroindex = 0;
    int succsec;
    int indextofree;
    while (temp)
    {
       if (strstr(temp->line, "mcro"))
        {
      
            macroarray = addMacroToList(macroarray, macroindex, temp);
            if (!macroarray)
                return NULL;
            while (temp = RemoveLine(head, -1))
            if (temp == head)
                temp = NULL;
            macroindex++;
        }
        else
            temp = temp->next;
    }
    temp = head;
    while (temp)
    {
        add = ExistMacro(macroarray, macroindex, temp->line);
        if (add)
        {
            indextofree = temp->lineNum;
            temp = AddMacroToProgram(temp, add);
            if (!temp && RemoveLine(head, indextofree))
                return NULL;
            RecountLine(head, START_LINE);
        }
        else
             temp = temp->next;
    }
    
   PrintLines(head); 
    return head;
}
macroPtr ExistMacro(macroPtr macros[], int size, char *name)
{
    LinePtr macrosstart = NULL;
    int index;
    for (index = 0; index < size; index++)
    {
        if (strcmp(name, macros[index]->name) == 0)
            macrosstart = macros[index]->start;
        index++;
    }
    return macrosstart;
}
macroPtr *addMacroToList(macroPtr *macroarray, int size, LinePtr temp)
{
    macroPtr *macroarraynew = NULL;
    int indexname;
    char **split;
    int sizeofsplit = 0;
    
    if (size == 0)
    {
        macroarraynew = malloc(sizeof(macroPtr));
    }
    else
    {
        macroarraynew = realloc(*macroarray, (size + 1) * sizeof(macroPtr));
    }

    if (!macroarraynew)
        return NULL;
    macroarraynew[size] = malloc(sizeof(macrostruct));
    split = Split(temp->line, " ", &sizeofsplit);
    indexname = getmacroname(split, sizeofsplit);
    if(indexname == -1)
        return NULL;
    macroarraynew[size]->name = malloc((strlen(split[indexname]) + 1) * sizeof(char));
    if( macroarraynew[size]->name  == NULL)
    {
        free(macroarraynew[size]);
        free(macroarraynew);
        return NULL;
    }
    macroarraynew[size]->name = strcpy(macroarraynew[size]->name, split[indexname]);
    macroarraynew[size]->start = InitSingelMacro(temp);
    if (macroarraynew[size]->start == NULL)
        return NULL;
    return macroarraynew;
}
LinePtr InitSingelMacro(LinePtr copy)
{
    LinePtr macroline;
    copy->lineNum =-1;
    copy = copy->next;
    macroline = InitLine(copy->line, 1);
    copy = copy->next;
    while (strcmp(copy->line, "mcroend\n") != 0)
    {
        copy->lineNum =-1;
        if(AddLine(macroline, copy->line)== 0)
        return NULL;
        if (!macroline)
            return NULL;
        copy = copy->next;
    }
    copy->lineNum =-1;
    return macroline;
}

int getmacroname(char **linearray, int size)
{
    
    if (size < 2 && size > 3)
    {
        printf("error: Macro's definition is invalid\n");
        return NULL;
    }
    if (size == 2 && strcmp(linearray[1], "mcro"))
        return 1;
    if (size == 3 && strcmp(linearray[2], "mcro"))
        return 2;
    return -1;
}
LinePtr AddMacroToProgram(LinePtr temp, LinePtr list)
{
    while (list)
    {
        
        if (addBetweenline(temp, list->line) == -1)
        return NULL;
        list = list->next;
        temp = temp->next;
    }
    return temp;
}