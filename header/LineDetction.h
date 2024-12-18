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


 const char* reservedWords[RESERVED_WORDS_COUNT];


int print_operand(LinePtr heads);
int check_operand(char* line, labelPtr Tables, int tablesize, int* instructionCount);
int check_no_save_word(const char* label);
labelPtr ininitlabel(char** words, int lineNum);
labelPtr AddtoLabelTable(labelPtr* table, labelPtr label, int size);
#endif