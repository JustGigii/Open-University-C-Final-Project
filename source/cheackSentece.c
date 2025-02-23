#include "../header/cheackSentece.h"

labelPtr **globtables;
int size_of_gloabal_table;

unsigned int extract_bits(int value, int start_bit, int length, SATATUS *peola)
{
    /* Ensure start_bit and length are within valid range */
    if (start_bit < 0 || start_bit >= 24 || length <= 0 || start_bit + length > 24)
    {
        *peola = FAILURE_OUT_OF_RANGE;
        return 0; /* Return 0 for invalid input */
    }

    return ((((unsigned int)1 << length) - 1) & value) << start_bit;
}
/*only for checking*/
void print_binary(unsigned int value, int num_bits)
{
    int i;
    for (i = num_bits - 1; i >= 0; i--)
    {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

unsigned int *cheackSentece(char **words, int sizewords, labelPtr **tables, int *tablesize, SATATUS *status, int linenumber, int *sizeofSentece)
{
    int *binarycode;
    int sizeofoprands = 0, i;
    char **oprands, *combineorands;
    labelPtr label;
    globtables = tables;
    size_of_gloabal_table = *tablesize;
    if(strcmp(*words,".string")==0|| strcmp(*words,".data")==0)
    {
        *status =DATA_HANDLER;
        return ;
    }
    if(strcmp(*words,".extern")==0 )
    {

        if(cheack_Label_Exist(tables, *tablesize, words[1]) != NULL)
        {
            *status = LABEL_ALREADY_EXIST;
            return NULL;
        }
        labelPtr label = create_label(words[1], 0);
        if (label == NULL) {
            *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
            return NULL;
        }
        label->is_extern = TRUE;
        *tables = AddtoLabelTable(*tables, label, tablesize);
    }
    if (strcmp(*words,".entry")==0)
    {
        if(assembly_run < 2)
        {
            *status = WAIT_TO_ALL_LIBEL;
            return NULL;
        }
        label = cheack_Label_Exist(tables, *tablesize, words[1]);
        if (label == NULL)
           *status = LABEL_NOT_FOUND;
        else if(label->is_entry==TRUE || label->is_extern==TRUE)
            *status = LABEL_ALREADY_EXIST;
        else
        {
        label->is_entry = TRUE;
        }
        return NULL;
    }
    *status = check_name_erorr(words, sizewords);
    if (*status != SUCCESS)
        return NULL;
    /* cheack for multiple space in the oprands*/
    if(sizewords == 1)
    {
        *status = SUCCESS;
        return oprandshandler(words[0], NULL, 0, status,sizeofSentece ,linenumber);
    }
    if (sizewords > 2)
    {
        /* combine the oprands */
        combineorands = combineStrings(words + 1, sizewords - 1, "");

        if (combineorands == NULL)
        {
            *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
            return NULL;
        }
    }
    else
        combineorands = words[1];
    /* check for error comma in the end of oprands */
    if (combineorands[strlen(combineorands) - 1] == ',')
    {
        *status = TO_MANY_PARAMETERS;
        return NULL;
    }
    /* check for multiple comma in the oprands */
    if (strstr(combineorands, ",,") != NULL)
    {
        *status = MULTIPLECOMMAS;
        return NULL;
    }
    /* split the oprands */
    oprands = Split(combineorands, ",", &sizeofoprands);
    if (oprands == NULL)
    {
        /* free the memory allocated*/
        if (sizeofoprands > 0)
            free(combineorands);

        *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
        return NULL;
    }
    /* check for error missing comma in the oprands */
    if (sizeofoprands != 0 && sizeofoprands >= sizewords - 1)
    {
        /* check for error or excute the command */
        *status = SUCCESS;
        binarycode = oprandshandler(words[0], oprands, sizeofoprands, status,sizeofSentece ,linenumber);
    }
    else
        *status = MISSING_PARAMETER;
    /* free the memory allocated*/
    freeIneersplit(oprands, sizeofoprands);
    /* free the combin eorands if initialized*/
    if (sizeofoprands > 0)
        free(combineorands);
    return binarycode;
}

SATATUS check_name_erorr(char **strarray, int sizeofarray)
{
    /* check for comma in the command name */
    if (strarray[0][strlen(strarray[0]) - 1] == ',')
        return ILLEGAL_COMMA;
    /* check if the command exists */
    if (isreservedWords(strarray[0]) == FALSE)
        return MISSING_COMMNAD;
    /* check for extra text after the command stop */
    if (is_no_oprand(strarray[0]) == TRUE && sizeofarray > 1)
    {
        return TO_MANY_PARAMETERS;
    }
    return SUCCESS;
}
BOOLEAN is_one_oprand(char *input)
{
    int i;
    /* check if the command is in all the commands with one operand */
    for (i = 0; i < MY_RESERVED_ONE_OPRAND_WORDS_COUNT; i++)
    {
        if (strcmp(input, my_reserved_one_oprand_words[i]) == 0)
            return TRUE;
    }
    return FALSE;
}
BOOLEAN is_two_oprand(char *input)
{
    int i;
    /* check if the command is in all the commands with two operands */
    for (i = 0; i < MY_RESERVED_TWO_OPRAND_WORDS_COUNT; i++)
    {
        if (strcmp(input, my_reserved_Two_oprand_words[i]) == 0)
            return TRUE;
    }
    return FALSE;
}
BOOLEAN is_no_oprand(char *input)
{
    int i;
    /* check if the command is in all the commands with two operands */
    for (i = 0; i < MY_RESERVED_NO_OPRAND_WORDS_COUNT; i++)
    {
        if (strcmp(input, my_reserved_no_oprand_words[i]) == 0)
            return TRUE;
    }
    return FALSE;
}
BOOLEAN isreservedWords(char *input)
{
    /* check if the command is in all the reserved words */
    if (is_two_oprand(input))
        return TRUE;
    if (is_one_oprand(input))
        return TRUE;
    if (is_no_oprand(input))
        return TRUE;
    return FALSE;
}
unsigned int *oprandshandler(char *commandname, char **oprands, int sizeofoprands, SATATUS *status, int *sizeofSentece, int line_number)
{
    *status = SUCCESS;
    unsigned int *x;
    int numberdest = 0;
    int numbersource = 0;
    int typedest = -1;
    int typesource = -1; 
    unsigned int opcode = -1;
    labelPtr label = NULL;
    if (sizeofoprands == 0)
    {
        x = (unsigned int *)malloc(sizeof(unsigned int));
        if (x == NULL)
        {
            *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
            return NULL;
        }
        x[0] = 4;
        if (is_no_oprand(commandname) == FALSE)
        {
            *status = MISSING_PARAMETER;
            free(x);
            return NULL;
        }
        *x |= (strcmp(commandname, "stop") == 0) ? STOP : RTS;
        *sizeofSentece = 1;
    }
    if (sizeofoprands == 1)
    {
        if (is_one_oprand(commandname) == FALSE)
        {
            *status = MISSING_PARAMETER;
            free(x);
            return NULL;
        }
        numberdest = cheackoprandtype(oprands[0], &typedest);
        if (typedest == -1)
        {
            *status = MISSING_PARAMETER;
            free(x);
            return NULL;
        }
        *sizeofSentece = (typedest != 3) ? 2 : 1;
        x = (unsigned int *)malloc(sizeof(unsigned int) * (*sizeofSentece));
        if (x == NULL)
        {
            *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
            return NULL;
        }
        x[0] = 4;
        x[0] |= extract_bits(typedest, DS, LEN_DS, status);
        if (typedest == 3 || typedest == 1)
        {
            opcode = (strcmp(commandname, "clr") == 0 && opcode == -1) ? CLR : opcode;
            opcode = (strcmp(commandname, "not") == 0 && opcode == -1) ? NOT : opcode;
            opcode = (strcmp(commandname, "inc") == 0 && opcode == -1) ? INC : opcode;
            opcode = (strcmp(commandname, "dec") == 0 && opcode == -1) ? DEC : opcode;
            opcode = (strcmp(commandname, "red") == 0 && opcode == -1) ? RED : opcode;
            opcode = (strcmp(commandname, "prn") == 0 && opcode == -1) ? PRN : opcode;
            if (typedest == 3)
            {
                if (opcode == -1)
                {
                    *status = ILLEGAL_ADDRESSING;
                    free(x);
                    return NULL;
                }
                x[0]|=opcode;
                x[0] |= extract_bits(numberdest, RD,LEN_RD, status);
               
                return x;
            }
        }
        if ((typedest == 1 || typedest == 2) && opcode == -1)
        {
            opcode = (strcmp(commandname, "jmp") == 0 && opcode == -1) ? JMP : opcode;
            opcode = (strcmp(commandname, "bne") == 0 && opcode == -1) ? BNE : opcode;
            opcode = (strcmp(commandname, "jsr") == 0 && opcode == -1) ? JSR : opcode;
        }
        if (strcmp(commandname, "prn") == 0 && typedest == 2 && opcode ==-1)
        {
            *status = ILLEGAL_ADDRESSING;
            free(x);
            return NULL;
        }
        else
            opcode = PRN;
        if (opcode == -1)
        {
            *status = TO_MANY_PARAMETERS;
            free(x);
            return NULL;
        }
        x[0] |= opcode;
        x[1] = process_type(label, oprands[0], typedest, numberdest, line_number, status);

    }

    if (sizeofoprands == 2)
    {
        if (is_two_oprand(commandname) == FALSE)
        {
            *status = TO_MANY_PARAMETERS;
            free(x);
            return NULL;
        }
        numbersource = cheackoprandtype(oprands[0], &typesource);
        numberdest = cheackoprandtype(oprands[1], &typedest);
        if (typesource == -1 || typedest == -1)
        {
            *status = ILIGAL_VALUE;
            free(x);
            return NULL;
        }
        if (typedest == 2 || typesource == 2)
        {
            *status = ILLEGAL_ADDRESSING;
            return NULL;
        }
        *sizeofSentece = (typedest == 3 || typesource == 3) ? ((typedest == 3 && typesource == 3) ? 1 : 2) : 3;
        x = (unsigned int *)malloc(sizeof(unsigned int) * (*sizeofSentece));
        if (x == NULL)
        {
            *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
            return NULL;
        }
        x[0] = 4;
        x[0] |= extract_bits(typedest, DS, LEN_DS, status);
        x[0] |= extract_bits(typesource, SS, LEN_SS, status);
        if (typesource == 0 || typesource == 1 || typesource == 3)
        {
            if (typedest == 1 || typedest == 3)
            {
                opcode = strcmp(commandname, "mov") == 0 && opcode == -1 ? MOV : opcode;
                opcode = strcmp(commandname, "add") == 0 && opcode == -1 ? ADD : opcode;
                opcode = strcmp(commandname, "sub") == 0 && opcode == -1 ? SUB : opcode;
            }
            if (opcode == -1 && (typedest == 0 || typedest == 1 || typedest == 3))
            {
                opcode = strcmp(commandname, "cmp") == 0 && opcode == -1 ? CMP : opcode;
            }
        }
        if (opcode == -1 && typesource == 1 && (typedest == 1 || typedest == 3))
        {
            opcode = strcmp(commandname, "lea") == 0 && opcode == -1 ? LEA : opcode;
        }
        if(opcode == -1)
        {
            *status = TO_MANY_PARAMETERS;
        }
        x[0]|= opcode;
        if (typedest == 3 || typesource == 3)
        {
            if (typedest == 3)
                x[0] |= extract_bits(numberdest, RD, LEN_RD, status);
            if (typesource == 3)
                x[0] |= extract_bits(numbersource, RS, LEN_RS, status);
        }
        if(*sizeofSentece ==1)
        {
           
            return x;
        }
        if(*sizeofSentece==2)
        {
            x[1] =0; 
            /*the arrat size is 2 mean or first oprand is register or secend oprand is register*/
            x[1] |= process_type(label, oprands[0], typesource, numbersource, line_number, status);
            x[1] |= process_type(label, oprands[1], typedest, numberdest, line_number, status);
        }
        else
        {
            x[2] = process_type(label, oprands[0], typesource, numbersource, line_number, status);
            x[1] = process_type(label, oprands[1], typedest, numberdest, line_number, status);
        }
      
    }
   
    return x;
}

int cheackoprandtype(char const *oprand, int *type)
{
    labelPtr label = NULL;
    int number = -1;
    int minus = 1;
    switch (oprand[0])
    {
    case '#':
        *type = 0;
        if (oprand[1] == "+" || oprand[1] == "-")
        {
            minus = oprand[1] == '-' ? -1 : 1;
            number = atoi(oprand + 2);
        }
        else
            number = atoi(oprand + 1);
        if (number == -1 && strcmp(oprand, "#-1") != 0)
            *type = -1;
        break;

    case 'r':
        number = atoi(oprand + 1);
        if (number > 7 || number < 0)
            *type = -1;
        else
            *type = 3;
        break;
    case '&':
        *type = 2;
        break;
    default:
        *type = 1;
        break;
    }
    return number;
}
int process_type(labelPtr label, const char *labelname, int type, int number, int line_number, SATATUS *status)
{
    int num;
    int i = 0;
    if(type == 3)
        return 0; /*not need to add is a register*/
    if (assembly_run == 1)
    {
        *status = WAIT_TO_ALL_LIBEL;
        return 0;
    }
    if (type)
    {
        i = (type == 2) ? 1 : 0;
        label = cheack_Label_Exist(globtables, size_of_gloabal_table, labelname+i);
        if (label != NULL)
        {
            num = (label->is_extern) ? 1 : 2; /* 2 means R 1 and E,A 0. 1 means E 1 and R,A 0 */
            num |= (type == 1) ? (label->lineNum << 3) : ((label->lineNum - line_number) << 3);
            label->where_mentioned = (label->size_of_where_mentioned==0)?malloc(sizeof(int)):realloc(label->where_mentioned,sizeof(int)*(label->size_of_where_mentioned+1));
            if(label->where_mentioned==NULL)
            {
                status = FAILURE_CANNOT_ALLOCATE_MEMORY;
                return 0;
            }
            label->where_mentioned[label->size_of_where_mentioned]=line_number;
            label->size_of_where_mentioned++;
        }
        else
        {
            *status = WAIT_TO_ALL_LIBEL;
            return 0;
        }
    }
    else
    {
        num = 4;
        num |= number << 3;
    }
    return num;
}