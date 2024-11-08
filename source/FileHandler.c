#include "../header/FileHandler.h"
#include "../header/NodeData.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int GetFileData(char* filename,LinePtr* head) {
    char * data;
    FILE* file = OpenFile(filename);
    int status = 1;
    if (!IfFileEndCottract(filename) || !file)
    {
        printf("File exists and has the correct extension.\n");
       status = 0;
    }
    else
    {
        *head= InitData(file);
    }
    fclose(file);
    return status;
}


LinePtr InitData(FILE* datafile) {
    char* line = NULL;
    size_t len = 0;
    short read;
    LinePtr head = NULL;
    while ((read = getline(&line, &len, datafile)) != -1) {
       if (!head)
       {
       head = InitLine(line,100);
       if(!head)return NULL;
       }
       else
       {
       if(AddLine(head, line) == 0)
       {
        return NULL;
       }
       }
       free(&line);
    }
    return head;
}

FILE* OpenFile(char* filename) {
        FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File does not exist.\n");
        return NULL;
    }
    return file;
}

int IfFileEndCottract(char* filename) {
    int len = strlen(filename);
    if (len < 3 || strstr(filename, ".sh") == NULL) {
        return 0;
    }
    return 1;
}