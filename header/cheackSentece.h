#ifndef CHEACKSENTENCE_H
#define CHEACKSENTENCE_H
#include <string.h>
#include "../header/StringUtils.h"
#include "../header/NodeData.h"
#include "../header/ValditionLine.h"
#include "../header/PublicDef.h"
#include "../header/LineDetction.h"

extern labelPtr **globtables;
extern int size_of_gloabal_table;


/**
 * Extracts a sequence of bits from a given value and returns the extracted value.
 *
 * @param value The value from which to extract the bits.
 * @param start_bit The starting bit number (from the least significant bit) to extract.
 * @param length The number of bits to extract.
 * @param peola A pointer to a SATATUS variable to store the status of the operation.
 *
 * @return The extracted bits as an unsigned int.
 *
 * @note If start_bit or length are out of range, the function returns 0 and sets peola to
 *       FAILURE_OUT_OF_RANGE.
 */
unsigned int extract_bits(int value, int start_bit, int length, SATATUS *peola);

/**
 * Process a sentence of assembly code.
 *
 * This function processes a sentence of assembly code, calling cheackSentece to
 * generate assembly code and processDirectives to handle directives. It also
 * handles errors and updates the instruction count and data count.
 *
 * @param line A pointer to the line structure containing the sentence to be
 * processed.
 * @param strarray An array of strings representing the operands.
 * @param size The number of operands in the strarray.
 * @param tables A pointer to the table of labels.
 * @param tablesize A pointer to the size of the label table.
 * @param status A pointer to the status of the parsing.
 *
 * @return The number of lines the sentence took up, or -1 if an error occurred.
 */
int process_sentence(LinePtr line, char **strarray, int size, labelPtr **tables, int *tablesize, SATATUS *status);

/**
 * Cheack the sentence for errors and if not create the binary code.
 *
 * The function takes an array of strings representing the words in the sentence,
 * the size of the array, a pointer to the table of labels, the size of the table,
 * a pointer to the status of the parsing and the line number.
 * If the sentence is a directive line, the function process the directive and return
 * the result. Otherwise, the function checks for errors and if not, creates the binary
 * code and store it in the line structure.
 *
 * @param words An array of strings representing the words in the sentence.
 * @param sizewords The size of the array.
 * @param tables A pointer to the table of labels.
 * @param tablesize A pointer to the size of the table.
 * @param status A pointer to the status of the parsing.
 * @param linenumber The line number.
 * @param sizeofSentece A pointer to the size of the binary code.
 *
 * @return A pointer to the binary code if the sentence is a instruction line, NULL otherwise.
 */
unsigned int *cheackSentece(char **words, int sizewords, labelPtr **tables, int *tablesize, SATATUS *status, int linenumber, int *sizeofSentece);

/**
 * Checks for errors in the command name.
 *
 * This function takes an array of strings and the size of the array.
 * It checks if the command name has a comma at the end, if the command exists,
 * and if there is extra text after the command stop.
 *
 * @param strarray An array of strings containing the command name.
 * @param sizeofarray The size of the array.
 *
 * @return A status code indicating success or the type of error encountered.
 */
SATATUS check_name_erorr(char **strarray, int sizeofarray);

/**
 * Checks if a given command is in the list of commands with one operand.
 *
 * @param input The command to check.
 *
 * @return TRUE if the command is in the list of commands with one operand, FALSE otherwise.
 */
BOOLEAN is_one_oprand(char *input);

/**
 * Checks if the given command requires two operands.
 *
 * This function iterates over the list of reserved words that correspond to
 * commands requiring two operands. It compares the input string against each
 * reserved word and returns TRUE if a match is found, indicating that the
 * command requires two operands. If no match is found, it returns FALSE.
 *
 * @param input The command string to check.
 * @return TRUE if the command requires two operands, FALSE otherwise.
 */
BOOLEAN is_two_oprand(char *input);

/**
 * Checks if a given command is in the list of commands with no operands.
 *
 * This function takes a string command and checks if it is in the list of
 * commands with no operands. If the command is found, the function returns
 * TRUE, otherwise it returns FALSE.
 *
 * @param input The command to check.
 * @return TRUE if the command is in the list of commands with no operands, FALSE
 * otherwise.
 */
BOOLEAN is_no_oprand(char *input);

/**
 * This function checks if the given string is a reserved word.
 *
 * @param input The string to check.
 *
 * @return TRUE if the string is a reserved word, FALSE otherwise.
 */
BOOLEAN isreservedWords(char *input);


#endif