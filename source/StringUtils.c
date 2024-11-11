#include "../header/StringUtils.h" 


int CountChar(const char* str, const char* substr )
{
    int count =0;
    while ((str = strstr(str, substr)) != NULL) {
        count++;
        str += strlen(substr);
    }

    return count;
}

char** Split(const char* str,const char* substr, int* count)
{
    char* tmp = strdup(str);
    *count = CountChar(tmp, substr);
    char** strarray = (char**)malloc(((*count)+1) * sizeof(char*));
    int i = 0;
    char * word = strtok(tmp, substr);
    while( word) {
        strarray[i] = (char*)malloc((strlen(word) + 1) * sizeof(char));
        strcpy(strarray[i], word);
        i++;
        word = strtok(NULL, substr);
    }
    free(tmp);
    (*count)++;
    return strarray;
}

void freeIneersplit(char** strarray, int count)
{ 
    int i;
        if(strarray) return;

    for ( i= 0; i < count; i++)
    {   
        if(strarray+i != NULL)
        free(strarray+i);
    }   
        free(strarray);

}