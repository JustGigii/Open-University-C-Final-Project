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
    labelPtr label=NULL;
    BOOLEAN is_in_table = FALSE;
    *deltacount = -1;
    if (strlen(operand[0]) > MAX_SIZE_OF_LABLE) /* Check if the label is too long */
        return LABEL_TO_MUCH; 
    if (check_no_save_word(operand[0]) == FALSE) /* Check if the label is a reserved word */
        return SAVE_WORLD;
    if (CheckLableName(operand[0]) == FALSE) /* Check if the label is valid */
        return ILIGAL_LABEL_NAME; 
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

        *deltacount = enterdatatoline(size, operand, line, &status, tables, tablesize); /* Add the data to the line */
        if (*deltacount == -1) /* if there is an error*/
        {
            if (label!=NULL)
            {
                free(label);
            }
            return status;
        }
        if(assembly_run < 2) /* if the first run add to the table*/
        *tables = AddtoLabelTable(*tables, label, tablesize);
    
    return SUCCESS;
}


unsigned int * processString(char *tav,int *sizeofdata)
{
    int i;
    unsigned int * data = malloc(strlen(tav));
    int asciiValue; /* Get the size of the string */
    if(data == NULL)
        return NULL;
    while (*tav != '\"') /* Loop until the end of the string */
    {
        if (*tav == '\\') /* Check for special characters */
        {          /* Check for escape sequence */
            tav++; /* Move to the next character */
            asciiValue = processEscapeSequence(*tav); /* Get the ASCII value */
            if (asciiValue == -1)/* Unrecognized escape sequence */
                return NULL;
        }
        else
            asciiValue = *tav;

        data[*sizeofdata] = asciiValue; /* Add the ASCII value to the array */
            *sizeofdata+=1; /* Increment the size of the array */
        tav++; /* Move to the next character */
    }
    data[*sizeofdata] =0; /*add null terminator*/
    *sizeofdata+=1; /* Increment the size of the array */
    return data;
}
SATATUS processData(char **word, int wordcount, LinePtr line, int size,BOOLEAN has_lable)
{
    int i, converted;
    char *data;
    unsigned int unsingedconverted; /*convert the number to unsigned to show binary*/
    unsigned int  *arrayofdata /*convert the number to unsigned to show binary*/;
    i = has_lable ? 2 : 1;
    arrayofdata = malloc(wordcount - i); /* Allocate memory for the array and handel lines with or without lables*/
    if (arrayofdata == NULL) 
        return FAILURE_CANNOT_ALLOCATE_MEMORY;
    for (i = 1; i < wordcount; i++)
    {
        data = word[i]; /* Get the data to convert ez to debug */
        if (data[strlen(data) - 1] != ',' && i < wordcount - 1 && word[i + 1][0] != ',') /* Check if there is a comma btween values */
        {
            free(arrayofdata);
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
                free(arrayofdata);
                return NOT_NUMBER;
            }
            if (converted > MAX_NUMBER || -converted < MIN_NUMBER) /* Check the number is valid  */
            {
                free(arrayofdata);
                return FAILURE_OUT_OF_RANGE;
            }
            if(data[0] == '+' && converted < 0) 
                return FAILURE_OUT_OF_RANGE;
            converted = (data[0] == '+') ? converted : -converted; /* Convert the data to an integer */
            unsingedconverted = converted; /*convert the number to unsigned to show binary*/
        }
        else
        {
            unsingedconverted = atoi(data); /* Convert the data to an integer */
            if (unsingedconverted == 0) /* Check the convert is valid  */
            {
                free(arrayofdata);
                return NOT_NUMBER;
            }
            if (unsingedconverted > MAX_UNUMBER) /* Check the number is valid unsinged  */
            {
                free(arrayofdata);
                return FAILURE_OUT_OF_RANGE;
            }
        }
       
        arrayofdata[line->assemblyCodeCount++] = unsingedconverted; /* Add the converted data to the array */
        
    }
    line->assemblyCode = arrayofdata;
    return SUCCESS;
}
int enterdatatoline(int sizewords,char **operand, LinePtr line, SATATUS *status, labelPtr **table, int *tablesize)
{
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
labelPtr* AddtoLabelTable(labelPtr* table, labelPtr label, int *size)
{
    /* Allocate or re-allocate depending on whether the table is empty */
    labelPtr* newtable;
    
    if (*size == 0) {
        /* If size == 0, we are creating a new array for 1 element */
        newtable = malloc(sizeof(labelPtr));
    } else {
        /* If size != 0, we expand the existing array by 1 element */
        newtable = realloc(table, (*size + 1) * sizeof(labelPtr));
    }
    
    /* Check if malloc/realloc failed */
    if (!newtable) {
        return NULL;
    }
    
    /* Store the new label at the end of the array */
    newtable[*size] = label;
    
    /* Increase the size by 1 */
    (*size)++;
    
    /* Return the new pointer to the array (may be the same as the old one) */
    return newtable;
}

int processDirectives(int sizewords, char **operand, LinePtr line, SATATUS *status, BOOLEAN has_lable)
{
    int sizeofdata=0;
    char *tav;
    unsigned int * data = NULL;
    *status = SUCCESS;
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
        sizeofdata=0;
        data=processString(tav, &sizeofdata);
        if (data==NULL) /* Process the string is faild */
        {
            *status = FAILURE;
            printf("in line %d: \"%s\": Undefined string\n", line->lineNum, line->line);
            free(line->assemblyCode);
            return -1;
        }
        /* Null-terminate the processed string */
        line->assemblyCode =data;
        line->assemblyCodeCount = sizeofdata;
        line->assemblyCode[sizeofdata] = 0;
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

BOOLEAN CheckLableName(const char * label)
{
    const char* tav = label;
    int counter=0;
    while (*tav != ':')
    {
        if(!((*tav>= 'a'&& *tav<='z')  || (*tav>= 'A'&& *tav<='Z') || (*tav>= '0'&& *tav<='9'))) /* Check if the character is valid */
            return FALSE;
        tav++;
        counter++; /* Increment the counter */
    }
    if (counter == strlen(label)-1) /* Check if not have ':' in the middle of the lablel*/
        return TRUE;
    return FALSE;

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