#include "../header/FileHandler.h"

int GetFileData(char* filename,LinePtr* head) {
    char * data;
    FILE* file = OpenFile(filename);
    int status = 1;
    if (!IfFileEndCottract(filename) || !file)
    {
        printf("File exists and has the correct extension.\n");
       status = 0;
    }
    else
    {
        *head= InitData(file);
        if (!*head)
            status = 0;
    }
    fclose(file);
    return status;
}

int ProcessLine(LinePtr* head, const char* line) {

    /* Ignore empty lines */
    if (line == NULL|| line[0] == '\0'|| line[0] == '\n'||line[0] == ';'|| strcmp(line, "    \n") == 0) 
    {
        printf ("%s\n",line);
       return 1;
    }
    
    /* clean the line to remove tabs */
    char* processedLine = cleanWitheTabs(line);  
    if (!processedLine) {
         /* Memory allocation failed */
        return 0; 
    }

    /* Remove the newline character, if present */
    int len = strlen(processedLine);
    if (len > 0 && processedLine[len - 1] == '\n') {
        processedLine[len - 1] = '\0';
    }

    /* Initialize the head or add to the list */
    if (!*head) {
        *head = InitLine(processedLine, START_LINE);
        if (!*head) {
            free(processedLine);
            return 0;
        }
    } else if (AddLine(*head, processedLine) == 0) {
        free(processedLine);
        return 0;
    }

     /* Free the duplicated line after processing */
    free(processedLine);
    return 1;
}
LinePtr InitData(FILE* datafile) {
    char* line = NULL;
    size_t len = 0;
    short read;
    LinePtr head = NULL;
    while ((read = getline(&line, &len, datafile)) != -1) {
       if (!ProcessLine(&head, line)) {
            free(line);
            return NULL;
        }
    }
     /* Free the buffer allocated by getline */ 
      free(line); 
    return head;
}

FILE* OpenFile(char* filename) {
        FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File does not exist.\n");
        return NULL;
    }
    return file;
}

int IfFileEndCottract(char* filename) {
    int len = strlen(filename);
    if (len < 3 || strstr(filename, ".sh") == NULL) {
        return 0;
    }
    return 1;
}