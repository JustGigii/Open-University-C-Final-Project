#ifndef NODEDATA
#define NODEDATA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/StringUtils.h"
#include "../header/PublicDef.h"
#include "../header/NodeData.h"

/*A struct representing a line in the linked list.*/
typedef struct linestruct
{
    short lineNum;
    char* line;
    unsigned int* assemblyCode;
    int assemblyCodeCount;
    struct linestruct* next;
} Line, * LinePtr; 

/**
 * Initializes a new line in the linked list.
 *
 * Allocates memory for a new Line structure and copies the given string
 * into the structure. Sets the line number and initializes other fields
 * such as assemblyCode and assemblyCodeCount to default values.
 *
 * @param line The string content to be stored in the line.
 * @param lineNum The line number to be assigned to the new line.
 * @return A pointer to the newly created Line structure, or NULL if
 *         memory allocation fails.
 */
LinePtr InitLine( char* line,short lineNum);

/**
 * Adds a line between the node and the next node line in the linked list
 *
 * @param head the head of the list
 * @param line the line to add
 * @return the line number of the added line, or -1 if memory could not be allocated
 */
int addBetweenline(LinePtr head, char* line);

/**
 * Recounts the line numbers of the linked list.
 *
 * @param head the head of the linked list
 * @param number the starting line number
 *
 * This function is used to update the line numbers of the linked list after lines have
 * been added or removed. It is used by the remove and add functions to make sure all
 * lines have a unique number.
 */
void RecountLine(const LinePtr head, short number);

/**
 * Adds a line to the linked list.
 *
 * @param head the head of the list
 * @param line the line to add
 * @return the line number of the added line, or -1 if memory could not be allocated
 */
int AddLine(LinePtr head, char* line);

/**
 * Removes a line from the linked list based on the specified line number.
 * 
 * This function traverses the linked list starting from the head, looking for a line 
 * with a line number that matches the specified number. If such a line is found, it is 
 * removed from the list, and its dynamically allocated memory is freed. If the line 
 * to remove is the head, the head is updated to the next line. If the line is not found, 
 * the function returns NULL.
 * 
 * @param head Pointer to the head of the linked list.
 * @param number The line number of the line to be removed.
 * @return Pointer to the new head of the linked list if the head is removed, or 
 *         the same head if another line is removed. Returns NULL if the line is not found.
 */
LinePtr RemoveLine(LinePtr head, int number);


int PrintLines(LinePtr head);

/**
 * Frees the memory allocated for a line in the linked list.
 *
 * @param Line Pointer to the line structure to be freed.
 * @return Always returns 0.
 *
 * This function deallocates the memory used by the line's content
 * and the line structure itself.
 */
int freeLine(LinePtr Line);

#endif