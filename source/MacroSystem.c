
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

         
        add = ExistMacro(macroarray, macroindex, temp->next->line);
        if (add)
        {
           temp = AddMacroToProgram(temp, add);
        }
       else if (strstr(temp->next->line, "mcro"))
        {
      
            macroarray = addMacroToList(macroarray, macroindex, temp);
            macroindex++;
        }
        else
            temp = temp->next;
    }
    temp = head;
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
        macroarraynew = malloc(sizeof(macroPtr));  
    else  
        macroarraynew = realloc(macroarray, (size + 1) * sizeof(macroPtr));


    if (!macroarraynew)
        return NULL;
   
    macroarraynew[size] = malloc(sizeof(macrostruct));
    split = Split(temp->next->line, " ", &sizeofsplit);
    indexname = getmacroname(split, sizeofsplit);
    if(indexname == -1)
        return NULL;
    macroarraynew[size]->name = strdup(split[indexname]);
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
    copy->next = NULL;
    head->next = tofree->next;
    freeLine(tofree);
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
    newLine = temp->next;
    temp->next = newLine->next;
    freeLine(newLine);
    LinePtr next = temp->next;
    while (list)
    {
        newLine = InitLine(list->line,-1);
        prev->next = newLine;
        prev= prev->next;
        list = list->next;

    }
     prev->next = next;
    return prev;
    
}