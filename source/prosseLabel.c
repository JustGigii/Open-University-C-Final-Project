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
    if (strlen(operand[0]) > MAX_SIZE_OF_LABLE)
        return LABEL_TO_MUCH;
    if (check_no_save_word(operand[0]) == FALSE)
        return SAVE_WORLD;
    label = cheack_Label_Exist(tables, *tablesize, operand[0]);
    if (label != NULL)
    {
        if (label->lineNum != 0)
            return LABEL_ALREADY_EXIST;
        label->lineNum = *instructionCount;
        is_in_table=TRUE;
    }

    if (label == NULL)
    {
        label = create_label(operand[0], *instructionCount);
        if (label == NULL)
            return FAILURE_CANNOT_ALLOCATE_MEMORY;
    }
    
    label->type = (strcmp(operand[1], ".string") == 0) ? STRING : (strcmp(operand[1], ".data") == 0) ? DATA
                                                                                                     : CODE;
    *deltacount = enterdatatoline(size, line->lineNum, operand, line, &status, tables, tablesize);
    if (*deltacount == -1)
    {
        free(label);
        return status;
    }

    /* label->lineNum = *instructionCount;*/
    if (!is_in_table)
    {
        *tables = AddtoLabelTable(*tables, label, tablesize);
    }
    return SUCCESS;
}

BOOLEAN processString(char *tav, LinePtr line)
{
    int asciiValue, size = strlen(tav);

    while (*tav != '"')
    {
        if (*tav == '\\')
        {          /* Check for escape sequence */
            tav++; /* Move to the next character */
            asciiValue = processEscapeSequence(*tav);
            if (asciiValue == -1)
                return FALSE;
        }
        else
            asciiValue = *tav;

        line->assemblyCode[line->assemblyCodeCount] = asciiValue;
        line->assemblyCodeCount++;
        tav++;
    }
    return TRUE;
}
SATATUS processData(char **word, int wordcount, LinePtr line, int size)
{
    int i, converted;
    line->assemblyCode = malloc(wordcount - 2);
    if (line->assemblyCode == NULL)
        return FAILURE_CANNOT_ALLOCATE_MEMORY;
    for (i = 1; i < wordcount; i++)
    {
        char *data = word[i];
        if (data[strlen(data) - 1] != ',' && i < wordcount - 1 && word[i + 1][0] != ',')
        {
            free(line->assemblyCode);
            return MISSING_COMMA;
        }
        if (data[strlen(data) - 1] == ',')
            data[strlen(data) - 1] = '\0';
        else if (i < wordcount - 1 && word[i + 1][0] == ',')
            i++;

        if (data[0] == '+' || data[0] == '-')
        {
            converted = atoi(data + 1);
            if (converted == 0)
            {
                free(line->assemblyCode);
                return NOT_NUMBER;
            }
            if (converted > MAX_NUMBER || -converted < MIN_NUMBER)
            {
                free(line->assemblyCode);
                return FAILURE_OUT_OF_RANGE;
            }
            converted = (data[0] == '+') ? converted : -converted;
        }
        else
        {
            converted = atoi(data);
            if (converted == 0)
            {
                free(line->assemblyCode);
                return NOT_NUMBER;
            }
            if (converted > MAX_UNUMBER)
            {
                free(line->assemblyCode);
                return FAILURE_OUT_OF_RANGE;
            }
        }
        line->assemblyCode[line->assemblyCodeCount] = converted;
        ++line->assemblyCodeCount;
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
        result = processDirectives(sizewords - 1, operand + 1, line, status);
        if (result == -1)
        {
            return -1;
        }
        return result;
    }
    else
    {
        /* Process non-directive instructions */
        line->assemblyCode = cheackSentece(operand + 1, sizewords - 1, table, tablesize, status, line->lineNum, &sizeofdata);
        if (*status != SUCCESS && *status != WAIT_TO_ALL_LIBEL)
        {
            print_error(*status, line->lineNum, line->line);
            return -1;
        }
        line->assemblyCodeCount += sizeofdata;
    }
    return line->assemblyCodeCount;
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

int processDirectives(int sizewords, char **operand, LinePtr line, SATATUS *status)
{
    int sizeofdata;
    char *tav;

    if (strcmp(operand[0], ".string") == 0)
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
        if (!processString(tav, line))
        {
            *status = FAILURE;
            printf("in line %d: \"%s\": Undefined string\n", line->lineNum, line->line);
            free(line->assemblyCode);
            return -1;
        }
        /* Null-terminate the processed string */
        line->assemblyCode[line->assemblyCodeCount] = '\0';
        return ++line->assemblyCodeCount;
    }
    else if (strcmp(operand[0], ".data") == 0)
    {
        *status = processData(operand, sizewords, line, sizeofdata);
        if (*status != SUCCESS)
        {

            free(line->assemblyCode);
            return -1;
        }
        return line->assemblyCodeCount;
    }

    /* If the directive is neither .string nor .data, return an error */
    *status = FAILURE;
    return -1;
}
labelPtr create_label(const char *name, int lineNum)
{
    int i=0;
    labelPtr label = malloc(sizeof(labelstruct));
    if (label == NULL)
    {
        return NULL;
    }
    i = (name[strlen(name) - 1] == ':') ? 1 : 0;
    label->name = strndup(name, strlen(name) - i);
    label->lineNum = lineNum;
    label->is_entry = FALSE;
    label->is_extern = FALSE;
    return label;
}