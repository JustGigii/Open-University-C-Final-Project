#include "../header/LineDetction.h"

const char *my_reserved_Two_oprand_words[] = {"mov", "cmp", "add", "sub", "lea"};
const char *my_reserved_one_oprand_words[] = { "clr", "not", "inc", "dec", "jmp",
                                            "bne", "jsr", "red", "prn"};
const char *my_reserved_no_oprand_words[] = { "rts","stop"};

BOOLEAN print_operand(LinePtr heads)
{
    int i;
    labelPtr *tables = NULL;
    int tablesize = 0, instructionCount = START_LINE;
    LinePtr temp = heads;
    while (temp)
    {
        if (check_operand(temp, &tables, &tablesize, &instructionCount) != SUCCESS)
            return FALSE;
        temp = temp->next;
    }
    for (i = 0; i < tablesize; i++)
    {
        printf("%s: %d\n", tables[i]->name, tables[i]->lineNum);
    }
    
}
SATATUS check_operand(LinePtr line, labelPtr ** tables, int* tablesize, int *instructionCount)
{
    SATATUS status = SUCCESS;
    int i;
    int size=0, deltacount = 0;
    char ** strarray=NULL;
    labelPtr label;
     /* check for have comma in the end */
    if(line->line[strlen(line->line)-1]==',')  
    {
        return TO_MANY_PARAMETERS;
    }
    /* split the input  to command name and parameters*/
    strarray = Split(line->line, " ", &size);
     if (strarray == NULL)
    {
        return FAILURE_CANNOT_ALLOCATE_MEMORY;
    }
    /* check for comma in the command name */
    if (strarray[0][strlen(strarray[0]) - 1] == ',')
        return ILLEGAL_COMMA;
    
    if (strarray[0][strlen(strarray[0]) - 1] == ':')
    {
        status =  ProcessLabel(strarray, line, instructionCount, tables, tablesize,size,&deltacount);
    
    }
    else
    {
        
    }
    *instructionCount += deltacount;
    freeIneersplit(strarray, size);
    return status;
}

BOOLEAN check_no_save_word(const char *label)
{
    int i;
    BOOLEAN ok =TRUE;
     for (i = 0; i < MY_RESERVED_ONE_OPRAND_WORDS_COUNT && ok; i++)
    {
        if (strcmp(my_reserved_one_oprand_words[i], label) == 0)
            ok = FALSE;
    }
    for (i = 0; i < MY_RESERVED_TWO_OPRAND_WORDS_COUNT && ok; i++)
    {
        if (strcmp(my_reserved_one_oprand_words[i], label) == 0)
            ok = FALSE;
    }
    for (i = 0; i < MY_RESERVED_NO_OPRAND_WORDS_COUNT && ok; i++)
    {
        if (strcmp(my_reserved_no_oprand_words[i], label) == 0)
            ok = FALSE;
    }
    if (strlen(label) == 2 && label[0] == 'r' && label[1] >= '1' && label[1] <= '9')
    {
        ok = FALSE;
    }

    return ok;
}

labelPtr cheack_Label_Exist(const labelPtr labels[],int size_of_labels,const char * labelname){
    int i;
    if(labels == NULL)
        return FALSE;
    for (i=0; i<size_of_labels; i++)
    {
        if (strcmp(labels[i]->name, labelname) == 0)
            return labels[i];
    }
    return NULL;
}
  
