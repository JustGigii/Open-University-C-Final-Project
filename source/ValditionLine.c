#include "../header/ValditionLine.h"
#define CheackifSuccses(stat)                         \
    if (stat != SUCCESS && stat != WAIT_TO_ALL_LIBEL) \
    {                                                 \
        free(x);                                      \
        return NULL;                                  \
    }
unsigned int *oprandshandler(char *commandname, char **oprands, int sizeofoprands, SATATUS *status, int *sizeofSentece, int line_number)
{
    unsigned int *x;
    int numberdest = 0;
    int numbersource = 0;
    int typedest = -1;
    int typesource = -1;
    unsigned int opcode = -1;
    labelPtr label = NULL;
    *status = SUCCESS;
    if (sizeofoprands == 0)
    {
        x = (unsigned int *)malloc(sizeof(unsigned int)); /* Allocate memory for the opcode */
        if (x == NULL)
        {
            *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
            return NULL;
        }
        x[0] = 4;
        if (is_no_oprand(commandname) == FALSE) /* Check if the command is in the list of commands with no operands */
        {
            *status = MISSING_PARAMETER;
            free(x);
            return NULL;
        }
        *x |= (strcmp(commandname, "stop") == 0) ? STOP : RTS; /* Set the opcode based on the command name */
        *sizeofSentece = 1;                                    /* Set the size of the sentence */
    }
    if (sizeofoprands == 1)
    {
        if (is_one_oprand(commandname) == FALSE) /* Check if the command is in the list of commands with one operand */
        {
            *status = MISSING_PARAMETER;
            free(x);
            return NULL;
        }
        numberdest = cheackoprandtype(oprands[0], &typedest, status); /* get the type of the operand */
        CheackifSuccses(*status);
        if (typedest == -1)                                   /* Check if the operand is valid */
        {
            *status = MISSING_PARAMETER;
            free(x);
            return NULL;
        }
        *sizeofSentece = (typedest != 3) ? 2 : 1;                            /* Set the size of the sentence based on the type of the operand regsiter save on the first byte */
        x = (unsigned int *)malloc(sizeof(unsigned int) * (*sizeofSentece)); /* Allocate memory for the opcode */
        if (x == NULL)
        {
            *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
            return NULL;
        }
        x[0] = 4;                                           /* start the first byte with only A flag open */
        x[0] |= extract_bits(typedest, DS, LEN_DS, status); /* Set the destination type in the first byte */
        if (typedest == 3 || typedest == 1)                 /* if the operand is register or label address like in the task table */
        {
            opcode = (strcmp(commandname, "clr") == 0 && opcode == -1) ? CLR : opcode;
            opcode = (strcmp(commandname, "not") == 0 && opcode == -1) ? NOT : opcode;
            opcode = (strcmp(commandname, "inc") == 0 && opcode == -1) ? INC : opcode;
            opcode = (strcmp(commandname, "dec") == 0 && opcode == -1) ? DEC : opcode;
            opcode = (strcmp(commandname, "red") == 0 && opcode == -1) ? RED : opcode;
            opcode = (strcmp(commandname, "prn") == 0 && opcode == -1) ? PRN : opcode;
            if (typedest == 3) /* if the operand is register */
            {
                if (opcode == -1) /* if the opcode is not set */
                {
                    *status = ILLEGAL_ADDRESSING;
                    free(x);
                    return NULL;
                }
                x[0] |= opcode;                                       /* Set the opcode in the first byte */
                x[0] |= extract_bits(numberdest, RD, LEN_RD, status); /* Set the register number in the first byte */
                return x;
            }
        }
        if ((typedest == 1 || typedest == 2) && opcode == -1) /* if the operand is label address */
        {
            opcode = (strcmp(commandname, "jmp") == 0 && opcode == -1) ? JMP : opcode;
            opcode = (strcmp(commandname, "bne") == 0 && opcode == -1) ? BNE : opcode;
            opcode = (strcmp(commandname, "jsr") == 0 && opcode == -1) ? JSR : opcode;
        }
        
        if ((typedest == 0 || typedest == 2) && opcode == -1) 
           if (strcmp(commandname, "clr") == 0||strcmp(commandname, "not") == 0||strcmp(commandname, "inc") == 0
           ||strcmp(commandname, "dec") == 0||strcmp(commandname, "red") == 0) /* if the operand is label address or number */
           {
           *status = ILLEGAL_ADDRESSING;
           free(x);
           return NULL;
           }
        
        
        if (strcmp(commandname, "prn") == 0 && typedest == 2 && opcode == -1) /* if the operand is label address */
        {
            *status = ILLEGAL_ADDRESSING;
            free(x);
            return NULL;
        }
        else if (opcode == -1) /* if the opcode is not set */
            opcode = PRN;
        if (opcode == -1) /* if the opcode is not set */
        {
            *status = TO_MANY_PARAMETERS;
            free(x);
            return NULL;
        }
        x[0] |= opcode;                                                                                     /* Set the opcode in the first byte */
        x[1] = process_type(label, oprands[0], typedest, numberdest, line_number + 1, line_number, status); /* Set the currect vlue in the second byte */
    }

    if (sizeofoprands == 2) /* Check if the command has two operands */
    {
        if (is_two_oprand(commandname) == FALSE) /* Check if the command is in the list of commands with two operands */
        {
            if(is_one_oprand(commandname) == TRUE || is_no_oprand(commandname) == TRUE) /* Check if the command is in the list of commands with one or no operands */
                *status = TO_MANY_PARAMETERS;
            else
            *status = TO_MANY_PARAMETERS;
            free(x);
            return NULL;
        }
        numbersource = cheackoprandtype(oprands[0], &typesource, status); /* get the type of the source operand */
        CheackifSuccses(*status);/* Check if the operand is valid */
        numberdest = cheackoprandtype(oprands[1], &typedest, status);     /* get the type of the destination operand */
        CheackifSuccses(*status); /* Check if the operand is valid */
        if (typesource == -1 || typedest == -1)                   /* Check if the operand is valid */
        {
            *status = ILIGAL_VALUE;
            free(x);
            return NULL;
        }
        if (typedest == 2 || typesource == 2) /* Check if the operand is illegal type for the command */
        {
            *status = ILLEGAL_ADDRESSING;
            return NULL;
        }
        /*if in line have two registers we need only one byte if have one register we need two bytes. else we need three bytes*/
        *sizeofSentece = (typedest == 3 || typesource == 3) ? ((typedest == 3 && typesource == 3) ? 1 : 2) : 3; /* Set the size of the sentence */
        x = (unsigned int *)malloc(sizeof(unsigned int) * (*sizeofSentece));                                    /* Allocate memory for the sentence */
        if (x == NULL)                                                                                          /* Check if the memory allocation was successful */
        {
            *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
            return NULL;
        }
        x[0] = 4;                                                  /* start the first byte with only A flag open */
        x[0] |= extract_bits(typedest, DS, LEN_DS, status);        /* Set the destination type in the first byte */
        x[0] |= extract_bits(typesource, SS, LEN_SS, status);      /* Set the source type in the first byte */
        if (typesource == 0 || typesource == 1 || typesource == 3) /* if the source operand is register or label address like in the table */
        {
            if (typedest == 1 || typedest == 3) /* if the destination operand is register or label address like in the table */
            {
                opcode = strcmp(commandname, "mov") == 0 && opcode == -1 ? MOV : opcode;
                opcode = strcmp(commandname, "add") == 0 && opcode == -1 ? ADD : opcode;
                opcode = strcmp(commandname, "sub") == 0 && opcode == -1 ? SUB : opcode;
            }
            if (opcode == -1 && (typedest == 0 || typedest == 1 || typedest == 3)) /* if the destination operand is register or label address like in the table */
            {
                opcode = strcmp(commandname, "cmp") == 0 && opcode == -1 ? CMP : opcode;
            }
        }
        if (opcode == -1 && typesource == 1 && (typedest == 1 || typedest == 3)) /* if the source operand is register and the destination operand is register or label address like in the table */
        {
            opcode = strcmp(commandname, "lea") == 0 && opcode == -1 ? LEA : opcode;
        }
        if (opcode == -1) /* if the opcode is not set */
        {
            *status = ILLEGAL_ADDRESSING;
            free(x);
            return NULL;
        }
        x[0] |= opcode;                       /* Set the opcode in the first byte */
        if (typedest == 3 || typesource == 3) /* if the destination or source operand is register */
        {
            if (typedest == 3) /* if the destination operand is register add the first byte */
                x[0] |= extract_bits(numberdest, RD, LEN_RD, status);
            if (typesource == 3) /* if the source operand is register add the first byte */
                x[0] |= extract_bits(numbersource, RS, LEN_RS, status);
        }
        if (*sizeofSentece == 1) /*if the sentence size is 1 mean or first oprand is register or secend oprand is register*/
        {
            return x;
        }
        if (*sizeofSentece == 2) /*the arrat size is 2 mean or first oprand is register or secend oprand is register*/
        {
            x[1] = 0; /*start the second byte 0*/
            /*add value to the second byte if is register ignore*/
            x[1] |= process_type(label, oprands[0], typesource, numbersource, line_number + 1, line_number, status);
            CheackifSuccses(*status); /*check if the oprand is valid*/
                                      /*add value to the second byte if is register ignore */
            x[1] |= process_type(label, oprands[1], typedest, numberdest, line_number + 1, line_number, status);
            CheackifSuccses(*status); /*check if the oprand is valid*/
        }
        else /* the oprand size is not register*/
        {
            x[1] = process_type(label, oprands[0], typesource, numbersource, line_number + 1, line_number, status);
            CheackifSuccses(*status); /*check if the oprand is valid*/
            x[2] = process_type(label, oprands[1], typedest, numberdest, line_number + 2, line_number, status);
            CheackifSuccses(*status); /*check if the oprand is valid*/
        }
    }

    return x;
}

int cheackoprandtype(const char *oprand, int *type, SATATUS *status)
{
    int number = -1;
    int minus = 1;
    switch (oprand[0]) /* Check the first character of the operand */
    {
    case '#': /* Check if the operand is a register */
        *type = 0;
        if (oprand[1] == '+' || oprand[1] == '-') /* register can have + or - */
        {
            if(strlen(oprand+2) > 7)/* maxsimus digit can handel*/
            {
                *status = FAILURE_OUT_OF_RANGE;
                return -1;
            }
            minus = oprand[1] == '-' ? -1 : 1; /* set the sign of the number */
            number = atoi(oprand + 2);         /* get the number */
            number *= minus;
        }
        else
        {
            if(strlen(oprand+1) > 8) /* maxsimus digit can handel*/
            {
                *status = FAILURE_OUT_OF_RANGE;
                return -1;
            }
            number = atoi(oprand + 1);                  /* get the number */
        }
        if (number == -1 && strcmp(oprand, "#-1") != 0) /* check if the convert is succses */
        {
            *type = -1;
            *status = FAILURE_OUT_OF_RANGE;
            return -1;                                 /* the convert is failed */
        }  
        if(oprand[1] == '-' && number > 0)
        {
            *status = FAILURE_OUT_OF_RANGE;
            return -1;
        }  
        if(oprand[1] == '+' && number < 0)
        {
            *status = FAILURE_OUT_OF_RANGE;
            return -1;
        }
        if(oprand[1] != '-' && oprand[1] != '+' && number < 0)
        {
            *status = FAILURE_OUT_OF_RANGE;
            return -1;
        }
        break;

    case 'r':
        number = atoi(oprand + 1); /* get the register number */
        if (number > 7 || number < 0)
            *type = -1; /* the register is not valid */
        else
            *type = 3; /* the register is valid */
        break;
    case '&':
        *type = 2; /* the operand is an type 2 sorting hadel with process_type */
        break;
    default:
        *type = 1; /* the operand is an type 1 sorting hadel with process_type */
        break;
    }
    return number; /* return the number if is register or number */
}
int process_type(labelPtr label, const char *labelname, int type, int number, int line_number, int ogrinal_line_number, SATATUS *status)
{
    int num;
    int i = 0;
    if (type == 3)
        return 0;                       /*not need to add is a register*/
    if (assembly_run == 1 && type != 0) /* if the first run ingore this we do it in the second run*/
    {
        *status = WAIT_TO_ALL_LIBEL;
        return 0;
    }
    if (type) /* if the type is 1 or 2 */
    {
        i = (type == 2) ? 1 : 0;                                                      /* hanedle the '&' in type 2 */
        label = cheack_Label_Exist(globtables, size_of_gloabal_table, labelname + i); /* check if the label is in the table */
        if (label != NULL)
        {
            num = (label->is_extern) ? 1 : (type == 2) ? 4
                                                       : 2;                                             /* 2 means R 1 and E,A 0. 1 means E 1 and R,A 0 */
            num |= (type == 1) ? (label->lineNum << 3) : ((label->lineNum - ogrinal_line_number) << 3); /* add the line number */
            if (label->is_extern == TRUE)
            {
                label->where_mentioned = (label->size_of_where_mentioned == 0) ? malloc(sizeof(int)) : realloc(label->where_mentioned, sizeof(int) * (label->size_of_where_mentioned + 1)); /* add where is colde if is extern*/
                if (label->where_mentioned == NULL)                                                                                                                                         /* if the realloc is failed*/
                {
                    *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
                    return 0;
                }
                extern_mention_counter++;
                label->where_mentioned[label->size_of_where_mentioned] = line_number; /* add the line number*/
                label->size_of_where_mentioned++; /* increase the size of where_mentioned*/
            }
        }
        else
        {
            *status = WAIT_TO_ALL_LIBEL; /* the label is not in the table*/
            return 0;
        }
    }
    else /* if the type is 0 */
    {
        num = 4; /* open the A bit*/
        num |= number << 3; /* add the number*/
    }
    return num;
}