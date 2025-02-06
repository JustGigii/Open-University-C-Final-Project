#ifndef PROSSSELABEL_H
#define PROSSSELABEL_H
#include <string.h>
#include "../header/PublicDef.h"
#include "../header/StringUtils.h"
#include "../header/NodeData.h"



typedef enum
{
    DATA = 1,
    STRING = 2,
    CODE = 4
} DATA_TYPE;



int processEscapeSequence(char nextChar);
SATATUS ProcessLabel(char **operand, LinePtr line, int *instructionCount, labelPtr **tables, int *tablesize, int size,int *deltacount);
BOOLEAN processString(char *tav, LinePtr line);
SATATUS processData(char **word, int wordcount, LinePtr line, int size);
int enterdatatoline(int sizewords, int *instractioncount, char **operand, LinePtr line,SATATUS *status);
labelPtr AddtoLabelTable(labelPtr *table, labelPtr label, int size);
#endif // PROSSSELABEL_H