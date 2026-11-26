#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <intrin.h>





typedef unsigned char bool;
#define false 0
#define true !false

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

typedef struct {
    bignum num;
}DegTable[16];

void PrintNumDec(bignum a);
void PrintNumHex(bignum a);
bignum StrBinaryToBignum(char* bin_str);

void SetBit(bignum* num, unsigned int bit_index, unsigned int bit);


unsigned int BignumReserve(bignum* n, unsigned int new_capacity);
int GetBit(bignum* a, unsigned int bit_index);

int MSB(const bignum* a);
int Compare(bignum a, bignum b);

bignum LongMulOneDigit(bignum* a, unsigned int b);
void LongShiftDigitsToHigh(bignum* a, unsigned int limb_shifts);

void LongShiftBitsToLow(const bignum* src, unsigned int shift_bits, bignum* dest);
void LongShiftBitsToHigh(const bignum* src, unsigned int shift_bits, bignum* dest);
bignum SmallConstToBignum(int small);
bignum StrToBinaryBignum(char* str);
bignum StrHexToBignum(char* hex_str);

bignum AddBigNums(bignum* a, bignum* b);
bignum LongMulOneDigit(bignum* a, unsigned int b);
bignum LongMul(bignum* a, bignum* b);
bignum SquareBignum(bignum* a);
bignum LongPower(bignum* a, bignum* b);

div_result LongDivBignum(bignum a, bignum b);
sub_result SubBigNums(bignum* a, bignum* b);


void gcd(bignum a, bignum b, bignum* res);
void lcm(bignum a, bignum b, bignum* result);
bool isEven(bignum a);
void reduct(bignum* a, bignum* mod, bignum* result, bignum* myu);

void ModAdd(bignum* a, bignum* b, bignum* n, bignum* result, bignum* myu);
void ModSub(bignum* a, bignum* b, bignum* n, bignum* result, bignum* myu);
void ModMul(bignum* a, bignum* b, bignum* n, bignum* result, bignum* myu);
void ModSquare(bignum* a, bignum* n, bignum* result, bignum* myu);
bignum ModPower(bignum* a, bignum* b, bignum* n, bignum* myu);
void LongPowerWindow(bignum* a, bignum* b, bignum n, bignum myu, bignum* result);
bignum CalculateMyu(bignum* mod);
void Copy(bignum* src, bignum* dest);

//############## LAB 3 #################
bignum P_ConstOne(bignum* g);
bignum P_ConstZero(bignum* g);
void Print(bignum a, int m);

void p2bf(char* poly, bignum* r);
void bf2p(bignum* p);

void PrintNumBin(bignum a);
void AddPoly(bignum a, bignum b, bignum* result);
void Reduct(bignum* p, bignum* g, bignum* result);
void Square(bignum* p, bignum* g, bignum* r);
int Trace(bignum* p, bignum* g);

void XTime(bignum* a, bignum* b, bignum* g, bignum* r);
void PowPoly(bignum* a, int c, bignum* g, bignum* r);
void PowPolyHorner(bignum* a, bignum* c, bignum* g, bignum* r);
void Inverse(bignum* a, bignum* g, bignum* r);
void TestLab3(int num, bignum* g, int code);

void Stats_Lab3(bignum* g);
void PrintInHex(char* A, char* B, char* C, bignum g);
void PrintFromBin(char* A, char* B, char* C, bignum g);

// ######### LAB 4 #############
void N_AddPoly(bignum a, bignum b, bignum* result);
void N_Mul(bignum* u, bignum* v, int m, bignum* result);
void CircularShiftRight(const bignum* src, unsigned int shift_bits, int m, bignum* dest);
void N_Square(const bignum* src, int  m,bignum* dest);
void N_Pow(bignum* a, bignum* b, int m, bignum* result);
void N_Inverse(bignum* a, int m, bignum* result);

int N_Trace(bignum* a);
int** N_allocate_matrix(int m);
int** N_InitMatrix(int m);
void Stats_Lab4(int m);
