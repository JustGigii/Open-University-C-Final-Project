#include "../header/FileHandler.h"

int GetFileData(char *filename, LinePtr *head)
{
    FILE *file = OpenFile(filename, "r"); /*open file*/
    int status = 1;
    if (IfFileEndCottract(filename)== FALSE|| !file) /*check if the file open and has the correct extension*/
    {
        printf("File %s does not exists or has the correct extension.\n", filename);
        status = 0;
    }
    else
    {
        *head = InitData(file);
        if (!*head)
            status = 0;
    }
    fclose(file);
    return status;
}

int ProcessLine(LinePtr *head, const char *line)
{
    char *processedLine;
    int len ;
    /* Ignore empty lines */
    if (line == NULL || line[0] == '\0' || line[0] == '\n' || line[0] == ';' || strcmp(line, "    \n") == 0)
    {
        return 1;
    }

    /* clean the line to remove tabs */
    processedLine = cleanWitheTabs(line);
    if (!processedLine)
    {
        /* Memory allocation failed */
        return 0;
    }

    /* Remove the newline character, if present */
    len = strlen(processedLine);
    if (len > 0 && processedLine[len - 1] == '\n')
    {
        processedLine[len - 1] = '\0';
    }
    /*Remove the space character, if present in last character*/
    if (len > 0 && processedLine[len - 1] == ' ')
        processedLine[len - 1] = '\0';

    /* Initialize the head or add to the list */
    if (!*head)
    {
        *head = InitLine(processedLine, 1); /* Initialize the head with line number 1*/
        if (!*head)
        {
            free(processedLine);
            return 0;
        }
    }
    else if (AddLine(*head, processedLine) == 0)
    {
        free(processedLine);
        return 0;
    }

    /* Free the duplicated line after processing */
    free(processedLine);
    return 1;
}

LinePtr InitData(FILE *datafile)
{
    char *line = NULL;
    size_t len = 0;
    short read;
    LinePtr head = NULL;
    while ((read = getline(&line, &len, datafile)) != -1)
    {                                        /*read the file until end of file*/
        if (strlen(line) > MAX_SIZE_OF_LINE) /*check if the line is too long*/
        {
            printf("line %d is too long\n", head->lineNum);
            return NULL;
        }
        if (!ProcessLine(&head, line))
        {
            free(line);
            return NULL;
        }
    }
    /* Free the buffer allocated by getline */
    free(line);
    return head;
}

FILE *OpenFile(char *filename, char *mode)
{
    /* Open the file */
    FILE *file = fopen(filename, mode);
    if (file == NULL)
    { /* Check if the file was opened successfully */
        printf("File %s does not exist.\n", filename);
        return NULL;
    }
    return file;
}

BOOLEAN IfFileEndCottract(char *filename)
{
    int len = strlen(filename);
    if (len <= 3 || strcmp(&filename[len - 3], ".sh")) /*check if the file has the correct extension or only extension*/
        return FALSE;
    return TRUE;
}

void CreateFileFromList(char *filename, LinePtr head)
{
    FILE *file = OpenFile(filename, "w"); /*open file to write*/
    if (file != NULL)
    { /*if file is open*/
        while (head != NULL)
        { /*write the data from the list to the file*/
            fprintf(file, "%s\n", head->line);
            head = head->next;
        }
        fclose(file);
    }
}


char *RenameExtensionfile(char *filename, char *newextension)
{
    int i = 0;
    while (filename[i] != '.') /*find the dot before the extension*/
        ++i;
    filename[i] = '\0';                        /*cut the extension*/
    filename = strcat(filename, newextension); /*add the new extension*/
    return filename;
}

void createcodefiles(char *filename, LinePtr head)
{
    char *ob = ".ob", *ent = ".ent", *ext = ".ext";
    int sizeoftable;
    SATATUS status;
    /* Create the code files from the assembly lines and initialize the tables */
    labelPtr *tables = CreateAssemblyLine(head, &sizeoftable, &status);
    FILE *outfile;
    if (status == FAILURE)
        return;

    /* Create the code files from the assembly lines redirecting the standard output to write to the file */
    outfile = freopen(RenameExtensionfile(filename, ob), "w", stdout);
    checkopenfile
    print_hexadecimal_line(head);
    printf("\n");
    fclose(outfile);
    if (is_extern)
    {
        outfile = freopen(RenameExtensionfile(filename, ext), "w", stdout);
        checkopenfile
            print_extern(tables, sizeoftable);
        printf("\n");
        fclose(outfile);
    }
    if (is_intern)
    {
        outfile = freopen(RenameExtensionfile(filename, ent), "w", stdout);
        checkopenfile
            print_intern(tables, sizeoftable);
        printf("\n");
        fclose(outfile);
    }
#ifdef _WIN32                    /*for our testing run for windows*/
    freopen("CON", "w", stdout); /*redirect the standard output to the console for windows*/
#else
    freopen("/dev/tty", "w", stdout); /*redirect the standard output to the console for linux*/
#endif
    printf("End of program execution file.\n");
    free_tables(tables, sizeoftable); /*free the tables*/
    freelinllist(head);               /*free the linked list*/
}
