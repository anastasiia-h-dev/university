#include <stdarg.h>
#include <stdio.h>


#define MAX(n1, n2)(n1 > n2 ? n1 : n2)

typedef struct{
    unsigned int iCapacity;
    unsigned int iNumOfDigits;
    char *cDigits;
} bignum;


typedef struct {
    bignum bNum;
    int borrow;
} sub_result;


extern const bignum ZERO;

bignum AllocateBigNum(unsigned int capacity);


// turn input from user into integer (or double? or float?)
bignum StrToBigNum(char* str);

//operations
int Compare(bignum a, bignum b);


bignum AddBigNums(bignum FirstNum, bignum SecondNum);


sub_result SubBigNums(bignum a, bignum b);


