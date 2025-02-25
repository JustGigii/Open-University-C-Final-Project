#include "../header/prosseLabel.h"

int processEscapeSequence(char nextChar)
{
    switch (nextChar)
    {
    case 't':
        return '\t'; /* Tab */
    case 'n':
        return '\n'; /* Newline */
    case 'r':
        return '\r'; /* Carriage Return */
    case 'v':
        return '\v'; /* Vertical Tab */
    case 'f':
        return '\f'; /* Form Feed */
    case 'b':
        return '\b'; /* Backspace */
    case 'a':
        return '\a'; /* Bell/Alert */
    case '\\':
        return '\\'; /* Backslash */
    case '\'':
        return '\''; /* Single Quote */
    case '\"':
        return '\"'; /* Double Quote */
    case '?':
        return '\?'; /* Question Mark */
    case '0':
        return '\0'; /* Null */
    default:
        return -1; /* Unrecognized escape sequence */
    }
}
SATATUS ProcessLabel(char **operand, LinePtr line, int *instructionCount, labelPtr **tables, int *tablesize, int size, int *deltacount)
{
    SATATUS status = SUCCESS;
    labelPtr label;
    BOOLEAN is_in_table = FALSE;
    if (strlen(operand[0]) > MAX_SIZE_OF_LABLE) /* Check if the label is too long */
        return LABEL_TO_MUCH; 
    if (check_no_save_word(operand[0]) == FALSE) /* Check if the label is a reserved word */
        return SAVE_WORLD;
    if (assembly_run < 2)   /* if the first run*/
    {
        label = cheack_Label_Exist(tables, *tablesize, operand[0]); /* Check if the label already exist */
        if (label != NULL) /* if the label already exist*/
        {
            if (label->lineNum != 0) /* if is not enrty or extern*/
                return LABEL_ALREADY_EXIST;
            label->lineNum = *instructionCount;
            is_in_table = TRUE;
        }

        if (label == NULL) /* if the label doesn't exist*/
        {
            label = create_label(operand[0], *instructionCount); /* Create a new label */
            if (label == NULL)
                return FAILURE_CANNOT_ALLOCATE_MEMORY;
        }
        /* check the type is code or data or string*/
        label->type = (strcmp(operand[1], ".string") == 0) ? STRING : (strcmp(operand[1], ".data") == 0) ? DATA
                                                                                                         : CODE;
    }
    /* label->lineNum = *instructionCount;*/
    if(assembly_run < 2 && is_in_table) return LABEL_ALREADY_EXIST; /* if the label already exist in the table in the first run*/

        *deltacount = enterdatatoline(size, line->lineNum, operand, line, &status, tables, tablesize); /* Add the data to the line */
        if (*deltacount == -1) /* if there is an error*/
        {
            free(label);
            return status;
        }
        if(assembly_run < 2) /* if the first run add to the table*/
        *tables = AddtoLabelTable(*tables, label, tablesize);
    
    return SUCCESS;
}

BOOLEAN processString(char *tav, LinePtr line)
{
    int asciiValue, size = strlen(tav); /* Get the size of the string */
    char tava;
    while (*tav != '"') /* Loop until the end of the string */
    {
        if (*tav == '\\') /* Check for special characters */
        {          /* Check for escape sequence */
            tav++; /* Move to the next character */
            asciiValue = processEscapeSequence(*tav); /* Get the ASCII value */
            if (asciiValue == -1)/* Unrecognized escape sequence */
                return FALSE;
        }
        else
            asciiValue = *tav;

        line->assemblyCode[line->assemblyCodeCount] = asciiValue; /* Add the ASCII value to the array */
        line->assemblyCodeCount++; /* Increment the size of the array */
        tav++; /* Move to the next character */
    }
    return TRUE;
}
SATATUS processData(char **word, int wordcount, LinePtr line, int size,BOOLEAN has_lable)
{
    int i, converted;
    char *data;
    i = has_lable ? 2 : 1;
    unsigned int unsingedconverted; /*convert the number to unsigned to show binary*/
    line->assemblyCode = malloc(wordcount - i); /* Allocate memory for the array and handel lines with or without lables*/
    if (line->assemblyCode == NULL) 
        return FAILURE_CANNOT_ALLOCATE_MEMORY;
    for (i = 1; i < wordcount; i++)
    {
        data = word[i]; /* Get the data to convert ez to debug */
        if (data[strlen(data) - 1] != ',' && i < wordcount - 1 && word[i + 1][0] != ',') /* Check if there is a comma btween values */
        {
            free(line->assemblyCode);
            return MISSING_COMMA;
        }
        if (data[strlen(data) - 1] == ',') /* Remove the comma to make the data valid to convert*/
            data[strlen(data) - 1] = '\0';
        else if (i < wordcount - 1 && word[i + 1][0] == ',') /* Remove the comma to make the data valid to convert*/
            i++;

        if (data[0] == '+' || data[0] == '-') /* Check is mean to postive or negative*/
        {
            converted = atoi(data + 1); /* Convert the data to an integer */
            if (converted == 0) /* Check the convert is valid  */
            {
                free(line->assemblyCode);
                return NOT_NUMBER;
            }
            if (converted > MAX_NUMBER || -converted < MIN_NUMBER) /* Check the number is valid  */
            {
                free(line->assemblyCode);
                return FAILURE_OUT_OF_RANGE;
            }
            converted = (data[0] == '+') ? converted : -converted; /* Convert the data to an integer */
        }
        else
        {
            converted = atoi(data); /* Convert the data to an integer */
            if (converted == 0) /* Check the convert is valid  */
            {
                free(line->assemblyCode);
                return NOT_NUMBER;
            }
            if (converted > MAX_UNUMBER) /* Check the number is valid unsinged  */
            {
                free(line->assemblyCode);
                return FAILURE_OUT_OF_RANGE;
            }
        }
        unsingedconverted = converted; /*convert the number to unsigned to show binary*/
        line->assemblyCode[line->assemblyCodeCount++] = unsingedconverted; /* Add the converted data to the array */
    }
    return SUCCESS;
}
int enterdatatoline(int sizewords, int *instractioncount, char **operand, LinePtr line, SATATUS *status, labelPtr **table, int *tablesize)
{
    int sizeofdata;
    int result;

    /* Use the new processDirectives function for .string and .data */
    if (strcmp(operand[1], ".string") == 0 || strcmp(operand[1], ".data") == 0)
    {
        if (assembly_run == 2) /* if the second run ignore the data in the second run*/
            return 0;
        /* Process the .string or .data directive */
        result = processDirectives(sizewords - 1, operand + 1, line, status,FALSE); 
        if (result == -1)
        {
            return -1;
        }
        /* Update the line count and the data line counter */
        data_line_couter += result;
        return result;
    }
    else
    {
        /* Process the rest of the instructions */
        result = process_sentence(line, operand + 1, sizewords - 1, table, tablesize, status);
    }
    return result;
}
labelPtr AddtoLabelTable(labelPtr *table, labelPtr label, int *size)
{

    LinePtr *newtable = (size == 0) ? malloc(sizeof(labelPtr)) : realloc(table, (*size + 1) * sizeof(labelPtr));
    if (!newtable)
        return NULL;
    newtable[*size] = label;
    *size += 1;
    return newtable;
}

int processDirectives(int sizewords, char **operand, LinePtr line, SATATUS *status, BOOLEAN has_lable)
{
    int sizeofdata;
    char *tav;

    if (strcmp(operand[0], ".string") == 0) /* Process the .string directive */
    {
        /* Check if there are exactly three words and the operand string is properly quoted */
        if (sizewords != 2 || operand[1][0] != '\"' || operand[1][strlen(operand[1]) - 1] != '\"')
        {
            *status = TO_MANY_PARAMETERS;
            return -1;
        }
        /* Skip the first quote */
        tav = operand[1] + 1;

        /* Allocate memory for the string without the quotes */
        line->assemblyCode = malloc(strlen(operand[1]) - 1);
        if (line->assemblyCode == NULL)
        {
            *status = FAILURE_CANNOT_ALLOCATE_MEMORY;
            return -1;
        }
        if (!processString(tav, line)) /* Process the string is faild */
        {
            *status = FAILURE;
            printf("in line %d: \"%s\": Undefined string\n", line->lineNum, line->line);
            free(line->assemblyCode);
            return -1;
        }
        /* Null-terminate the processed string */
        line->assemblyCode[line->assemblyCodeCount] = 0;
        line->assemblyCodeCount++;
        return line->assemblyCodeCount; /* Return the size of the string */
    }
    else if (strcmp(operand[0], ".data") == 0) /* Process the .data directive */
    {
        *status = processData(operand, sizewords, line, sizeofdata,has_lable); /* Process the data */
        if (*status != SUCCESS) /* If the data processing failed */
        {

            free(line->assemblyCode);
            return -1;
        }
        return line->assemblyCodeCount; /* Return the size of the data */
    }

    /* If the directive is neither .string nor .data, return an error */
    *status = FAILURE;
    return -1;
}
labelPtr create_label(const char *name, int lineNum)
{
    int i = 0;
    labelPtr label = malloc(sizeof(labelstruct));/* Allocate memory for the label */
    if (label == NULL)
    {
        return NULL;
    }
    i = (name[strlen(name) - 1] == ':') ? 1 : 0; /* Check if the label name ends with ':' */
    label->name = strndup(name, strlen(name) - i); /* Copy the label name */
    label->lineNum = lineNum; /* Set the line number */
    label->is_entry = FALSE; /* Initialize the entry flag */
    label->is_extern = FALSE; /* Initialize the extern flag */
    label->where_mentioned = NULL; /* Initialize the where_mentioned pointer */
    label->size_of_where_mentioned = 0; /* Initialize the size of where_mentioned */
    label->type = UNDEFINED; /* Initialize the label type */
    return label;
}