#include "../header/LineDetction.h"

const char *my_reserved_Two_oprand_words[] = {"mov", "cmp", "add", "sub", "lea"}; /* array of the reserved two oprand words*/
const char *my_reserved_one_oprand_words[] = { "clr", "not", "inc", "dec", "jmp",/* array of the reserved one oprand words*/
                                            "bne", "jsr", "red", "prn"};/* array of the reserved one oprand words*/
const char *my_reserved_no_oprand_words[] = { "rts","stop"};/* array of the reserved no oprand words*/

int assembly_run =0;/* 1 for the first run and 2 for the second run*/
int data_line_couter =0;    /* counter of the data line*/
int code_line_couter =0; /* counter of the code line*/
int extern_mention_counter =0; /* how many extern mention*/
BOOLEAN is_extern = FALSE; /* if the lines have extern*/
BOOLEAN is_intern = FALSE; /* if the lines have intern*/
labelPtr * CreateAssemblyLine(LinePtr heads,int * sizeofTables,SATATUS *status)
{
    BOOLEAN is_succsess = TRUE;
    SATATUS is_line_succsess = SUCCESS;
    int i;
    labelPtr *tables = NULL;
    int tablesize = 0, instructionCount = START_LINE;
    LinePtr temp = heads;
    assembly_run=1; /* strart the first run*/
    data_line_couter =0;    /* counter of the data line*/
    code_line_couter =0; /* counter of the code line*/
    extern_mention_counter =0; /* how many extern mention*/
    is_extern = FALSE; /* if the lines have extern*/
    is_intern = FALSE; /* if the lines have intern*/
    for ( i = 0; i < 2; i++) /* run only two times*/
    {    
    while (temp) /* check each line*/
    {
        /* convert the line to assembly code add to label table if succsess*/
        is_line_succsess = check_operand(temp, &tables, &tablesize, &instructionCount); 
        if (is_line_succsess != SUCCESS) /* if the line is not succsess*/
        {
            is_succsess = FALSE;
            /* print the error if found*/
            print_error(is_line_succsess, temp->lineNum, temp->line);
        }
        temp = temp->next; /* go to the next line*/
    }
    if(is_succsess==FALSE|| tables ==NULL) /* if the line is not succsess or the label table is empty we didn't need to run over again*/
        i=2;
    temp = heads; /* go back to the first line*/
    assembly_run = 2; /* start the second run*/
    }
    if(extern_mention_counter == 0)
        is_extern = FALSE;
    *status = (is_succsess ==TRUE)?SUCCESS:FAILURE; /* set the status*/
    *sizeofTables = tablesize; /* set the size of the label table*/
    return is_succsess? tables: NULL; /* return the label table if have label*/
}
SATATUS check_operand(LinePtr line, labelPtr ** tables, int* tablesize, int *instructionCount)
{
    SATATUS status = SUCCESS;
    int size=0, deltacount = 0;
    char ** strarray=NULL;
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
    /* check for label. lable start only with ':' */
    if (strarray[0][strlen(strarray[0]) - 1] == ':')
    {
        /* check if the label is valid */
        status =  ProcessLabel(strarray, line, instructionCount, tables, tablesize,size,&deltacount);

    }
    else
    {
        /* check if the command is valid */
        deltacount = process_sentence(line, strarray, size, tables, tablesize, &status);
    }
    if (assembly_run<2 && deltacount != -1) /* update the line number 'ic' if we are in the first run*/
    {
        line->lineNum =*instructionCount; /* update the line number*/
        *instructionCount += deltacount; /* update the instruction count*/
    }
    freeIneersplit(strarray, size); /* free the strarray*/
    return status;
}

BOOLEAN check_no_save_word(const char *label)
{
    int i;
    BOOLEAN ok =TRUE;
    /* check if the command is in all the commands with one operand */
     for (i = 0; i < MY_RESERVED_ONE_OPRAND_WORDS_COUNT && ok; i++)
    {
        if (strcmp(my_reserved_one_oprand_words[i], label) == 0)
            ok = FALSE;
    }
    /* check if the command is in all the commands with two operands */
    for (i = 0; i < MY_RESERVED_TWO_OPRAND_WORDS_COUNT && ok; i++)
    {
        if (strcmp(my_reserved_one_oprand_words[i], label) == 0)
            ok = FALSE;
    }
    /* check if the command is in all the commands with no operands */
    for (i = 0; i < MY_RESERVED_NO_OPRAND_WORDS_COUNT && ok; i++)
    {
        if (strcmp(my_reserved_no_oprand_words[i], label) == 0)
            ok = FALSE;
    }
    /* check if not a register */
    if (strlen(label) == 2 && label[0] == 'r' && label[1] >= '1' && label[1] <= '9')
    {
        ok = FALSE;
    }

    return ok;
}

labelPtr cheack_Label_Exist(labelPtr *labels[],int size_of_labels,const char * labelname){
    int i;
    /* check if the label is in the label table */
    if(*labels == NULL)
        return FALSE;
    /* check if the label is in the label table */
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
        /* free the where_mentioned array*/
        free(tables[i]->where_mentioned);
        /* free the name*/
        free(tables[i]->name);
        free(tables[i]);
    }
    free(tables);
    return TRUE;
}
  
