#ifndef LINEDETECTION
#define LINEDETECTION
#include <string.h>
#include "../header/PublicDef.h"
#include "../header/StringUtils.h"
#include "../header/NodeData.h"
#include "../header/prosseLabel.h"
#include "../header/print_error.h"
#include "../header/cheackSentece.h"
#define MY_RESERVED_TWO_OPRAND_WORDS_COUNT 5 /*size of my_reserved_Two_oprand_words add my beacuse defined in stdio */
#define MY_RESERVED_ONE_OPRAND_WORDS_COUNT 9 /* size of my_reserved_one_oprand_words add my beacuse defined in stdio*/
#define MY_RESERVED_NO_OPRAND_WORDS_COUNT 2 /* size of my_reserved_no_oprand_words add my beacuse defined in stdio*/

extern int assembly_run; /* 1 for the first run and 2 for the second run*/
extern int data_line_couter;   /* counter of the data line*/
extern int code_line_couter; /* counter of the code line*/
extern BOOLEAN is_extern; /* if the lines have extern*/
extern BOOLEAN is_intern; /* if the lines have intern*/
extern int extern_mention_counter; /* how many extern mention*/


extern const char *my_reserved_Two_oprand_words[]; /* array of the reserved two oprand words*/

extern const char *my_reserved_one_oprand_words[]; /* array of the reserved one oprand words*/

extern const char *my_reserved_no_oprand_words[]; /* array of the reserved no oprand words*/


/**
 * Creates an assembly line from a given linked list of lines.
 *
 * This function processes the given linked list of lines twice. In the first
 * pass, it counts the number of labels in the file and allocates memory for
 * the table of labels. In the second pass, it processes the lines and fills in
 * the table of labels. The function returns a pointer to the table of labels
 * or NULL if an error occurs.
 *
 * @param heads The head of the linked list of lines.
 * @param sizeofTables A pointer to store the size of the table of labels.
 * @param status A pointer to store the status of the assembly line.
 * @return A pointer to the table of labels or NULL if an error occurs.
 */
labelPtr * CreateAssemblyLine(LinePtr heads,int * sizeofTables,SATATUS *status);
/**
 * Checks a single line of assembly code for errors and processes it.
 *
 * This function takes a line of assembly code, splits it into a command name and parameters,
 * checks for errors, and processes the line accordingly. If the line is a directive line,
 * it calls ProcessLabel to handle the directive. If the line is not a directive line, it
 * calls process_sentence to handle the instruction. It also updates the instruction count
 * and stores the line number in the line structure.
 *
 * @param line A pointer to the line structure containing the line of assembly code.
 * @param tables A pointer to the table of labels.
 * @param tablesize A pointer to the size of the label table.
 * @param instructionCount A pointer to the instruction count.
 *
 * @return A status code indicating success or the type of error encountered.
 */
SATATUS check_operand(LinePtr line, labelPtr ** tables, int* tablesize, int *instructionCount);

/**
 * Checks if the given label is not a reserved word and not a register.
 *
 * This function goes over all the reserved words and checks if the given label
 * is not one of them. Additionally, it checks if the label is not a register
 * (i.e. a string of the form "rX" where X is a digit between 1 and 9).
 *
 * @param label The label to check.
 * @return TRUE if the label is not a reserved word and not a register, FALSE otherwise.
 */
BOOLEAN check_no_save_word(const char *label);

/**
 * Searches for a label in the given array of label pointers.
 *
 * @param labels An array of pointers to label structures.
 * @param size_of_labels The size of the labels array.
 * @param labelname The name of the label to search for.
 *
 * @return A pointer to the label if found, or NULL if not.
 */
labelPtr cheack_Label_Exist(const labelPtr *labels[],int size_of_labels,const char * labelname);

/**
 * Frees all memory allocated for the given table of labels.
 *
 * This function takes a pointer to a table of label pointers and the size of the table.
 * It frees the memory allocated for each label structure and then frees the memory
 * allocated for the table itself.
 *
 * @param tables A pointer to a table of label pointers.
 * @param size The size of the table.
 *
 * @return TRUE if the memory was freed successfully, FALSE otherwise.
 */
BOOLEAN free_tables(labelPtr *tables, int size);
#endif