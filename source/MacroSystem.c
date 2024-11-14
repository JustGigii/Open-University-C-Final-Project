
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
    while (temp->next)
    {
       if (strstr(temp->next->line, "mcro"))
        {
      
            macroarray = addMacroToList(macroarray, macroindex, temp);
            macroindex++;
        }
        else
            temp = temp->next;
    }
    temp = head;
    while (temp->next)
    {
        
        add = ExistMacro(macroarray, macroindex, temp->next->line);
        if (add)
        {
           temp = AddMacroToProgram(temp, add);
        }
        else
             temp = temp->next;
    }
    RecountLine(head, START_LINE);
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
        {   
            macrosstart = macros[index]->start;
            index = size;
        }
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
    split = Split(temp->next->line, " ", &sizeofsplit);
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

    LinePtr head = copy;
    LinePtr tofree=copy->next;
    LinePtr macro;
    copy->next = tofree->next;
    freeLine(tofree);
    macro= copy->next;
    while (strcmp(copy->next->line, "mcroend\n") != 0)
    {
        copy = copy->next;
    }
    tofree = copy->next;
    freeLine(tofree);
    copy->next = NULL;
    head->next = tofree->next;

    return macro;
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
    LinePtr newLine;
    LinePtr prev = temp;
    LinePtr next = temp->next;
    newLine = temp->next;
    temp->next = newLine->next;
    freeLine(newLine);
    while (list)
    {
        newLine = InitLine(list->line, list->lineNum);
        prev->next = newLine;
        prev= prev->next;
        list = list->next;

    }
     prev->next = next;
    return next;
    
}