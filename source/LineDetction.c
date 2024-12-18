#include "../header/LineDetction.h"


const char *reservedWords[] = {
    "mov", "cmp", "add", "sub", "lea", 
    "clr", "not", "inc", "dec", "jmp", 
    "bne", "jsr", "red", "prn", "rts", 
    "stop"
};


int print_operand(LinePtr heads){
    labelPtr Tables=NULL;
    int tablesize=0,instructionCount=0;
    LinePtr temp = heads;
    while (temp){
       if (check_operand(temp->line,Tables,tablesize,&instructionCount) == 0)
       return 1;
        temp = temp->next;
    }
}
int check_operand(char* line,labelPtr Tables,int tablesize,int *instructionCount){
    int size,i;
    char** word;
    char ** operand = Split(line, " ", &size);
    
    if(operand[0][strlen(operand)-1] == ':')
    {
       if(check_no_save_word(operand[0])==0)
       {
       printf("in line %d: %s\n found label %s as a save word\n",operand[0]); 
       return 0;
       }

    }

    
    printf("\n");
    freeIneersplit(operand, size);
}

int check_no_save_word(const char* label){
int i;
int ok = 1;
 char * fix_label = strndup(label, strlen(label)-1);
    if (!fix_label)
        return 0;
    
    for (i = 0; i < RESERVED_WORDS_COUNT && ok; i++)
    {
        if (strcmp(reservedWords[i], fix_label) == 0)
            ok = 0;
    }
    if (strlen(label) == 2 && label[0] == 'r' && label[1] >= '1' && label[1] <= '9') {
        ok = 0;
    }
    free(fix_label);
    return ok;
}
labelPtr ininitlabel(char ** words,int lineNum){
    
}
labelPtr AddtoLabelTable(labelPtr* table,labelPtr label,int size){
    table = (table == NULL|| size == 0)?malloc(sizeof(labelPtr)):realloc(*table, (size + 1) * sizeof(labelPtr));
    if (!table)
        return NULL;
    table[size] = label;
    return table;
}

