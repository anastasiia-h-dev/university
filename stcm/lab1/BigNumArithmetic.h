#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <intrin.h>


void TestOperation();

typedef struct {
    unsigned int uCapacity; //the whole number of limbs
    unsigned int iNumOfLimbs; //limbs that are filled with bits
    uint32_t* uLimbs;
} bignum;


typedef struct {
    int64_t iBorrow;
    bignum diff;
} sub_result;


typedef struct {
    bignum q;
    bignum r;
} div_result;



void PrintNumDec(bignum a);
void PrintNumHex(bignum a);

void SetBit(bignum* num, unsigned int bit_index, unsigned int bit);


unsigned int BignumReserve(bignum* n, unsigned int new_capacity);
unsigned int GetBit(bignum* a, unsigned int bit_index);

int MSB(const bignum* a);
int Compare(bignum a, bignum b);

void LongShiftBitsToLow(const bignum* src, unsigned int shift_bits, bignum* dest);
void LongShiftBitsToHigh(const bignum* src, unsigned int shift_bits, bignum* dest);
bignum SmallConstToBignum(int small);
bignum StrToBinaryBignum(char* str);
bignum StrHexToBignum(char* hex_str);

bignum AddBigNums(bignum* a, bignum* b);
bignum LongMulOneDigit(bignum* a, unsigned int b);
bignum LongMul(bignum* a, bignum* b);
bignum SquareBignum(bignum* a);
bignum LongPower(bignum * a, bignum *b);

div_result LongDivBignum(bignum a, bignum b);
sub_result SubBigNums(bignum* a, bignum* b);



