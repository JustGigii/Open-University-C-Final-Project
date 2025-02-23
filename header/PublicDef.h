#ifndef PUBLICDEF
#define PUBLICDEF
#define MAX_SIZE_OF_LINE 81
#define MAX_SIZE_OF_LABLE 31
#define START_LINE 100
#define MAX_UNUMBER 16777215
#define MAX_NUMBER 8388607
#define MIN_NUMBER -8388608

typedef enum{
    TRUE = 1, 
    FALSE = 0
} BOOLEAN;
typedef enum 
{
 SUCCESS = 0,
 FAILURE = 1,
 FAILURE_OPRAND_NOT_MUCH = 2,
 FAILURE_TO_MUCH_LANE_TO_OPERAND = 3,
 FAILURE_OUT_OF_RANGE =4,
 FAILURE_CANNOT_ALLOCATE_MEMORY = 5,
 SAVE_WORLD = 6,
 LABEL_TO_MUCH = 7,
 MISSING_COMMA = 8,
 NOT_NUMBER = 9,
 TO_MANY_PARAMETERS = 10,
 ILLEGAL_COMMA = 11,
 MULTIPLECOMMAS = 12,
 MISSING_PARAMETER = 13,
 MISSING_COMMNAD = 14,
 ILLEGAL_ADDRESSING=15,
 WAIT_TO_ALL_LIBEL=16,
 CODE_HANDLER=17,
 DATA_HANDLER=18,
 LABEL_ALREADY_EXIST=19,
 LABEL_NOT_FOUND=20,
 ILIGAL_VALUE=21
} SATATUS;

typedef enum {
   ARE =0,
   funct =3,
   RD= 8, /*Destination register*/
   DS = 11, /*Destination sorting*/
   RS = 13, /*Source register*/
   SS = 16, /*Source sorting*/
   OPCODE = 18,
}BIT_START;
 typedef enum {
   LEN_ARE =3,
   LEN_funct =5,
   LEN_RD= 3, /*Destination register*/
   LEN_DS = 2, /*Destination sorting*/
   LEN_RS = 3, /*Source register*/
   LEN_SS = 2, /*Source sorting*/
   LEN_OPCODE = 6,
}BIT_LENGHT;

typedef enum {
    MOV = 0,          /* opcode: 0, func: 0 */
    CMP = 262144,     /* opcode: 1, func: 0 */
    ADD = 524296,     /* opcode: 2, func: 1 */
    SUB = 524304,     /* opcode: 2, func: 2 */
    LEA = 1048576,    /* opcode: 4, func: 0 */
    CLR = 1310728,    /* opcode: 5, func: 1 */
    NOT = 1310736,    /* opcode: 5, func: 2 */
    INC = 1310744,    /* opcode: 5, func: 3 */
    DEC = 1310752,    /* opcode: 5, func: 4 */
    JMP = 2359304,    /* opcode: 9, func: 1 */
    BNE = 2359312,    /* opcode: 9, func: 2 */
    JSR = 2359320,    /* opcode: 9, func: 3 */
    RED = 3145728,    /* opcode: 12, func: 0 */
    PRN = 3407872,    /* opcode: 13, func: 0 */
    RTS = 3670016,    /* opcode: 14, func: 0 */
    STOP = 3932160    /* opcode: 15, func: 0 */
  
} OPCODE_AND_FUNC;
typedef enum
{
    UNDEFINED = 0,
    DATA = 1,
    STRING = 2,
    CODE = 3,
} DATA_TYPE;

typedef struct
{
    char *name;
    int lineNum;
    DATA_TYPE type;
    BOOLEAN is_entry;
    BOOLEAN is_extern;
    int * where_mentioned;
    int size_of_where_mentioned;
} labelstruct, *labelPtr;


#endif