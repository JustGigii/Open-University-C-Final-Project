#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/NodeData.h"

int lineNum = 1;
LinePtr InitLine( char* line){
    LinePtr newLine;
    newLine= (LinePtr)malloc(sizeof(Line));
    newLine->line = (char*)malloc(strlen(line) + 1);
    strcpy(newLine->line, line);
    newLine->lineNum = lineNum++;
    newLine->next = NULL;
    return newLine;
}
int AddLine(LinePtr head, char* line)
{ 
    LinePtr newLine = InitLine(line);
    
    if (!head)
    {
        head = newLine;
        return newLine->lineNum;
    }
        LinePtr temp = head;
        
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newLine;
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
        return head;
}

int PrintLines(const LinePtr head)
{
    LinePtr temp = head;
    while (temp)
    {
        printf("%d: %s", temp->lineNum, temp->line);
        temp = temp->next;
    }
    return 0;
}