#ifndef VALDITONLINE_H
#define VALDITONLINE_H
#include "../header/PublicDef.h"
#include "../header/NodeData.h"
#include "../header/LineDetction.h"
unsigned int *oprandshandler(char *commandname, char **oprands, int sizeofoprands, SATATUS *status, int *sizeofSentece, int line_number);
int cheackoprandtype(char const *oprand, int *type);
int process_type(labelPtr label, const char *labelname, int type, int number, int line_number,int ogrinal_line_number, SATATUS *status);

#endif