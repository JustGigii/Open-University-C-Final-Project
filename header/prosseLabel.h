#ifndef PROSSSELABEL_H
#define PROSSSELABEL_H
#include <string.h>
#include "../header/PublicDef.h"
#include "../header/StringUtils.h"
#include "../header/NodeData.h"
#include "../header/print_error.h"
#include "../header/cheackSentece.h"




/**
 * Process a directive line.
 *
 * This function processes a line that contains a directive (e.g. .string or .data).
 * It checks the syntax of the line and processes the directive according to its type.
 * If the processing is successful, it allocates memory for the processed directive
 * and stores it in the line structure.
 *
 * @param sizewords The number of words in the line.
 * @param operand The array of words in the line.
 * @param line The line structure to store the processed directive.
 * @param status A pointer to a status variable to report success or failure.
 * @param has_lable A boolean indicating whether the line has a label.
 * @return The size of the processed directive or -1 if an error occurs.
 */
int processDirectives(int sizewords, char **operand, LinePtr line, SATATUS *status, BOOLEAN has_lable);

/**
 * Process a single character escape sequence.
 *
 * The function takes a single character escape sequence (e.g. \n, \t, etc.) and
 * returns the corresponding ASCII character.
 *
 * @param nextChar The character following the backslash.
 *
 * @return The corresponding ASCII character if the escape sequence is recognized, -1 otherwise.
 */
int processEscapeSequence(char nextChar);

/**
 * Handles the operands for a given assembly command.
 *
 * This function processes the operands for a specified assembly command, determining
 * the appropriate opcode and operand types. It allocates memory for the resulting
 * machine code representation of the instruction and returns a pointer to it.
 *
 * @param operand An array of operand strings.
 * @param line A pointer to a Line structure.
 * @param instructionCount A pointer to the instruction count.
 * @param tables A pointer to a table of label pointers.
 * @param tablesize A pointer to the size of the table.
 * @param size The size of the operand array.
 * @param deltacount A pointer to store the size of the generated sentence.
 * @return A status code.
 */
SATATUS ProcessLabel(char **operand, LinePtr line, int *instructionCount, labelPtr **tables, int *tablesize, int size,int *deltacount);

/**
 * Process a string and convert it to an array of unsigned integers.
 * The string can contain escape sequences such as '\n' and '\t'.
 *
 * @param tav The string to process.
 * @param sizeofdata The size of the string.
 * @return An array of unsigned integers representing the string.
 */
unsigned int * processString(char *tav,int *sizeofdata);

/**
 * Processes data operands for an assembly instruction.
 *
 * This function iterates over the operands in the provided word array,
 * converting each operand to an unsigned integer and storing it in the
 * line's assembly code. It handles errors such as missing commas, invalid
 * numbers, and out-of-range values. Memory allocation is performed for
 * storing the assembly code, and the function returns an appropriate status
 * in case of failure.
 *
 * @param word An array of strings representing the operands.
 * @param wordcount The number of operands in the word array.
 * @param line A pointer to the line structure where the processed data will be stored.
 * @param size The size of the data.
 * @param has_lable A boolean indicating if the instruction has a label.
 * @return A status code indicating success or the type of failure encountered.
 */
SATATUS processData(char **word, int wordcount, LinePtr line, int size,BOOLEAN has_lable);

/**
 * Process directives .string and .data, and enter the data into the code.
 *
 * @param sizewords The number of words in the operand.
 * @param operand The operand array.
 * @param line A pointer to the current line in the linked list.
 * @param status A pointer to the status of the parsing.
 * @param table A pointer to the label table.
 * @param tablesize A pointer to the size of the label table.
 * @return The number of lines the data took up, or -1 if an error occurred.
 */
int enterdatatoline(int sizewords, char **operand, LinePtr line,SATATUS *status,labelPtr ** table,int *tablesize);

/**
 * Adds a label to the given table of labels.
 *
 * This function takes a pointer to the first element of an array of label pointers, a pointer to a
 * label to be added to the table, and a pointer to the size of the table. It allocates memory for
 * the new table, copies the old table into the new one, and adds the new label to the table.
 * If the allocation fails, it returns NULL. Otherwise, it returns a pointer to the new table.
 *
 * @param table A pointer to the first element of an array of label pointers.
 * @param label A pointer to the label to be added to the table.
 * @param size A pointer to the size of the table.
 * @return A pointer to the new table of labels or NULL if the allocation fails.
 */
labelPtr * AddtoLabelTable(labelPtr *table, labelPtr label, int * size);

/**
 * Creates a new label structure with the given name and line number.
 * If the given name has a colon at the end, it is removed.
 * The label is initialized as not being an entry or an external label.
 * The label is also initialized with no mentions.
 * The type of the label is initially set to undefined.
 *
 * @param name The name of the label to create.
 * @param lineNum The line number where the label was declared.
 *
 * @return A pointer to the newly created label or NULL if memory allocation fails.
 */
labelPtr create_label(const char *name, int lineNum);
/**
 * Checks if a given label name is valid.
 *
 * The function takes a label name as input and checks if it is valid.
 * A label name is considered valid if it does not contain any invalid characters
 * and does not have a colon (:) in the middle of the label name.
 *
 * @param label The label name to check.
 * @return TRUE if the label name is valid, FALSE otherwise.
 */
BOOLEAN CheckLableName(const char * label);
#endif