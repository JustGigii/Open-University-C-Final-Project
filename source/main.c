#include <stdio.h>
#include <stdlib.h>
#include "../header/FileHandler.h"
#include "../header/NodeData.h"
#include "../header/StringUtils.h" 
#include "../header/MacroSystem.h"
#include "../header/LineDetction.h"


int main(int argc, char* argv[]) {
    char* filename;
    int i;
    char* am=".am";
    LinePtr head = NULL;
     if (argc < 2) {
         printf("Usage: %s <filename>\n", argv[0]);
        return 1;
     }
     for (i = 1; i < argc; i++) {
        filename = argv[i];
        if (GetFileData(filename,&head)) {
          printf ("File exists and has the correct extension.\n");
          if(InitMacro(head)!=NULL) /*if head==null there are no macros in the program*/
          CreateFileFromList(RenameExtensionfile(filename,am),head); /*create copy of the original file after opening macro macro*/
           /*PrintLines(head);*/
           print_operand(head);
        }
        else
       {
        printf("Error: File does not exist or has incorrect extension.\n");
      }
   }
    return 0;
}