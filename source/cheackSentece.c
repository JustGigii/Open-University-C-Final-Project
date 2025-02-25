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

int process_sentence(LinePtr line, char **strarray, int size, labelPtr **tables, int *tablesize, SATATUS *status)
{

    int deltacount = 0;
    /*create the binary code*/
    unsigned int *x = cheackSentece(strarray, size, tables, tablesize, status, line->lineNum, &deltacount);
    /*check for errors in the binary code*/
    if (*status != SUCCESS && *status != DATA_HANDLER && *status != WAIT_TO_ALL_LIBEL)
    {
        return -1;
    }
    /*handel if found data without label*/
    if (*status == DATA_HANDLER )
    {
        /*ingnore the data in the second run*/
        if (assembly_run == 2)
        {
            *status = SUCCESS;
            return 0;
        }
        /*add the correct data to the binary code*/
        deltacount = processDirectives(size, strarray, line, status,FALSE);
        if(*status == SUCCESS)
        {
            /*add how many line we add*/
            data_line_couter += deltacount; /*add how many line we add to data sigment*/
            return deltacount;
        }
        else 
        return -1;
    }
    /*handel if found label in code and is not in table*/
    if (*status == WAIT_TO_ALL_LIBEL)
    {
        /*handel no found in second run*/
        if (assembly_run == 2)
        {
            *status = LABEL_NOT_FOUND;
            return 0;
        }
        *status =SUCCESS;
        if(x != NULL)
        free(line->assemblyCode);/*free the binary code to enter the new one with the label*/
    }
    
        /*add the correct data to the binary code*/
        line->assemblyCode = x;
        /*add how many line we add*/
        line->assemblyCodeCount = deltacount;
    
    if (assembly_run < 2)
    {
        /*add how many line we add to code sigment*/
        code_line_couter += deltacount;
        *status =SUCCESS;
    }
    return deltacount;
}

unsigned int *cheackSentece(char **words, int sizewords, labelPtr **tables, int *tablesize, SATATUS *status, int linenumber, int *sizeofSentece)
{
    int *binarycode;
    int sizeofoprands = 0, i;
    char **oprands, *combineorands;
    labelPtr label;
    globtables = tables;
    size_of_gloabal_table = *tablesize;
    /*check for label and data*/
    if(strcmp(*words,".string")==0|| strcmp(*words,".data")==0)
    {
        *status =DATA_HANDLER;
        return NULL;
    }
    /*check for extern*/
    if(strcmp(*words,".extern")==0 )
    {
        /* ingnore the extern in the second run*/
        if(assembly_run <= 2)
        return NULL;
        /*check if the label is already in the table*/
        if(cheack_Label_Exist(tables, *tablesize, words[1]) != NULL)
        {
            *status = LABEL_ALREADY_EXIST; /*the label is already in the table is a erro*/
            return NULL;
        }
        /*mark on gloabal variable the sentense as extern*/
        is_extern = TRUE;
        /*add the label to the table*/
        labelPtr label = create_label(words[1], 0);
        if (label == NULL) {
            *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
            return NULL;
        }
        /*mark label as extern*/
        label->is_extern = TRUE;
        /*add the label to the table*/
        *tables = AddtoLabelTable(*tables, label, tablesize);
        return NULL;
    }
    /*check for entry*/
    if (strcmp(*words,".entry")==0)
    {

        /* ingnore the entry add when only the label defined*/
        if(assembly_run < 2)
        {
            *status = WAIT_TO_ALL_LIBEL;
            return NULL;
        }
        label = cheack_Label_Exist(tables, *tablesize, words[1]); /*check if the label is already in the table*/
        if (label == NULL) /*the label is not in the table in the second run is a erro */
           *status = LABEL_NOT_FOUND;
        else if(label->is_entry==TRUE || label->is_extern==TRUE) /* check if the symbol is already in the table*/
            *status = LABEL_ALREADY_EXIST; /*the label is already have a symbol is a erro*/
        else
        {
                            /* mark on gloabal variable the sentense as entry*/
        is_intern = TRUE;
        /*mark label as entry*/
        label->is_entry = TRUE;
        }
        return NULL;
    }
    /*check for line defined correct*/
    *status = check_name_erorr(words, sizewords);
    if (*status != SUCCESS)
        return NULL;
    /* cheack for multiple space in the oprands*/
    if(sizewords == 1) /* if only command name*/
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
