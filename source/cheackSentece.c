#include "../header/cheackSentece.h"



SATATUS cheackSentece(char **words, int sizewords,labelPtr ** tables, int* tablesize ,int *instructionCount, int * asembleyline)
{
    switch (sizewords)
    {
    case 1:
        if(strcmp(words[0], "data") == 0||strcmp(words[0],""))
        /* code */
        break;
    case 2:
    break;
    case 3:
    break;
    default:
     return FAILURE_TO_MUCH_LANE_TO_OPERAND;
        break;
    }

}

