#include "../header/LineDetction.h"

void check_operand(char* line){
    int size,i;
    char** word;
    line = cleanWitheTabs(line);
    printf("%s\n", line);
    char ** operand = Split(line, " ", &size);
    for (i = 0; i < size; i++){
        word = operand+i;
        printf("|%s|,", operand[i]);
    }
    printf("\n");
    freeIneersplit(operand, size);
}

void print_operand(LinePtr heads){
    LinePtr temp = heads;
    while (temp){
       check_operand(temp->line);
        temp = temp->next;
    }
}