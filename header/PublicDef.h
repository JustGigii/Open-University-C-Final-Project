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
 FAILURE_OUT_OF_RANGE =4

} SATATUS;
 typedef enum {
   ARE =0,
   funct =3,
   RD= 8, /*Destination register*/
   DS = 11, /*Destination sorting*/
   RS = 13, /*Source register*/
   SS = 11, /*Source sorting*/
   OPCODE = 18,
}BIT_START;
 typedef enum {
   ARE =3,
   funct =5,
   RD= 3, /*Destination register*/
   DS = 2, /*Destination sorting*/
   RS = 3, /*Source register*/
   SS = 2, /*Source sorting*/
   OPCODE = 6,
}BIT_LENGHT;
#endif