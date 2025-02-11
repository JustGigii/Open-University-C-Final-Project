
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
    RecountLine(head, 1);

    return head;
}

/*start new version*/
LinePtr InitMacro2(LinePtr head)
{
    LinePtr temp = head;
    LinePtr tofree;
    LinePtr add = NULL;
    macroPtr *macroarray = NULL; /* (macroPtr*)malloc((sizeofmacroarray+1) * sizeof(macroPtr));*/
    int macroindex = 0;
    int succsec;
    int indextofree;
    /*first stage:collect definition of macro */
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
    /*second stage: look after macro and replace them */
        temp = head;
    while (temp->next){
       add = ExistMacro(macroarray, macroindex, temp->next->line);
       if (add)
           temp = AddMacroToProgram(temp, add);
        else
          temp = temp->next;
    }

} /*end new version*/

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
    if (split == NULL)
    {
        free(macroarraynew);
        return NULL;
    }
    
    indexname = getmacroname(split, sizeofsplit);
    if(indexname == -1)
    {
        free(macroarraynew);
        freeIneersplit(split, sizeofsplit);
        return NULL;
    }

    macroarraynew[size]->name = strdup(split[indexname]);
    macroarraynew[size]->start = InitSingelMacro(temp);
    freeIneersplit(split, sizeofsplit);
    if (macroarraynew[size]->start == NULL)
    {
        free(macroarraynew);
        return NULL;
    }
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
   
    while (strcmp(copy->next->line, "mcroend") != 0)
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
    
    if (size!=2)
    {
        printf("error: Macro's definition is invalid\n");
        return NULL;
    }
    else if ( strcmp(linearray[1], "mcro"))
        return 1;
    else
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
