#ifndef LINEDETECTION
#define LINEDETECTION
#include <string.h>
#include "../header/PublicDef.h"
#include "../header/StringUtils.h"
#include "../header/NodeData.h"
#include "../header/prosseLabel.h"
#include "../header/print_error.h"
#include "../header/cheackSentece.h"
#define MY_RESERVED_TWO_OPRAND_WORDS_COUNT 5 /*size of my_reserved_Two_oprand_words add my beacuse defined in stdio */
#define MY_RESERVED_ONE_OPRAND_WORDS_COUNT 9 /* size of my_reserved_one_oprand_words add my beacuse defined in stdio*/
#define MY_RESERVED_NO_OPRAND_WORDS_COUNT 2 /* size of my_reserved_no_oprand_words add my beacuse defined in stdio*/



extern const char *my_reserved_Two_oprand_words[]; /* array of the reserved two oprand words*/

extern const char *my_reserved_one_oprand_words[]; /* array of the reserved one oprand words*/

extern const char *my_reserved_no_oprand_words[]; /* array of the reserved no oprand words*/

BOOLEAN print_operand(LinePtr heads);
SATATUS check_operand(LinePtr line, labelPtr ** tables, int* tablesize, int *instructionCount);

BOOLEAN check_no_save_word(const char *label);

labelPtr cheack_Label_Exist(const labelPtr labels[],int size_of_labels,const char * labelname);

#endif