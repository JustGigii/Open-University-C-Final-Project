#include "../header/StringUtils.h"

int CountChar(const char *str, const char *substr)
{
    int count = 0;
    while ((str = strstr(str, substr)) != NULL)
    { /*count how many substr in str*/

        count++;               /*count the substr*/
        str += strlen(substr); /*move to the next substr*/
    }

    return count;
}

char *cleanWitheTabs(const char *str)
{
    int i = 0, j = 0;
    int len = strlen(str); /*get the length of the string*/
    char *clean_str = (char *)malloc(len + 1);
    if (clean_str == NULL) /*check if the string is null*/
    {
        return NULL;
    }
    while (str[i] == ' ') /*remove the leading tabs*/
    {
        i++;
    }

    for (; i < len; i++) /*remove the trailing tabs*/
    {
        clean_str[j] = str[i];
        if (str[i] != ' ' || str[i + 1] != ' ') /*check if the next char is not a tab*/
            j++;
    }
    if (clean_str[j - 1] == ' ') /*remove the last tab*/
        j--;
    clean_str[j] = '\0'; /*add the null terminator*/
    return clean_str;
}

char **Split(const char *str, const char *substr, int *count)
{
    char *word;
    char **strarray;
    int i = 0;
    char *tmp = strdup(str);                                            /*copy the string*/
    *count = CountChar(tmp, substr);                                    /*count how many substr in str*/
    strarray = (char **)malloc(((*count) + 1) * sizeof(char *)); /*allocate memory for the strarray*/
    word = strtok(tmp, substr); /*split the string*/
    while (word)
    {                                                                    /*add words to strarray*/
        strarray[i] = (char *)malloc((strlen(word) + 1) * sizeof(char)); /*allocate memory for each word*/
        strcpy(strarray[i], word);                                       /*copy the word*/
        i++;
        word = strtok(NULL, substr); /*get the next word*/
    }
    free(tmp);       /*free the tmp*/
    (*count)++;      /*increment the count*/
    return strarray; /*return the strarray*/
}

void freeIneersplit(char **strarray, int count)
{
    int i;
    if (strarray)
        return; /*check if the strarray is null*/

    for (i = 0; i < count; i++) /*free the strarray*/
    {
        if (strarray + i != NULL) /*check if the strarray is null*/
            free(strarray + i); /*free the strarray*/
    }
    free(strarray);
}

char *strndup(const char *str, int chars) 
{
    char *newStr;
    int n = 0;

    newStr = (char *)malloc(chars + 1); 
    if (!newStr)
        return NULL;
    while ((n < chars) && (str[n] != 0)) /*copy the string until the end*/
    {
        newStr[n] = str[n]; /*copy the element of the string*/
        n++;
    }
    newStr[n] = 0;

    return newStr;
}

char *strdup(const char *str) 
{
    char *newStr;
    int n = 0;

    newStr = (char *)malloc(strlen(str) + 1); 
    if (!newStr)
        return NULL;
    while (str[n] != 0) /*copy the string until the end*/
    {
        newStr[n] = str[n]; /*copy the element of the string*/
        n++;
    }
    newStr[n] = 0;

    return newStr;
}
char *strnduplower(const char *str, int chars)
{
    char *newStr;
    int n = 0;

    newStr = (char *)malloc(chars + 1);
    if (!newStr)
        return NULL;
    while ((n < chars) && (str[n] != 0)) /*copy the string until the end*/
    {
        newStr[n] = tolower(str[n]); /*copy the element of the string and convert it to lowercase*/
        n++; 
    }
    newStr[n] = 0;

    return newStr;
}
char *combineStrings(char **strings, int count, const char *separator)
{
    char *combined = NULL; 
    int i;
    int separatorLength ;
    /* Calculate total length for the combined string */
    int totalLength = 0;
    if (count <= 0)
    {
        return NULL; /* Return NULL for an empty input array */
    }

    separatorLength = separator ? strlen(separator) : 0;

    for (i = 0; i < count; i++)
    {
        totalLength += strlen(strings[i]);
        if (i < count - 1)
        {
            totalLength += separatorLength; /* Add space for separators */
        }
    }

    /* Allocate memory for the combined string */
    combined = (char *)malloc(totalLength + 1); /* +1 for null terminator */
    if (!combined)
    {
        printf("Failed to allocate memory");
        return NULL;
    }

    /* Combine the strings */
    combined[0] = '\0'; /* Start with an empty string */
    for (i = 0; i < count; i++)
    {
        strcat(combined, strings[i]); /* Append string */
        if (i < count - 1 && separator)
        {
            strcat(combined, separator); /* Append separator */
        }
    }

    return combined;
}
