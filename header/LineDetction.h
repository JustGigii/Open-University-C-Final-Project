#ifndef LINEDETECTION
#define LINEDETECTION
#include <string.h>
#include "../header/StringUtils.h"
#include "../header/NodeData.h"
#define RESERVED_WORDS_COUNT 16
typedef enum
{
    DATA = 1,
    STRING = 2,
    EXRERN = 3,
    CODE = 4
} DATA_TYPE;
typedef struct
{
    char *name;
    int lineNum;
    short type;
    short isentry;
} labelstruct, *labelPtr;


extern const char *reservedWords[];
int processEscapeSequence(char nextChar);
BOOLEAN processString(char *tav, LinePtr line);
BOOLEAN print_operand(LinePtr heads);
BOOLEAN check_operand(LinePtr line, labelPtr ** tables, int* tablesize, int *instructionCount);
BOOLEAN check_no_save_word(const char *label);
int enterdatatoline(int sizewords,int* instractioncount,char ** operand,LinePtr line);
labelPtr AddtoLabelTable(labelPtr *table, labelPtr label, int size);
BOOLEAN processData(char **word, int wordcount, LinePtr line, int size);

#endif