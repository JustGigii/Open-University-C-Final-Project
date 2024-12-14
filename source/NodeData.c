#include "../header/NodeData.h"


LinePtr InitLine( char* line,short lineNum){
    LinePtr newLine;
    newLine= (LinePtr)malloc(sizeof(Line));
    if (!newLine) return NULL;

    newLine->line = (char*)malloc(strlen(line) + 1);
    if (!newLine) return NULL;
    
    strcpy(newLine->line, line);
    newLine->lineNum = lineNum;
    newLine->next = NULL;
    return newLine;
}
/**
 * Adds a line to the linked list.
 *
 * @param head the head of the list
 * @param line the line to add
 * @return the line number of the added line, or -1 if memory could not be allocated
 */
int AddLine(LinePtr head, char* line)
{ 
    LinePtr newLine = InitLine(line,-1);
    if (newLine == NULL)
    {
       return NULL;
    }
    
    if(!newLine)return -1;
    if (!head)
    {
        head = newLine;
        newLine->lineNum=1;
        return newLine->lineNum;
    }
        LinePtr temp = head;
        
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newLine;
        newLine->lineNum = temp->lineNum + 1;
    return newLine->lineNum;
}
int addBetweenline(LinePtr head, char* line)
{
    LinePtr temp;
    LinePtr newLine = InitLine(line,0);
    if(!newLine)return -1;
    temp = head->next;
    head->next = newLine;
    newLine->next = temp;
    return newLine->lineNum;
   
}
LinePtr RemoveLine(LinePtr head, int number){

    LinePtr temp = head;
    LinePtr prev = NULL;
    if (temp->lineNum == number)
    {
        head = temp->next;
        free(temp->line);
        free(temp);
        return head;
    }
    while (temp &&temp->lineNum != number)
    {
        prev = temp;
        temp = temp->next;
        
    }
    if (prev&&temp)
    {
        prev->next = temp->next;
        free(temp->line);
        free(temp);
    }
    if(!temp)
    return NULL;

    if(prev != NULL)
        return prev->next;
    return head;

}

void RecountLine(const LinePtr head, short number)
{
    LinePtr temp = head;
    while (temp)
    {
        temp->lineNum = number++;
        temp = temp->next;
    }
}

int PrintLines(const LinePtr head)
{
    LinePtr temp = head;
    while (temp)
    {
        printf("%d: %s\n", temp->lineNum, temp->line);
        temp = temp->next;
    }
    return 0;
}
int freeLine(LinePtr Line)
{
    free(Line->line);
    free(Line);
    return 0;
}