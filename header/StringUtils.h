#ifndef STRING_UTILS
#define STRINGUTILS
#include "../header/PublicDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/**
 * Counts the number of occurrences of a character in a string.
 *
 * @param str the input string
 * @param c the character to count
 * @return the number of occurrences of the character
 */
int CountChar(const char* str, const char* substr );

/**
 * Splits a string into substrings separated by a character.
 *
 * @param str the input string
 * @param c the character to split on
 * @param count a pointer to an integer to store the number of substrings
 * @return an array of pointers to the substrings, or NULL on error
 */
char** Split(const char* str,const char* substr, int* count);

/**
 * This function takes a string and removes all leading and 
 * trailing tabs, and also removes any double tabs in the string.
 * The function returns the cleaned string in a new allocated memory.
 * If the allocation failed, the function will return NULL.
 * @param str The string to be cleaned.
 * @return The cleaned string in a new allocated memory, or NULL if the allocation failed.
 */
char* cleanWitheTabs(const char * str);

/**
 * Frees the memory allocated for the 2D array strarray.
 *
 * This function takes a 2D array and its size as arguments and frees the memory
 * allocated for the array and its elements. It is used to free the memory
 * allocated by the Split function.
 *
 * @param strarray The 2D array to be freed.
 * @param count The size of the array.
 * @return None
 */
void freeIneersplit(char** strarray, int count);

/**
 * Duplicates up to a specified number of characters from a string.
 *
 * Allocates memory and copies up to 'chars' characters from the input string 'str'
 * into a newly allocated string. The duplicated string is null-terminated.
 *
 * @param str The input string to duplicate.
 * @param chars The maximum number of characters to duplicate.
 * @return A pointer to the newly allocated duplicate string, or NULL if memory allocation fails.
 *
 * Note: It is the caller's responsibility to free the allocated memory.
 */
char *strndup(const char *str, int chars);

/**
 * Duplicates a portion of a string and converts it to lowercase.
 *
 * Allocates memory for a new string that contains up to 'chars' characters
 * from the input string 'str', converted to lowercase. The new string is
 * null-terminated.
 *
 * @param str The input string to duplicate and convert.
 * @param chars The maximum number of characters to duplicate from 'str'.
 * @return A pointer to the newly allocated lowercase string, or NULL if
 *         memory allocation fails.
 */
char *strnduplower(const char *str, int chars);

/**
 * Combine an array of strings into one string, with an optional separator in between the strings.
 * @param strings The array of strings to combine.
 * @param count The number of strings in the array.
 * @param separator The separator to use in between strings, or NULL to not use a separator.
 * @return The combined string, or NULL if memory allocation fails or if the input array is empty.
 */
char* combineStrings(char** strings, int count, const char* separator);
/**
 * Duplicates a string.
 *
 * Allocates memory and copies the string 'str' into a newly allocated string.
 * The duplicated string is null-terminated.
 *
 * @param str The input string to duplicate.
 * @return A pointer to the newly allocated duplicate string, or NULL if memory allocation fails.
 *
 * Note: It is the caller's responsibility to free the allocated memory.
 */

 char *mystrdup(const char *str); 
#endif 