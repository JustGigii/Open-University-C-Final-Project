#include <stdio.h>
#include <stdlib.h>
#include "../header/FileHandler.h"
#include "../header/NodeData.h"
#include "../header/StringUtils.h" 
#include "../header/MacroSystem.h"
#include "../header/LineDetction.h"


int main(int argc, char* argv[]) {
    char* filename;
    LinePtr head = NULL;
     if (argc < 2) {
         printf("Usage: %s <filename>\n", argv[0]);
        return 1;
     }
     for (int i = 1; i < argc; i++) {
        filename = argv[i];
        if (GetFileData(filename,&head)) {
          printf ("File exists and has the correct extension.\n");
          InitMacro(head);
          CreateFileFromList(AddExtensionToFileName(filename,.am),head);
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