#ifndef MACROSYSTEM
#define MACROSYSTEM

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/StringUtils.h"
#include "../header/NodeData.h"
#include "../header/PublicDef.h"

/** \brief Structure that represents a macro.*/
typedef struct
{
    char *name;
    LinePtr start;
} macrostruct, *macroPtr;


/**
 * \brief Check if a macro name exists in the given list of macros.
 *
 * \param [in] macros The list of macros.
 * \param [in] size The size of the macros list.
 * \param [in] name The name of the macro to be searched.
 *
 * \return The start of the macro if it exists, NULL otherwise.
 */
macroPtr ExistMacro(macroPtr macros[],int size, char *name);

/**
 * This function add a new macro to the array of macros. the function get a pointer
 * to a line that is a macro definition, and make a new list of lines that is the
 * macro definition. the function return the new array of macros.
 * the function return NULL if the allocation of memory fails.
 * the function return NULL if the split of the line to words fails.
 * the function return NULL if the macro name is not valid.
 * the function return NULL if the macro definition is invalid.
 * @param macroarray a pointer to a array of macros
 * @param size the size of the array of macros
 * @param temp a pointer to a line that is a macro definition
 * @param ptractmacroflag a pointer to a boolean that indicate if there is a macro definition
 * @return a pointer to a new array of macros
 */
macroPtr * addMacroToList(macroPtr *macroarray,int size, LinePtr temp,BOOLEAN *ptrmacroflag);

/**
 * This function get a pointer to a line that is a macro definition, and make
 * a new list of lines that is the macro definition. the function get the next
 * lines until it see the word "mcroend" and make a new list from them.
 * the function return the new list.
 * @param copy a pointer to a line that is a macro definition
 * @return a pointer to a new list of lines that is the macro definition
 */
LinePtr InitSingelMacro(LinePtr copy);

/**
 * Replaces a line in the linked list with a macro definition.
 *
 * @param temp Pointer to the line in the linked list where the macro should be inserted.
 * @param list Pointer to the start of the macro definition to be inserted.
 * @return Pointer to the last line of the inserted macro in the linked list.
 *
 * This function removes the line following temp and inserts the lines from the list
 * in its place, effectively expanding the macro at that point in the linked list.
 */
LinePtr AddMacroToProgram(LinePtr temp, LinePtr list);

/**
 * This function gets a linked list of lines and BOOLEAN flag and init the macro system.
 * The function will go over the linked list and collect all the macro definitions.
 * After that the function will go over the linked list again and replace all the macro
 * calls with the macro definition.
 * At the end the function will return the linked list after the changes.
 * @param head the head of the linked list
 * @param ptrmacroflag BOOLEAN flag that will be FALSE if there was an error in the macro system
 * @return the linked list after the changes
 */
LinePtr InitMacro(LinePtr head, BOOLEAN *ptrmacroflag);

#endif 