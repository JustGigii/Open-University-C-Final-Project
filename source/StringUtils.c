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
char* cleanWitheTabs(char * str)
{
    int i,j= 0;
    int len = strlen(str);
    char * clean_str =(char*) malloc(len+1);
    if (clean_str == NULL)
    { 
    return NULL;
    }    
    if (str[0]==' ') j=1;
    for (i = 0; i < len; i++)
    {   
        clean_str[i] = str[j];
        if(str[i] != ' ' || str[i+1] != ' ') 
            j++;
    }
    clean_str[j] = '\0';
    return clean_str;
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