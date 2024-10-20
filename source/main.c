#include <stdio.h>
#include <stdlib.h>
#include "../header/FileHandler.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    char* filename = argv[1];

    if (GetFileData(filename)) {
        printf("File data retrieved successfully.\n");
    } else {
        printf("Error: File does not exist or has incorrect extension.\n");
    }

    return 0;
}