#include "../header/PrintForFile.h"
void print_extern(labelPtr *tables, int tablesize)
 {
    int i,j;

    for ( i = 0; i < tablesize; i++) /* run on the label table*/
    {
        if(tables[i]->is_extern ==TRUE) /* if the label is extern*/
        {
            for ( j = 0; j < tables[i]->size_of_where_mentioned; j++)
            {
                printf("%s ", tables[i]->name);  /* print the label name*/
                print_number_of_line(tables[i]->where_mentioned[j],'0'); /* print the line number like we ask in the task*/
                printf("\n");
            }
        }
    }

    
}
void print_intern(labelPtr *tables, int tablesize)
{
    int i;
    labelPtr addr;
    for ( i = 0; i < tablesize; i++) /* run on the label table*/
    {
        if(tables[i]->is_entry ==TRUE) /* if the label is entry*/
        {
           printf("%s ", tables[i]->name);  /* print the label name*/
           print_number_of_line(tables[i]->lineNum,'0'); /* print the line number like we ask in the task*/
           printf("\n");
        }
    }
}
void print_hexadecimal(unsigned int value)
{   
    int i;
    unsigned int mask = 15;
    unsigned int result = 0;
    unsigned int b = value;
    mask = mask<<(6*4);/*shift the mask to the end of the hex number*/
    for (i= 6; i>0; i--) /* run on the hex number*/
    {
        mask = mask>>(4); /* shift the mask to the start of the hex number*/
        result = b & mask; /* get the hex number*/
        result = result>>(4*(i-1)); /* shift the hex number to the start of the hex number*/
        printf("%x",result); /* print the hex number*/
    }
    printf("\n");
}

void print_hexadecimal_line(const LinePtr head)
{
    int i;
    LinePtr temp = head;
    print_number_of_line(code_line_couter,' ');/* print the line number like we ask in the task*/
    printf("%d\n", data_line_couter);
    while (temp) /* run on the line*/
    {
        for(i=0; i < temp->assemblyCodeCount; i++)
        {
            print_number_of_line(temp->lineNum+i,'0');/* print the line number like we ask in the task*/
            print_hexadecimal(temp->assemblyCode[i]);/* print the hex number*/
        }
        temp = temp->next;
    }
}
void print_number_of_line(int linenumber,char tav) 
{
  
    int i,counter = 0; 
    int tenp =linenumber; 
    while (tenp != 0) /* run how many digits in the line number*/
    {
        counter++; /* count the digits*/
        tenp = tenp/10; /* divide the line number by 10*/
    }
    for (i = 0; i < 6 - counter; i++) /* print the 'tav' how many times*/
    {
        printf("%c", tav);
    }
    printf("%d ", linenumber); /* print the line number*/
}
