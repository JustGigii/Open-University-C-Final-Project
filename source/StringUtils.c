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
    int i=0,j= 0;
    int len = strlen(str);
    char * clean_str =(char*) malloc(len+1);
    if (clean_str == NULL)
    { 
    return NULL;
    }    
   while (str[i] == ' ')
   {
    i++;
   }
   
    for (i; i < len; i++)
    {   
        clean_str[j] = str[i];
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
char *strndup(char *str, int chars)
{
    char *newStr;
    int n=0;

    newStr = (char *)malloc(chars + 1);
    if (!newStr)
        return NULL;
        while ((n < chars) && (str[n] != 0) )
        {
            newStr[n] = str[n];
        n++;
        }
        newStr[n] = 0;

    return newStr;
}