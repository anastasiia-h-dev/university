#include "resource.h"

int main()
{
    bignum g = { 0 };
    p2bf("x^239 + x^15 + x^2 + x^1 + x^0", &g);
    printf("\n[+]Polynomial Form : x^239 + x^15 + x^2 + x^1 + x^0");

    int bits = MSB(&g);
    printf("\n[+]Binary Form  (%d bits)   : ", bits);
    PrintNumBin(g);

    char* A = "56345643563456";
    char* B = "118674932019485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485761";
    bignum num_A = StrToBinaryBignum(A);
    bignum num_B = StrToBinaryBignum(B);

    //39     + 51
    //100111 ^ 110011 = 010100
    //A = 32 + 0 + 0 + 4 + 2 + 1  = 39
    //B = 32 + 16 + 0 + 0 + 2 + 1 = 51

    bignum add_without_reduction_result = { 0 };
    AddPoly(num_A, num_B, &add_without_reduction_result);
    printf("\n\nA (decimal) =  %s\nB (decimal) = %s\n\n", A, B);
    printf("\nA (binary) = ");
    PrintNumBin(num_A);
    printf("\nB (binary) = ");
    PrintNumBin(num_B);
    printf("\n\nA + B (binary) = \n");
    PrintNumBin(add_without_reduction_result);


    printf("\n\n[+]Reduction : ");
    bignum reduction = { 0 };
    Reduct(&add_without_reduction_result, &g, &reduction);
    PrintNumBin(reduction);

}
