#include "../header/StringUtils.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int CountChar(const char* str, char c){
    int count = 0;
    while (*str) {
        if (*str == c) {
            count++;
        }
        str++;
    }
    return count;
}

char** Split(const char* str, char c, int* count){
    *count = CountChar(str, c);
    char** strarray = (char**)malloc(*count * sizeof(char*));
    int i = 0;
    char * word = strtok(str, c);
    while( word ) {
        strarray[i] = (char*)malloc((strlen(word) + 1) * sizeof(char));
        strcpy(strarray[i], word);
        i++;
        word = strtok(NULL, c);
    }
    return strarray;
}