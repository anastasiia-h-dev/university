#include "resource.h"

int main()
{
    bignum g = { 0 };
    p2bf("x^239 + x^15 + x^2 + x^1 + x^0", &g);
    //p2bf("x^163 + x^7 + x^6 + x^3 + x^0", &g);
    printf("\n[+]Polynomial Form : x^239 + x^15 + x^2 + x^1 + x^0");

    int bits = MSB(&g);
    printf("\n[+]Binary Form  (%d bits)   : ", bits + 1);
    PrintNumBin(g);

    char* A = "100";
    char* B = "1324365475786544212309182409452473414823482349827349872384238723435346457423454542445645645667";
    bignum num_A = StrToBinaryBignum(A);
    bignum num_B = StrToBinaryBignum(B);

    int bits_A = MSB(&num_A) + 1;
    int bits_B = MSB(&num_B) + 1;
    //39     + 51
    //100111 ^ 110011 = 010100
    //A = 32 + 0 + 0 + 4 + 2 + 1  = 39
    //B = 32 + 16 + 0 + 0 + 2 + 1 = 51

    bignum add_without_reduction_result = { 0 };
    AddPoly(num_A, num_B, &add_without_reduction_result);

    printf("\n\nA (decimal) =  %s\nB (decimal) = %s\n\n", A, B);
    printf("\nA (binary, %d bits) = ", bits_A);
    PrintNumBin(num_A);
    printf("\nB (binary, %d bits) = ", bits_B);
    PrintNumBin(num_B);
    printf("\n\nA + B (binary, %d bits) = \n", MSB(&add_without_reduction_result) + 1);

    bignum reduction = { 0 };
    Reduct(&add_without_reduction_result, &g, &reduction);
    printf("\n\n[+]Reduction (%d bits): ", MSB(&reduction) + 1);

    PrintNumBin(reduction);
    printf("\n");

    
    bignum sqr = { 0 };
    Square(&num_A, &g, &sqr);

    printf("\n\nSquare (%d bits): ", MSB(&sqr) + 1);
    PrintNumBin(sqr);

    bignum p = { 0 };
    Copy(&g, &p);
    int trace = Trace(&num_A, &g);
    printf("\n\nTrace : %d", trace);


}
