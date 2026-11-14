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

    char* A = "546475285290767338394993818487129138098258817754868358620503656369512242";
    char* B = "1324365475786544212309182409452473414823482349827349872384238723435346457423454542445645645667";
    char* C = "12443";

    bignum num_A = StrToBinaryBignum(A);
    bignum num_B = StrToBinaryBignum(B);
    bignum num_C = StrToBinaryBignum(C);

    int bits_A = MSB(&num_A) + 1;
    int bits_B = MSB(&num_B) + 1;
    int bits_C = MSB(&num_C) + 1;
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
    printf("\nC (binary, %d bits) = ", bits_C);
    PrintNumBin(num_C);

    bignum reduction = { 0 };
    Reduct(&add_without_reduction_result, &g, &reduction);

    printf("\n\nA + B (binary, %d bits) = \n", MSB(&reduction) + 1);
    PrintNumBin(reduction);
    printf("\n");

    printf("\n\nA * B = ");
    bignum mul_res = { 0 };
    XTime(&num_A, &num_B, &g, &mul_res);
    PrintNumBin(mul_res);
    
    bignum sqr = { 0 };
    Square(&num_A, &g, &sqr);

    printf("\n\nSquare (%d bits): ", MSB(&sqr) + 1);
    PrintNumBin(sqr);

    bignum p = { 0 };
    Copy(&g, &p);
    int trace = Trace(&num_A, &g);
    printf("\n\nTrace : %d", trace);


    bignum pow_res = { 0 };
    //PowPoly(&num_A, 123, &g, &pow_res);
    PowPolyHorner(&num_A, &num_C, &g, &pow_res);
    printf("\n\nA ^ C (%d bits)= ", MSB(&pow_res) + 1);
    PrintNumBin(pow_res);


    bignum inverse = { 0 };
    Inverse(&num_A, &g, &inverse);
    printf("\n\nINVERSE(A)  (%d bits) = ", MSB(&inverse) + 1);
    PrintNumBin(inverse);

}
