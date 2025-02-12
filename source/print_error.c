#include "../header/print_error.h"

void print_error(SATATUS status,int linenum,char *line)
{
    switch (status)
    {
        case FAILURE_CANNOT_ALLOCATE_MEMORY:
            printf("in line %d: \"%s\": cannot allocate memory\n", linenum, line);
            break;
        case SAVE_WORLD:
            printf("in line %d: \"%s\": found label as a save word\n", linenum, line);
            break;
        case FAILURE_OUT_OF_RANGE:
            printf("in line %d: \"%s\": value out of range\n", linenum, line);
            break;
        case FAILURE_TO_MUCH_LANE_TO_OPERAND:
            printf("in line %d: \"%s\": to much lane to operand\n", linenum, line);
            break;
        case FAILURE_OPRAND_NOT_MUCH:
            printf("in line %d: \"%s\": operand not much\n", linenum, line);
            break;
        case MISSING_COMMA:
            printf("in line %d: \"%s\": Missing comma\n", linenum, line);
            break;
        case NOT_NUMBER:
            printf("in line %d: \"%s\": Undefined integer variable\n", linenum, line);
            break;
        case TO_MANY_PARAMETERS:
            printf("in line %d: \"%s\": Extraneous text after end of command\n", linenum, line);
            break;
        case ILLEGAL_COMMA:
              printf("in line %d: \"%s\": Illegal comma\n", linenum, line);
              break;
        case MULTIPLECOMMAS:
              printf("in line %d: \"%s\": Multiple consecutive commas\n", linenum, line);
              break;
        case MISSING_PARAMETER:
              printf("in line %d: \"%s\": Missing parameter\n", linenum, line);
              break;
        case MISSING_COMMNAD:
              printf("in line %d: \"%s\": Missing command\n", linenum, line);
              break;
        case ILLEGAL_ADDRESSING:
                printf("in line %d: \"%s\": Illegal addressing methods to the command\n", linenum, line);
                break;
    } 
}