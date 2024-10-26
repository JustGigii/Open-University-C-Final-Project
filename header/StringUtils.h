#ifndef STRING_UTILS
#define STRINGUTILS

/**
 * Counts the number of occurrences of a character in a string.
 *
 * @param str the input string
 * @param c the character to count
 * @return the number of occurrences of the character
 */
int CountChar(const char* str, char c);

/**
 * Splits a string into substrings separated by a character.
 *
 * @param str the input string
 * @param c the character to split on
 * @param count a pointer to an integer to store the number of substrings
 * @return an array of pointers to the substrings, or NULL on error
 */
char** Split(const char* str, char c, int* count);

#endif  // STRING_UTILS_H