#include <stdio.h>
#include <stdlib.h>
#include "../header/FileHandler.h"
#include "../header/NodeData.h"
#include "../header/StringUtils.h" 
#include "../header/MacroSystem.h"
#include "../header/LineDetction.h"


int main(int argc, char* argv[]) {
    char* filename;
    BOOLEAN macroflag=TRUE;
    int i;
    char* am=".am";
    LinePtr head = NULL;
     if (argc < 2) {
         printf("Usage: %s <filename>\n", argv[0]);
        return 1;
     }
     
     for (i = 1; i < argc; i++) {
        filename = argv[i];
        if (GetFileData(filename,&head)) 
          printf ("File %s exists and has the correct extension.\n",filename); 
        else
         continue;
        head =InitMacro(head,&macroflag);
         if(head!=NULL&&macroflag==TRUE){ /*if head==null there are no macros in the program*/
          CreateFileFromList(RenameExtensionfile(filename,am),head); /*create copy of the original file after opening macro macro*/ 
         }
         else{
             if (macroflag==TRUE) 
             printf(" No macros in the program.\n");
             else
               printf("Error: Macro's definition is invalid\n");
          }
           /*PrintLines(head);*/
           print_operand(head);
        }
        printf("End of program.\n");
        return 0; 
   }