
#include "../header/MacroSystem.h"

int getmacroname(char **linearray, int size,BOOLEAN *ptrmacroflag);
const char *my_reserved[]={"mov","cmp","add","sub","lea","clr","not","inc","dec","jmp","bne","jsr","red","prn","rts","stop",".data",".string",".entry",".extern",};
const int my_reserved_count=20;

LinePtr InitMacro(LinePtr head,BOOLEAN *ptrmacroflag)
{
    LinePtr temp = head;
    LinePtr tofree;
    LinePtr add = NULL;
    macroPtr *macroarray = NULL; /* (macroPtr*)malloc((sizeofmacroarray+1) * sizeof(macroPtr));*/
    int macroindex = 0;
    int succsec;
    int indextofree;
    LinePtr globalline = InitLine("mman14100", 34);/*create fake line for head becouse the checking start to check from the next line*/
    globalline->next = head;
    temp = globalline;
    /*first stage:collect definition of macro */
    while (temp->next)
    {
      if (strstr(temp->next->line, "mcro"))
        {

            macroarray = addMacroToList(macroarray, macroindex, temp,ptrmacroflag);
            macroindex++;
            temp = temp->next;
        }
        else
            temp = temp->next;
        if (*ptrmacroflag==FALSE)
             return NULL;
    }
    printf("==%d==%d\n",*ptrmacroflag,FALSE);
      
    /*second stage: look after macro and replace them */
        temp = globalline;
    while (temp->next){
       add = ExistMacro(macroarray, macroindex, temp->next->line);
       if (add)
           temp = AddMacroToProgram(temp, add);
        else
          temp = temp->next;
    }
    temp = globalline;
    globalline = globalline->next;
    freeLine(temp); /*free fake line*/
    RecountLine(globalline, 1);
    return globalline;
} 


macroPtr ExistMacro(macroPtr macros[], int size, char *name)
{
        LinePtr macrosstart = NULL;
    int index;
    for (index = 0; index < size; index++)
    {
        if (strcmp(name, macros[index]->name) == 0)/*if macro exist*/
        {   
            macrosstart = macros[index]->start;
            index = size;
        }
    }
    return macrosstart;
}

macroPtr *addMacroToList(macroPtr *macroarray, int size, LinePtr temp,BOOLEAN *ptrmacroflag)
{
    macroPtr *macroarraynew = NULL;
    int indexname;
    char **split;
    int sizeofsplit = 0;
    if (size == 0)/*first macro*/
        macroarraynew = malloc(sizeof(macroPtr));  
    else /*not first macro*/ 
        macroarraynew = realloc(macroarray, (size + 1) * sizeof(macroPtr));


    if (!macroarraynew)/*error in allocation*/
        return NULL;
   
    macroarraynew[size] = malloc(sizeof(macrostruct));
    split = Split(temp->next->line, " ", &sizeofsplit);/*split the macro to peaces of one word*/
    if (split == NULL)/*no words*/
    {
        free(macroarraynew);
        return NULL;
    }
    
    indexname = getmacroname(split, sizeofsplit,ptrmacroflag);/*get the name of the macro after cheking if it is valid*/
    if(indexname == -1)/*name is not valid*/
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
    /*copy the macro definition*/
    copy->next = tofree->next;
    freeLine(tofree);
    macro= copy->next;
   
    while (strcmp(copy->next->line, "mcroend") != 0)/*not end of macro*/
    {
        copy = copy->next;
    }
    tofree = copy->next;
    copy->next = NULL;
    head->next = tofree->next;
    freeLine(tofree);
    return macro;
}

int getmacroname(char **linearray, int size,BOOLEAN *ptrmacroflag)
{
    int i;
    if (size!=2) /*macro definition must have 2 words*/
    {
        *ptrmacroflag=FALSE;
        printf("error: Macro's definition is invalid, must have 2 words\n");
        return -1;
    }

    /*check if macro's name is reserved word*/
    for (i = 0; i < my_reserved_count; i++)
        if (strcmp(linearray[1], my_reserved[i]) == 0){
           printf("error: Macro's name %s is reserved word\n",linearray[1]);
           *ptrmacroflag=FALSE;
            return -1;
        }
     if ( strcmp(linearray[0], "mcro")==0)/*if the first word is mcro*/
        return 1;
    else
    {
        printf("error: Macro's definition is invalid\n");
    *ptrmacroflag=FALSE;
      return -1;
    }
}

LinePtr AddMacroToProgram(LinePtr temp, LinePtr list)
{
    LinePtr newLine;
    LinePtr prev = temp;
    newLine = temp->next;
    temp->next = newLine->next;
    freeLine(newLine);
    LinePtr next = temp->next;
    while (list)/*copy the macro to the program*/
    {
        newLine = InitLine(list->line,-1);
        prev->next = newLine;
        prev= prev->next;
        list = list->next;

    }
     prev->next = next;
    return prev;
    
}
