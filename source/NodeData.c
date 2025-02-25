#include "../header/NodeData.h"



LinePtr InitLine( char* line,short lineNum){
    LinePtr newLine;
    newLine= (LinePtr)malloc(sizeof(Line));
    if (!newLine) return NULL;

    newLine->line = (char*)malloc(strlen(line) + 1);
    if (!newLine) return NULL;
    /* Copy the line to the new line */
    /* Initialize other fields of the new line */
    strcpy(newLine->line, line);
    newLine->lineNum = lineNum;
    newLine->assemblyCode = NULL;
    newLine->assemblyCodeCount = 0;
    newLine->next = NULL;
    return newLine;
}

int AddLine(LinePtr head, char* line)
{ 
    /* create a new line */
    LinePtr newLine = InitLine(line,-1);
    
    if(!newLine)return -1; /* if the new line is not created return -1 */
    if (!head) /* if the list is empty */
    {
        head = newLine; /* set the head to the new line */
        newLine->lineNum=1; /* set the line number to 1 */
        return newLine->lineNum;    /* return the line number */
    }
        LinePtr temp = head; /* if the list is not empty set the temp to the head */
        
        while (temp->next) /* while the next line is not null */
        {
            temp = temp->next;
        }
        temp->next = newLine; /* set the next line to the new line */
        newLine->lineNum = temp->lineNum + 1;/* set the line number to the line number of the last line + 1 */
    return newLine->lineNum;/* return the line number */
}

int addBetweenline(LinePtr head, char* line)
{
    LinePtr temp;
    LinePtr newLine = InitLine(line,0);/*create new line*/
    if(!newLine)return -1;/*if the new line is not created return -1*/
    temp = head->next;/*set the temp to the next line of the head*/
    head->next = newLine;/*set the next line of the head to the new line*/
    newLine->next = temp;/*set the next line of the new line to the temp*/
    return newLine->lineNum;
   
}

LinePtr RemoveLine(LinePtr head, int number){

    LinePtr temp = head;
    LinePtr prev = NULL;
    if (temp->lineNum == number)/*if the first line is the line to be removed*/
    {
        head = temp->next;/*set the head to the next line of the first line*/
        free(temp->line);
        free(temp);
        return head;
    }
    while (temp &&temp->lineNum != number) /*while the line is not the line to be removed*/
    {
        prev = temp;
        temp = temp->next;
        
    }
    if (prev&&temp) /*if the line is found*/
    {
        prev->next = temp->next;/*set the next line of the previous line to the next line of the line to be removed*/
        free(temp->line);
        free(temp);
    }
    if(!temp) /*if the line is not found*/
    return NULL;

    if(prev != NULL) /*if the line is found as not the last line*/
        return prev->next;
    return head;

}



void RecountLine(const LinePtr head, short number)
{
    LinePtr temp = head;
    while (temp)
    {
        temp->lineNum = number++; /* Recount the line number */
        temp = temp->next;
    }
}
/*only for checking*/
int PrintLines(const LinePtr head)
{
    LinePtr temp = head;
    while (temp)
    {
        printf("%d: %s\n", temp->lineNum, temp->line); /* Print the line number and the line */
        temp = temp->next;
    }
    return 0;
}
int freeLine(LinePtr Line)
{

    free(Line->line); /* Free the line dara */
    if(Line->assemblyCode != NULL) /* if the assembly code is not null */
    free(Line->assemblyCode); /* Free the assembly code data */
    free(Line);
    return 0;
}


BOOLEAN freelinllist(LinePtr head)
{
    LinePtr temp = head;
    while (temp)
    {
        head = temp->next; /* Set the head to the next line */
        freeLine(temp);/* Free the line */
        temp = head; /* Set the temp to the head */
    }
    return TRUE;
}
