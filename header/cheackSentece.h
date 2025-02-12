#ifndef CHEACKSENTENCE_H
#define CHEACKSENTENCE_H
#include <string.h>
#include "../header/StringUtils.h"
#include "../header/NodeData.h"
#include "../header/PublicDef.h"
#include "../header/LineDetction.h"


extern labelPtr **globtables;
extern int size_of_gloabal_table;

unsigned int extract_bits(int value, BIT_START start_bit, BIT_START length, SATATUS *peola);
void print_binary(unsigned int value, int num_bits);
unsigned int *cheackSentece(char **words, int sizewords, labelPtr **tables, int *tablesize, SATATUS *status, int linenumber, int *sizeofSentece);
SATATUS check_name_erorr(char **strarray, int sizeofarray);
BOOLEAN is_one_oprand(char *input);
BOOLEAN is_two_oprand(char *input);
BOOLEAN is_no_oprand(char *input);
BOOLEAN isreservedWords(char *input);
unsigned int *oprandshandler(char *commandname, char **oprands, int sizeofoprands, SATATUS *status, int *sizeofSentece, int line_number);
int cheackoprandtype(char const *oprand, int *type);
int process_type(labelPtr label, const char *labelname, int type, int number, int line_number, SATATUS *status);

#endif