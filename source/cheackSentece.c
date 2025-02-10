#include "../header/cheackSentece.h"

labelPtr ** globtables;
int size_of_gloabal_table;
int timein = 0;
unsigned int extract_bits(int value, BIT_START start_bit, BIT_LENGHT length,SATATUS *peola) {
    /* Ensure start_bit and length are within valid range */
    if (start_bit < 0 || start_bit >= 24 || length <= 0 || start_bit + length > 24) {
        *peola = FAILURE_OUT_OF_RANGE;
        return 0; /* Return 0 for invalid input */
    }

    return ((((unsigned int)1 << length) - 1)&value)<<start_bit-1;
}
/*only for checking*/
void print_binary(unsigned int value, int num_bits) {
    int i;
    for (i = num_bits - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

int * cheackSentece(char **words, int sizewords,labelPtr ** tables, int* tablesize ,SATATUS *status,int linenumber,int * sizeofSentece)
{
    int * binarycode;
    int  sizeofoprands = 0, i;
    char **oprands, *combineorands;
    globtables =tables;
    size_of_gloabal_table= *tablesize;
    *status = check_name_erorr( words, sizewords);
    if (*status != SUCCESS)
        return NULL;
    /* cheack for multiple space in the oprands*/
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
        *status =TO_MANY_PARAMETERS;
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
    if(oprands==NULL) 
    {
     /* free the memory allocated*/
     if(sizeofoprands>0) free(combineorands);

        *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
        return NULL;
    }
    /* check for error missing comma in the oprands */
    if(sizeofoprands!=0 && sizeofoprands>=sizewords-1)
    {
        /* check for error or excute the command */
    *status = SUCCESS;
     binarycode =oprandshandler(words[0], oprands, sizeofoprands,status,linenumber,sizeofSentece);
    }
    else
     *status = MISSING_PARAMETER;
    /* free the memory allocated*/
    freeIneersplit(oprands, sizeofoprands);
    /* free the combin eorands if initialized*/
    if(sizeofoprands>0) free(combineorands);
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
    if (istwooprand(input)) return TRUE;
    if(isoneoprand(input)) return TRUE;   
    if(is_no_oprand(input)) return TRUE;
    return FALSE;
}
int * oprandshandler(char *commandname, char **oprands, int sizeofoprands,SATATUS *status, int* sizeofSentece,int line_number)
{
    *status = SUCCESS;
    int *x; 
    int number =0;
    int type=-1;
    unsigned opcode=-1;
    labelPtr label= NULL;
    if(sizeofoprands==0)
    {
        x = (int *)malloc(sizeof(int));
    if (x == NULL)
        {
            *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
            return NULL;
        }
    x[0] = 4;
        if(is_no_oprand(commandname)==FALSE )
        {
            *status = MISSING_PARAMETER;
            free(x);
            return NULL;
        }
         *x |=(srtcmp(commandname, "stop")==0)? STOP:RTS;
         *sizeofSentece = 1;
         return x;
    }
    if (sizeofoprands == 1)
    {
         if(is_one_oprand(commandname)==FALSE )
        {
            *status = MISSING_PARAMETER;
            free(x);
            return NULL;
        }
        number =cheackoprandtype(oprands[0],&type);  
        x =(type!=3)? (int *)malloc(sizeof(int)*2):(int *)malloc(sizeof(int));
        if (x == NULL)
        {
        *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
        return NULL;
        }
        sizeofSentece= (type!=3)? 2:1;
        x[0] = 4;
        x[0] |= extract_bits(type,DS,LEN_DS,status);
        if(type == 3 || type ==1)
        {
          opcode = (strcmp(commandname, "clr") == 0)?CLR:-1;
          opcode = (strcmp(commandname, "not") == 0)?NOT:-1;
          opcode = (strcmp(commandname, "inc") == 0)?INC:-1;
          opcode = (strcmp(commandname, "dec") == 0)?DEC:-1;
          opcode = (strcmp(commandname, "red") == 0)?RED:-1;
          opcode = (strcmp(commandname, "prn") == 0)?PRN:-1;
            if (type==3) 
            {
                if(opcode == -1)
                {
                  *status = ILLEGAL_ADDRESSING;
                    free(x);
                    return NULL;  
                }
                x[0] |= extract_bits(number,RD,LEN_RD,status);
                return x;
            }
        } 

        
                label = findlabel(oprands[0],globtables, size_of_gloabal_table);
                if (label == NULL&& timein >=2)
                {
                    *status = ILLEGAL_ADDRESSING;
                    free(x);
                    return NULL;
                }
                if(label != NULL)
                {
                    x[1] = (label->isentry)?2:1; /* 2 mean R 1 and E,A 0. 1 MEAN E 1 AND R,A 0*/
                    x[1] |= label->lineNum<<3;
                }
    }
}


int cheackoprandtype(char const * oprand,int* type)
{
    labelPtr label= NULL;
    int number=-1;
    int minus=1;
    switch (oprand[0])
    {
    case '#':
        *type = 0;
        if(oprand[1]=="+"||oprand[1]=="-")
        {
            minus= oprand[1]=='-'? -1:1;
            number = atoi(oprand+2);
        }
        else
            number = atoi(oprand+1);
        if (number == -1&& strcmp(oprand,"#-1")!=0)
            *type = -1;
        break;

        case 'r':
        number = atoi(oprand+1);
        if (number > 7 || number < 0)
            *type = -1;
        else
            *type = 3;
        break;
        case '&':
        *type =2;
        break;
    default:
        *type = 1;
        break;
    }
    return number;
}
