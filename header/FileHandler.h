#ifndef FILEHANDLER
#define FILEHANDLER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/NodeData.h"
#include "../header/PublicDef.h"
#include "../header/LineDetction.h"
#include "../header/PrintForFile.h"
/*define a maccro that check if the file is open successfully if the file is not open it will print an error message*/
#define checkopenfile   if( outfile == NULL) \
{ \
    printf("we have a problem with opning the file: %s\n",filename);\
}\

/**
 * This function get a file name and a pointer to a pointer to a line structure and open the file.
 * If the file exist and has the correct extension, the function will create a linked list of the content of the file.
 * The function will return 1 if the file was opened successfully and 0 otherwise.
 * @param filename the name of the file to open
 * @param head a pointer to a pointer to a line structure, will be updated to the head of the linked list
 * @return 1 if the file was opened successfully, 0 otherwise
 */
int GetFileData(char* filename, LinePtr* head);

/**
 * Opens a file and returns a FILE pointer to it.
 *
 * @param filename The name of the file to open.
 * @param mode The mode in which to open the file (e.g. "r", "w", etc.).
 *
 * @return A pointer to the opened FILE, or NULL if the file does not exist.
 */
FILE* OpenFile(char* filename,char* mode);

/**
 * Checks if the given file name has the correct extension (.sh) or only contains the extension.
 *
 * @param filename The file name to check.
 * @return 1 if the file name has the correct extension, 0 otherwise.
 */
BOOLEAN IfFileEndCottract(char *filename);

/**
 * Reads a file line by line and creates a linked list of lines.
 *
 * @param datafile a pointer to an open file
 * @return a pointer to the head of the linked list, or NULL if an error occurred
 *
 * This function reads a file line by line and creates a linked list of lines. It
 * checks the length of each line and prints an error message if it is too long.
 * If an error occurs while allocating memory for the linked list, it prints an
 * error message and returns NULL.
 */
LinePtr InitData(FILE* datafile);

/**
 * Write the linked list to a file with the given filename.
 *
 * The function will open the file and write the data from the linked list to the file.
 * If the file can not be opened the function will return without doing anything.
 *
 * @param filename The name of the file to write to.
 * @param head A pointer to the first node of the linked list.
 */
void CreateFileFromList(char* filename,LinePtr head);

/**
 * Creates multiple code files (.ob, .ent, .ext) from a linked list of assembly lines.
 *
 * This function takes a filename and a linked list head representing assembly lines. It generates
 * the .ob, .ent, and .ext files by processing the linked list and writing the output to the respective files.
 * Each file is opened using freopen, and the standard output is temporarily redirected to the file to be written.
 * The function prints the hexadecimal representation of the assembly code, externals, and internals as necessary.
 * After writing to the files, the standard output is reset, and resources are cleaned up.
 *
 * @param filename The base name of the file to which the extensions will be appended.
 * @param head The head of the linked list containing the assembly lines.
 */
void createcodefiles(char* filename,LinePtr head);
/**
 * RenameExtensionfile - Replace the extension of a file name with a new one.
 * @filename: The file name to be modified.
 * @newextension: The new extension to be added to the file name.
 *
 * This function takes a file name and a new extension as parameters and returns a
 * modified file name that has the new extension. For example, if the filename is
 * "example.sh" and the new extension is ".sh", the function will return
 * "example.am".
 * 
 * Returns: The modified file name.
 */
char *RenameExtensionfile(char *filename, char *newextension);

#endif  