/** @file main.c
 * @brief main function of the program
 * @author Dvir Yarden and Omri Gigi
 * @date 27/02/2025
 * description: This file contains the main function of the program that is the entry point of the program 
 * and the main loop of the program that contains the main loop of the program.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../header/FileHandler.h"
#include "../header/NodeData.h"
#include "../header/StringUtils.h" 
#include "../header/MacroSystem.h"
#include "../header/LineDetction.h"


/**
 * @brief The main function of the program.
 * This function is the entry point of the program.
 * It receives a list of file names as arguments and assembles each file separately.
 * For each file, it creates a linked list of lines, opens macros, and creates .ob, .am .ent, and .ext files.
 * If there are any errors while assembling the file, it prints an error message and continues to the next file.
 * If the file does not exist or has the wrong extension, it prints an error message and continues to the next file.
 * If there are no macros in the program, it prints a message and continues to the next file.
 * If there are any errors while opening macros, it prints an error message and continues to the next file.
 * If the assembly is successful, it prints a success message and returns 0.
 */
int main(int argc, char* argv[]) {
    char* filename;
    BOOLEAN macroflag=TRUE;
    int i;
    char* newfilename;
    LinePtr head = NULL;
    LinePtr aftermacro= NULL;
     if (argc < 2) { /*if the user did not enter a file name*/
         printf("not found file\npls enter file name to assembly for example\n: %s onlymcro.sh\n", argv[0]);
        return 1;
     }
     for (i = 1; i < argc; i++) {
        filename = argv[i];
        if (GetFileData(filename,&head)) /*create list of line from file*/
          printf ("File %s exists and has the correct extension.\nstart to assembly the file",filename); 
        else
        {
         continue;/*if the file does not exist or has the wrong extension, continue to the next file*/
        }
         aftermacro =InitMacro(head,&macroflag);
         if(aftermacro != NULL)
          head = aftermacro;
         if(aftermacro!=NULL&&macroflag==TRUE){ /*if head==null there are no macros in the program*/
          newfilename= RenameExtensionfile(filename,".am"); /*create copy of the original file after opening macro macro*/
          CreateFileFromList(newfilename,head); /*create copy of the original file after opening macro macro*/ 
          free(newfilename);
         }

         else
             if (macroflag==TRUE)/*if macroflag==TRUE there are no macros in the program*/ 
             printf(" No macros in the program.\n");
             else{
               printf("Error: Macro's definition is invalid\n");
                continue;/*if macroflag==FALSE there is a problem with the macro definition*/
           }
        createcodefiles(filename,head);/*create .ob .ent and .ext files*/        
        }
        printf("the assembly end successfully\n");
        return 0; 
   }