#include "../header/PrintForFile.h"
void print_extern(labelPtr *tables, int tablesize)
 {
    int i,j;
    labelPtr addr;
    for ( i = 0; i < tablesize; i++)
    {
        addr = tables[i];
        if(tables[i]->is_extern ==TRUE)
        {
            for ( j = 0; j < tables[i]->size_of_where_mentioned; j++)
            {
                printf("%s ", tables[i]->name);
                print_number_of_line(addr->where_mentioned[j],'0');
                printf("\n");
            }
        }
    }

    
}
void print_intern(labelPtr *tables, int tablesize)
{
    int i;
    labelPtr addr;
    for ( i = 0; i < tablesize; i++)
    {
        addr = tables[i];
        if(tables[i]->is_entry ==TRUE)
        {
           printf("%s ", tables[i]->name);
           print_number_of_line(tables[i]->lineNum,'0');
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
    mask = mask<<(6*4);
    for (i= 6; i>0; i--)
    {
        mask = mask>>(4);
        result = b & mask;
        result = result>>(4*(i-1));
        printf("%x",result);
    }
    printf("\n");
}

void print_hexadecimal_line(const LinePtr head)
{
    int i;
    LinePtr temp = head;
    print_number_of_line(code_line_couter,' ');
    printf("%d\n", data_line_couter);
    while (temp)
    {
        for(i=0; i < temp->assemblyCodeCount; i++)
        {
            print_number_of_line(temp->lineNum+i,'0');
            print_hexadecimal(temp->assemblyCode[i]);
        }
        temp = temp->next;
    }
}
void print_number_of_line(int linenumber,char tav)
{
  
    int i,counter = 0;
    int tenp =linenumber;
    while (tenp != 0)
    {
        counter++;
        tenp = tenp/10;
    }
    for (i = 0; i < 6 - counter; i++)
    {
        printf("%c", tav);
    }
    printf("%d ", linenumber);
}
