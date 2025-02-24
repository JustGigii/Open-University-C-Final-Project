#ifndef PRINTFORFILE
#define PRINTFORFILE
#include "../header/NodeData.h"
#include "../header/PublicDef.h"
#include "../header/LineDetction.h"

/**
 * Prints the names and line numbers of all external labels in the table.
 *
 * This function iterates over a table of labels and checks each label to see if it is marked as 
 * external. For each external label, it prints the label's name followed by the line numbers 
 * where the label is mentioned, formatted with a leading '0'.
 *
 * @param tables An array of pointers to label structures.
 * @param tablesize The size of the label array.
 */
void print_extern(labelPtr *tables, int tablesize);

/**
 * Prints the entry labels from the given table of labels.
 *
 * This function iterates over the array of label pointers and prints the names
 * and line numbers of labels marked as entries. Each entry label is printed in
 * a separate line followed by its line number in a hexadecimal format.
 *
 * @param tables An array of pointers to label structures.
 * @param tablesize The number of label pointers in the tables array.
 */
void print_intern(labelPtr *tables, int tablesize);

/**
 * Prints a hexadecimal representation of the given unsigned integer value.
 * The hexadecimal representation is printed in lowercase, and is padded with
 * leading zeros to a length of 6 characters.
 * @param value the value to be printed
 */
void print_hexadecimal(unsigned int value);

/**
 * Prints a line of hexadecimal values representing the assembly code.
 *
 * This function takes a linked list of assembly lines and prints a line of
 * hexadecimal values representing the assembly code. The line begins with the
 * line number of the first assembly line, followed by the size of the data
 * section, followed by the hexadecimal values of the assembly code. The line
 * ends with a newline character.
 *
 * @param head The head of the linked list containing the assembly lines.
 */
void print_hexadecimal_line(const LinePtr head);

/**
 * Prints a line number with a given character as a filler.
 *
 * Prints a line number with a given character as a filler, padding the number
 * with the given character to a minimum of 6 characters.
 *
 * @param linenumber The line number to print.
 * @param tav The character to use as a filler.
 */
void print_number_of_line(int linenumber,char tav);


#endif