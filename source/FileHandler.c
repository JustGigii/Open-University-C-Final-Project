#include "../header/FileHandler.h"
#include <stdio.h>
#include <string.h>

int GetFileData(char* filename) {
    FILE* file = OpenFile(filename);
    int status = 1;
    if (!IfFileEndCottract(filename) || !file)
    {
        printf("File exists and has the correct extension.\n");
       status = 0;
    }
    else
    {
        print_file(file);
        fclose(file);
    }
    return status;
}


int print_file(FILE* datafile) {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), datafile)) {
        printf("%s", buffer);
    } 
    return 0;
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