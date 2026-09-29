#include <stdarg.h>
#include <stdio.h>


#define MAX(n1, n2)(n1 > n2 ? n1 : n2)

typedef struct{
    unsigned int iCapacity;
    unsigned int iNumOfDigits;
    char *cDigits;
} bignum;

extern const bignum ZERO;

bignum AllocateBigNum(unsigned int capacity);


bignum StrToBigNum(char* str);


//operations
char Compare(bignum Num1, bignum Num2);

bignum AddBigNums(bignum FirstNum, bignum SecondNum);

bignum SubBigNums(bignum FirstNum, bignum SecondNum);



