#include "../header/StringUtils.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int CountChar(const char* str, const char* substr )
{
    int count =0;
    while ((str = strstr(str, substr)) != NULL) {
        count++;
        str += strlen(substr);
    }

    return count;
}

char** Split(char* str,const char* substr, int* count)
{
    *count = CountChar(str, substr);
    char** strarray = (char**)malloc(((*count)+1) * sizeof(char*));
    int i = 0;
    char * word = strtok(str, substr);
    while( word) {
        strarray[i] = (char*)malloc((strlen(word) + 1) * sizeof(char));
        strcpy(strarray[i], word);
        i++;
        word = strtok(NULL, substr);
    }
    (*count)++;
    return strarray;
}

void freeIneersplit(char** strarray, int count)
{ 
        if(strarray) return;

    for (int i = 0; i < count; i++)
    {   
        if(strarray+i != NULL)
        free(strarray+i);
    }   
        free(strarray);

}