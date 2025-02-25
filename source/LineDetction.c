#include "../header/LineDetction.h"

const char *my_reserved_Two_oprand_words[] = {"mov", "cmp", "add", "sub", "lea"};
const char *my_reserved_one_oprand_words[] = { "clr", "not", "inc", "dec", "jmp",
                                            "bne", "jsr", "red", "prn"};
const char *my_reserved_no_oprand_words[] = { "rts","stop"};

int assembly_run =0;
int data_line_couter =0;    
int code_line_couter =0;
BOOLEAN is_extern = FALSE;
BOOLEAN is_intern = FALSE;
labelPtr * CreateAssemblyLine(LinePtr heads,int * sizeofTables,SATATUS *status)
{
    BOOLEAN is_succsess = TRUE;
    SATATUS is_line_succsess = SUCCESS;
    int i;
    labelPtr *tables = NULL;
    int tablesize = 0, instructionCount = START_LINE;
    LinePtr temp = heads;
    assembly_run=1;
    for ( i = 0; i < 2; i++)
    {    
    while (temp)
    {
        is_line_succsess = check_operand(temp, &tables, &tablesize, &instructionCount);
        if (is_line_succsess != SUCCESS)
        {
            is_succsess = FALSE;
            print_error(is_line_succsess, temp->lineNum, temp->line);
        }
        temp = temp->next;
    }
    if(is_succsess==FALSE|| tables ==NULL)
        i=2;
    temp = heads;
    assembly_run = 2;
    }
    /*
    print_extern(tables, tablesize);
    printf("\n");
    print_intern(tables, tablesize);
    printf("\n");
    print_hexadecimal_line(heads);*/
    *status = (is_succsess ==TRUE)?SUCCESS:FAILURE;
    *sizeofTables = tablesize;
    return is_succsess? tables: NULL;
}
SATATUS check_operand(LinePtr line, labelPtr ** tables, int* tablesize, int *instructionCount)
{
    SATATUS status = SUCCESS;
    int i;
    int size=0, deltacount = 0;
    char ** strarray=NULL;
    labelPtr label;
    unsigned int *x;
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
        deltacount = process_sentence(line, strarray, size, tables, tablesize, &status);
    }
    if (assembly_run<2)
    {
        line->lineNum =*instructionCount;
        *instructionCount += deltacount;
    }
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

labelPtr cheack_Label_Exist(const labelPtr *labels[],int size_of_labels,const char * labelname){
    int i;
    if(*labels == NULL)
        return FALSE;
    for (i=0; i<size_of_labels; i++)
    {
        if (strncmp((*labels)[i]->name, labelname, strlen((*labels)[i]->name)) == 0)
            return (*labels)[i];
    }
    return NULL;
}

BOOLEAN free_tables(labelPtr *tables, int size){
    int i;
    for (i = 0; i < size; i++)
    {
        tables[i]->where_mentioned;
        free(tables[i]->name);
        free(tables[i]);
    }
    free(tables);
    return TRUE;
}
  
