#include <stdio.h>
#include <stdlib.h>
#include "../header/FileHandler.h"
#include "../header/NodeData.h"
#include "../header/StringUtils.h" 
int main(int argc, char* argv[]) {
     char string[50] = "Hello! We are learning about strtok";
     int count =0;
    char** words = Split(string, ' ',&count);
    printf("%d\n", count);
    for (int i = 0; count>i; i++) {
        printf("%s\n", words[i]);
    }
    // char* filename;
    // LinePtr head = NULL;
     if (argc != 2) {
         printf("Usage: %s <filename>\n", argv[0]);
        return 1;
     }
    // }
    // filename = argv[1];
    // if (GetFileData(filename,&head)) {
    //     printf ("File exists and has the correct extension.\n");
    //    PrintLines(head);
    //    head=RemoveLine(head,1);
    //    PrintLines(head);
    // } else {
    //     printf("Error: File does not exist or has incorrect extension.\n");
    // }

    return 0;
}