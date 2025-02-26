#ifndef VALDITONLINE_H
#define VALDITONLINE_H
#include "../header/PublicDef.h"
#include "../header/NodeData.h"
#include "../header/LineDetction.h"

/**
 * Handles the operands for a given assembly command.
 *
 * This function processes the operands for a specified assembly command, determining
 * the appropriate opcode and operand types. It allocates memory for the resulting
 * machine code representation of the instruction and returns a pointer to it.
 *
 * @param commandname The name of the assembly command.
 * @param oprands An array of operand strings.
 * @param sizeofoprands The number of operands.
 * @param status Pointer to a status variable to report success or failure.
 * @param sizeofSentece Pointer to store the size of the generated sentence.
 * @param line_number The line number in the source code for error reporting.
 * @return A pointer to the generated machine code or NULL if an error occurs.
 */
unsigned int *oprandshandler(char *commandname, char **oprands, int sizeofoprands, SATATUS *status, int *sizeofSentece, int line_number);

/**
 * This function takes a string and a pointer to an int and checks if the string
 * is a valid operand for an instruction. If the string is a valid operand, the
 * function will return the number value of the operand, and the type of the
 * operand will be stored in the pointer to int. If the string is not a valid
 * operand, the function will return -1 and the type will be set to -1.
 *
 * @param oprand a string that should be checked if it is a valid operand
 * @param type a pointer to an int that will store the type of the operand
 * @param status a pointer to a SATATUS that will store the status of the operand
 * @return the number value of the operand, or -1 if the string is not a valid
 * operand
 */
int cheackoprandtype(const char *oprand, int *type, SATATUS *status);
/**
 * Process a label or number operand of an assembly instruction.
 *
 * This function handles the case where the operand is a label or number.
 * It checks if the label is already in the global table and if not, it adds it.
 * It also stores the line number where the label was mentioned.
 *
 * @param label The label to process.
 * @param labelname The name of the label.
 * @param type The type of the operand. Can be 0 for a number, 1 for a label, 2 for an extern label, or 3 for a register.
 * @param number The value of the number if the type is 0.
 * @param line_number The line number of the instruction.
 * @param ogrinal_line_number The original line number of the instruction.
 * @param status A pointer to the status of the parsing. Can be used to return an error.
 * @return The processed value of the operand.
 */
int process_type(labelPtr label, const char *labelname, int type, int number, int line_number,int ogrinal_line_number, SATATUS *status);

#endif