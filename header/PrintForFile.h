#ifndef PRINTFORFILE
#define PRINTFORFILE
#include "../header/NodeData.h"
#include "../header/PublicDef.h"
#include "../header/LineDetction.h"
void print_extern(labelPtr *tables, int tablesize);
void print_intern(labelPtr *tables, int tablesize);

void print_hexadecimal(unsigned int value);

void print_hexadecimal_line(const LinePtr head);
void print_number_of_line(int linenumber,char tav);


#endif