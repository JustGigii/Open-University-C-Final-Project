#include "../header/cheackSentece.h"

unsigned int extract_bits(int value, BIT_START start_bit, BIT_LENGHT length,SATATUS *peola) {
    /* Ensure start_bit and length are within valid range */
    if (start_bit < 0 || start_bit >= 24 || length <= 0 || start_bit + length > 24) {
        *peola = FAILURE_OUT_OF_RANGE;
        return 0; /* Return 0 for invalid input */
    }

    /* Create a mask with the desired length of 1s */
    unsigned int mask = (1 << length) - 1;

    /* Shift the mask to the starting position and apply it to the value */
    return (value >> start_bit) & mask;
}

void print_binary(unsigned int value, int num_bits) {
    int i;
    for (i = num_bits - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}
SATATUS cheackSentece(char **words, int sizewords,labelPtr ** tables, int* tablesize ,int *instructionCount, int ** asembleyline)
{
    int opcode;
    SATATUS peola = SUCCESS;
    switch (sizewords)
    {
    case 1:
        if(strcmp(words[0], "rts") == 0||strcmp(words[0],"stop")==0)
        {

            *asembleyline = malloc(sizeof(int));
           **asembleyline = 4;
           opcode = (strcmp(words[0], "rts") == 0) ? 14 : 15;
           **asembleyline = extract_bits(opcode,OP,opcode,&peola)
        }
        else 
        return FAILURE_OPRAND_NOT_MUCH;
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

