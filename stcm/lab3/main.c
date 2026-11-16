#include "resource.h"

int main()
{
    bignum g = { 0 };
    p2bf("x^239 + x^15 + x^2 + x^1 + x^0", &g);
    //p2bf("x^163 + x^7 + x^6 + x^3 + x^0", &g);
    printf("\n[+]g = x^239 + x^15 + x^2 + x^1 + x^0");

    int bits = MSB(&g);
    printf("\n[+]g (binary)  (%d bits)   : ", bits + 1);
    PrintNumBin(g);

    char* A = "54647528529076733839499381848";
    char* B = "132436547578654421230918245645645667";
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

    printf("\n\nA (decimal) = %s\nB (decimal) = %s\nC (decimal) = %s\n\n", A, B,C);
    printf("\nA (binary, %d bits) = ", bits_A);
    PrintNumBin(num_A);
    printf("\n\nB (binary, %d bits) = ", bits_B);
    PrintNumBin(num_B);
    printf("\n\nC (binary, %d bits) = ", bits_C);
    PrintNumBin(num_C);
    printf("\n\n ### POLYNOMIAL FORM ### \n");
    printf("g = ");
    bf2p(&g);
    printf("\nA = ");
    bf2p(&num_A);
    printf("\nB = ");
    bf2p(&num_B);
    printf("\nC = ");
    bf2p(&num_C);

    bignum reduction = { 0 };
    Reduct(&add_without_reduction_result, &g, &reduction);

    printf("\n\n[+]A + B (binary, %d bits) = ", MSB(&reduction) + 1);
    PrintNumBin(reduction);
    printf("\n");

    bignum mul_res = { 0 };
    XTime(&num_A, &num_B, &g, &mul_res);
    printf("\n\n[+]A * B (binary, %d bits) = ", MSB(&mul_res) + 1);
    PrintNumBin(mul_res);
    
    bignum p = { 0 };
    Copy(&g, &p);
    int trace = Trace(&num_A, &g);
    printf("\n\n[+]Trace(%c) : %d", 'A', trace);

    bignum sqr = { 0 };
    Square(&num_A, &g, &sqr);
    printf("\n\n[+]A^2 (%d bits): ", MSB(&sqr) + 1);
    PrintNumBin(sqr);


    bignum pow_res = { 0 };
    //PowPoly(&num_A, 123, &g, &pow_res);
    PowPolyHorner(&num_A, &num_C, &g, &pow_res);
    printf("\n\n[+]A^C (%d bits)= ", MSB(&pow_res) + 1);
    PrintNumBin(pow_res);


    bignum inverse = { 0 };
    Inverse(&num_A, &g, &inverse);
    printf("\n\n[+]INVERSE(%c)  (%d bits) = ", 'A', MSB(&inverse) + 1);
    PrintNumBin(inverse);



    /// ### TESTS ###
        //TEST1

    printf("\n\n#### TESTS ####\n");
    bignum add_result = { 0 };
    AddPoly(num_A, num_B, &add_result);
    bignum num5 = { 0 };
    XTime(&add_result, &num_C, &g, &num5);
    printf("\n[+](A + B) * C : \n");
    PrintNumHex(num5);

    bignum num6 = { 0 };
    XTime(&num_A, &num_C, &g, &num6);
    bignum num7 = { 0 };
    XTime(&num_B, &num_C, &g, &num7);
    bignum add_result1 = { 0 };
    AddPoly(num6, num7, &add_result1);
    printf("\n[+]A * C + B * C : \n");
    PrintNumHex(add_result1);


    //2^m - 1:
    bignum temp = StrToBinaryBignum("1");
    bignum two = { 0 };
    LongShiftBitsToHigh(&temp, MSB(&g), &two);


    bignum one = StrToBinaryBignum("1");
    sub_result deg = SubBigNums(&two, &one);

    PowPolyHorner(&num_A, &deg.diff, &g, &temp);

    bignum r = { 0 };
    Reduct(&temp, &g, &r);

    printf("\n\n[+]A^(2^m - 1) = ");
    PrintNumBin(r);


    ////
    printf("\n\n#### 1) A + B ####");
    TestLab3(100, &g, 1);
    TestLab3(1000, &g, 1);
    TestLab3(100000, &g, 1);

    printf("\n\n#### 2) A * B ####");
    TestLab3(100, &g, 2);
    TestLab3(1000, &g, 2);
    TestLab3(10000, &g, 2);

    printf("\n\n#### 3) Trace(A) ####");
    TestLab3(100, &g, 3);
    TestLab3(1000, &g, 3);
    //TestLab3(10000, &g, 3);

    printf("\n\n#### 4) A^2 ####");
    TestLab3(100, &g, 4);
    TestLab3(1000, &g, 4);
    //TestLab3(10000, &g, 4);

    printf("\n\n#### 5) A^C ####");
    TestLab3(100, &g, 5);
    TestLab3(1000, &g, 5);
    //TestLab3(10000, &g, 5);

    printf("\n\n#### 6) INVERSE(A) ####");
    TestLab3(100, &g, 6);
    TestLab3(1000, &g, 6);
    //TestLab3(10000, &g, 6);





}
