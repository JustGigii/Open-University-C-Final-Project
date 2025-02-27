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
    if (file)
     fclose(file);
    return status;
}

BOOLEAN mygetline(char** s,FILE *file){ 
    int c,i;
    *s =(char *) malloc(MAX_SIZE_OF_LINE);  /*allocate memory*/
    for (i=0;i<MAX_SIZE_OF_LINE&&(c=getc(file))!=EOF&&c!='\n';i++) /*read the line and check if the line is too long or end of file*/
    {
        (*s)[i]= (char)c; /*add the character to the string*/
    }
    if(i==MAX_SIZE_OF_LINE) /*check if the line is too long*/
    {
        (*s)[i-1]= 0;
        printf("%s is too long\n",*s); 
        free(*s);
        return FALSE;
    }
    if (c=='\n') /*check if the line is end of file*/
        (*s)[i++]=(char)c; /*add the character to the string*/
    if(i==0) /*check if the end of file*/
    return FALSE; /*return false ifthe end of file*/
    (*s)[i]='\0';/*add the null character to the string*/
    return TRUE;
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
   /* Remove the newline character, if present */
   if (processedLine[len - 1] == '\n')
   {
       processedLine[len - 1] = '\0';
       len--;
   }
   /* Remove the carriage return character, if present */
   if (processedLine[len - 1] == '\r')
   {
       processedLine[len - 1] = '\0';
       len--;
   }
       /*Remove the space character, if present in last character*/
   if (processedLine[len - 1] == ' ')
       {
           processedLine[len - 1] = '\0';
           len--;
       }
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
    short read;
    LinePtr head = NULL;
    while ((read = mygetline(&line, datafile)) != FALSE)
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


/*************  ✨ Codeium Command ⭐  *************/
/******  3743f181-9d14-45c2-8dd4-9ac1a63eea0b  *******/
char *RenameExtensionfile(char *filename, char *newextension)
{
    char *new_filename;
    char *dot_position;
    size_t base_len;

    dot_position = strrchr(filename, '.');

    if (dot_position == NULL) {
        base_len = strlen(filename);
    } else {
        base_len = dot_position - filename;
    }

    new_filename = (char*)malloc(base_len + strlen(newextension) + 2);
    if (new_filename == NULL) {
        return NULL;
    }

    strncpy(new_filename, filename, base_len);
    new_filename[base_len] = '\0';

    strcat(new_filename, newextension);

    return new_filename;
}


void createcodefiles(char *filename, LinePtr head)
{
    char *newfilename;
    char *ob = ".ob", *ent = ".ent", *ext = ".ext";
    int sizeoftable;
    SATATUS status;
    /* Create the code files from the assembly lines and initialize the tables */
    labelPtr *tables = CreateAssemblyLine(head, &sizeoftable, &status);
    FILE *outfile;
    if (status == FAILURE)
        return;

    /* Create the code files from the assembly lines redirecting the standard output to write to the file */
    newfilename = RenameExtensionfile(filename, ob);
    outfile = freopen(newfilename, "w", stdout);
    checkopenfile
    print_hexadecimal_line(head);
    printf("\n");
    fclose(outfile);
    free(newfilename);
    if (is_extern)
    {
        newfilename = RenameExtensionfile(filename, ext);
        outfile = freopen(newfilename, "w", stdout);
        checkopenfile
            print_extern(tables, sizeoftable);
        printf("\n");
        fclose(outfile);
        free(newfilename);
    }
    if (is_intern)
    {
        newfilename = RenameExtensionfile(filename, ent);
        outfile = freopen(newfilename, "w", stdout);
        checkopenfile
            print_intern(tables, sizeoftable);
        printf("\n");
        fclose(outfile);
        free(newfilename);
    }
#ifdef _WIN32                    /*for our testing run for windows*/
    freopen("CON", "w", stdout); /*redirect the standard output to the console for windows*/
#else
    freopen("/dev/tty", "w", stdout); /*redirect the standard output to the console for linux*/
#endif
    printf("End of assembly execution file: %s.\n",filename);
    free_tables(tables, sizeoftable); /*free the tables*/
    freelinllist(head);               /*free the linked list*/
}
