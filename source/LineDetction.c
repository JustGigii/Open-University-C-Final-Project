#include "../header/LineDetction.h"

const char *reservedWords[] = {
    "mov", "cmp", "add", "sub", "lea",
    "clr", "not", "inc", "dec", "jmp",
    "bne", "jsr", "red", "prn", "rts",
    "stop"};

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
BOOLEAN print_operand(LinePtr heads)
{
    int i;
    labelPtr *tables = NULL;
    int tablesize = 0, instructionCount = START_LINE;
    LinePtr temp = heads;
    while (temp)
    {
        if (check_operand(temp, &tables, &tablesize, &instructionCount) == FALSE)
            return FALSE;
        temp = temp->next;
    }

    
}
BOOLEAN check_operand(LinePtr line, labelPtr ** tables, int* tablesize, int *instructionCount)
{
    int i;
    int size=0, deltacount = 0;
    char **word;
    char **operand = Split(line->line, " ", &size);
    labelPtr label;
    if (operand[0][strlen(operand[0]) - 1] == ':')
    {
        if (check_no_save_word(operand[0]) == 0)
        {
            char * newlabel = strnduplower(operand[0],strlen(operand[0]) - 1);
            if (!newlabel)
            {
                return FALSE;
            }
            printf("in line %d: \"%s\": found label %s as a save word\n", line->lineNum, line->line,newlabel);
            free(newlabel);
            return FALSE;
        }
        label = malloc(sizeof(labelstruct));
        if (label == NULL)
            return FALSE;
        label->name = strndup(operand[0],strlen(operand[0]) - 1);
        label->lineNum = *instructionCount;
        label->type = (strcmp(operand[1], ".string") == 0) ? STRING : (strcmp(operand[1], ".data") == 0) ? DATA : CODE;
        *tables = AddtoLabelTable(*tables, label, *tablesize);
        if(*tables == NULL)
        return FALSE;
        *tablesize += 1;
        deltacount = enterdatatoline(size, line->lineNum, operand, line);
        if (deltacount == -1)
            return FALSE;
        label->lineNum = *instructionCount;
        *tables = AddtoLabelTable(*tables, label, *tablesize);
    }
    else
    {
        
    }
    *instructionCount += deltacount;
    freeIneersplit(operand, size);
    return TRUE;
}

BOOLEAN check_no_save_word(const char *label)
{
    int i;
    BOOLEAN ok = TRUE;
    char *fix_label = strnduplower(label, strlen(label) - 1);
    if (!fix_label)
        return FALSE;
    if (strlen(fix_label)> MAX_SIZE_OF_LABLE)
    {
        printf("label %s is too long\n", fix_label);
        ok = FALSE;
    }
    
    for (i = 0; i < RESERVED_WORDS_COUNT && ok; i++)
    {
        if (strcmp(reservedWords[i], fix_label) == 0)
            ok = FALSE;
    }
    if (strlen(label) == 2 && label[0] == 'r' && label[1] >= '1' && label[1] <= '9')
    {
        ok = FALSE;
    }
    free(fix_label);
    return ok;
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
BOOLEAN processData(char **word, int wordcount, LinePtr line, int size)
{
    int i, converted;
    line->assemblyCode = malloc(wordcount - 2);
    if (line->assemblyCode == NULL)
        return FALSE;
    for (i = 2; i < wordcount; i++)
    {
        char *data = word[i];
        if (data[strlen(data) - 1] != ',' && i < wordcount - 1 && word[i + 1][0] != ',')
        {
            printf("in line %d: \"%s\": missing , bteen values: %s ~ &s\n", line->lineNum, line->line, word[i], word[i + 1]);
            return FALSE;
        }
        if (data[strlen(data) - 1] == ',')
            data[strlen(data) - 1] = '\0';
        else if (i< wordcount - 1 && word[i + 1][0] == ',')
            i++;
        

        if (data[0] == '+' || data[0] == '-')
        {
            converted = atoi(data + 1);
            if (converted == 0)
            {
                printf("in line %d: \"%s\": value %s is not a number\n", line->lineNum, line->line,data);
                return FALSE;
                
            }
            if(converted > MAX_NUMBER || -converted < MIN_NUMBER)
            {
              printf("in line %d: \"%s\": value %d is out of range\n", line->lineNum, line->line, converted);
              return FALSE;
              }
            converted = (data[0] == '+') ? converted : -converted;
        }
        else
        {
            converted = atoi(data);
            if (converted == 0)
            {
                 printf("in line %d: \"%s\": value %s is not a number\n", line->lineNum, line->line,data);
                return FALSE;
            }
            if (converted > MAX_UNUMBER)
            {
              printf("in line %d: \"%s\": value %d is out of range\n", line->lineNum, line->line, converted);
              return FALSE;
            }
        }
        line->assemblyCode[line->assemblyCodeCount] = converted;
        line->assemblyCodeCount++;
    }
    return TRUE;
}
int enterdatatoline(int sizewords, int *instractioncount, char **operand, LinePtr line)
{
    int sizeofdata;
    char *tav;
    if (strcmp(operand[1], ".string") == 0)
    {
        int i = 0;
        if (sizewords != 3 && operand[2][strlen(operand[2]) - 1] != '\"' || operand[2][0] != '\"')
        {
            printf("in line %d: \"%s\": found to many parameters. in .string you alow only one btween \" \"\n", line->lineNum, line->line);
            return -1;
        }
        tav = operand[2] + 1;
        line->assemblyCode = malloc(operand[2] - 1);
        if (line->assemblyCode == NULL)
            return -1;
        if (!processString(tav, line))
            return -1;
        line->assemblyCode[line->assemblyCodeCount] = '\0';
        return line->assemblyCodeCount++;
    }
    else if (strcmp(operand[1], ".data") == 0)
    {
        if(!processData(operand, sizewords, line, sizeofdata))
            return -1;
        return line->assemblyCodeCount;
    }
    else if (strcmp(operand[1], ".code"))
    {
        return 1;
    }
    
    return 0;
}
labelPtr AddtoLabelTable(labelPtr *table, labelPtr label, int size)
{
    
    LinePtr * newtable = (size == 0) ? malloc(sizeof(labelPtr)) : realloc(table, (size + 1) * sizeof(labelPtr));
    if (!newtable)
        return NULL;
    newtable[size] = label;
    return newtable;
}
