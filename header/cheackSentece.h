#ifndef CHEACKSENTENCE_H
#define CHEACKSENTENCE_H
#include <string.h>
#include "../header/StringUtils.h"
#include "../header/NodeData.h"
#include "../header/ValditionLine.h"
#include "../header/PublicDef.h"
#include "../header/LineDetction.h"

extern labelPtr **globtables;
extern int size_of_gloabal_table;

unsigned int extract_bits(int value, int start_bit, int length, SATATUS *peola);
int process_sentence(LinePtr line, char **strarray, int size, labelPtr **tables, int *tablesize, SATATUS *status);
unsigned int *cheackSentece(char **words, int sizewords, labelPtr **tables, int *tablesize, SATATUS *status, int linenumber, int *sizeofSentece);
SATATUS check_name_erorr(char **strarray, int sizeofarray);
BOOLEAN is_one_oprand(char *input);
BOOLEAN is_two_oprand(char *input);
BOOLEAN is_no_oprand(char *input);
BOOLEAN isreservedWords(char *input);


#endif