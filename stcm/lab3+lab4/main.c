#include "resource.h"

int main()
{
    char* poly = "x^239 + x^15 + x^2 + x^1 + x^0";
    bignum g = { 0 };
    p2bf(poly, &g);
    //p2bf("x^163 + x^7 + x^6 + x^3 + x^0", &g);
    printf("\n[+]%s", poly);

    int m = MSB(&g);
    printf("\n[+]g (binary)  (%d bits)   : ", m + 1);
    PrintNumBin(g);

    char* A = "67FD220D13D1394BE5F1D6FEE0739AB27873ED5FCE2DF943D6AFC0D36DAA";
    char* B = "3388724C67D591B0CA5B29F74003A75ED65D3E2B19E9125E755F25B07AA5";
    char* C = "70D268E8B98042416F6EDE42CB75E6A13AFD4F2E6D7B05E3BC270A4908FA";

 
    //printf("\n\n### HEX ###");
    //PrintInHex(A, B, C, g);


    //printf("\n\n### BINARY ###");
    //PrintFromBin(A, B, C, g);


    printf("\n\n");



    /// ### TESTS ###
        //TEST1

    //printf("\n\n#### TESTS ####\n");
    //bignum add_result = { 0 };
    //AddPoly(num_A, num_B, &add_result);
    //bignum num5 = { 0 };
    //XTime(&add_result, &num_C, &g, &num5);
    //printf("\n[+](A + B) * C : \n");
    //PrintNumHex(num5);

    //bignum num6 = { 0 };
    //XTime(&num_A, &num_C, &g, &num6);
    //bignum num7 = { 0 };
    //XTime(&num_B, &num_C, &g, &num7);
    //bignum add_result1 = { 0 };
    //AddPoly(num6, num7, &add_result1);
    //printf("\n[+]A * C + B * C : \n");
    //PrintNumHex(add_result1);


    //2^m - 1:
    //bignum temp = StrToBinaryBignum("1");
    //bignum two = { 0 };
    //LongShiftBitsToHigh(&temp, MSB(&g), &two);


    //bignum one = StrToBinaryBignum("1");
    //sub_result deg = SubBigNums(&two, &one);

    //PowPolyHorner(&num_A, &deg.diff, &g, &temp);

    //bignum r = { 0 };
    //Reduct(&temp, &g, &r);

    //printf("\n\n[+]A^(2^m - 1) = ");
    //PrintNumBin(r);


    ////
    //Stats(&g);

    
    printf("\n\n ###### LAB 4 #####");
    bignum num_A = StrHexToBignum(A);
    bignum num_B = StrHexToBignum(B);
    bignum num_C = StrHexToBignum(C);

    printf("\n\nA (%d bits) = ", MSB(&num_A) + 1);
    PrintNumHex(num_A);
    printf("\n\nB (%d bits) = ", MSB(&num_B) + 1);
    PrintNumHex(num_B);
    printf("\n\nC (%d bits) = ", MSB(&num_C) + 1);
    PrintNumHex(num_C);


    bignum add_result = { 0 };
    N_AddPoly(num_A, num_B, &add_result);
    printf("\n\nA + B (%d bits) = ", MSB(&add_result) + 1);
    PrintNumHex(add_result);


    bignum mul_res = { 0 };
    N_Mul(&num_A, &num_B, m, &mul_res);
    printf("\n\nA * B (%d bits)= ", MSB(&mul_res) + 1);
    PrintNumHex(mul_res);


    bignum shifted_num = { 0 };
    CircularShiftRight(&num_A, 1, m, &shifted_num);
    printf("\n\nA^2 (%d bits) = ", MSB(&shifted_num) + 1);
    PrintNumHex(shifted_num);


    bignum inverse = { 0 };
    N_Inverse(&num_A, m, &inverse);
    printf("\n\nA^(-1) (%d bits)= ", MSB(&inverse) + 1);
    PrintNumHex(inverse);

    bignum pow = { 0 };
    N_Pow(&num_A, &num_C, m, &pow);
    printf("\n\nA^C (%d bits)= ", MSB(&pow) + 1);
    PrintNumHex(pow);


    printf("\n\n#### TESTS ####");

    printf("\n\n# TEST 1");
    bignum add_result1 = { 0 };
    N_AddPoly(num_A, num_B, &add_result1);
    bignum num5 = { 0 };
    N_Mul(&add_result1, &num_C, m, &num5);
    printf("\n[+](A + B) * C : \n");
    PrintNumHex(num5);

    bignum num6 = { 0 };
    N_Mul(&num_A, &num_C, m, &num6);
    bignum num7 = { 0 };
    N_Mul(&num_B, &num_C, m, &num7);
    bignum add_result2 = { 0 };
    N_AddPoly(num6, num7, &add_result2);
    printf("\n[+]A * C + B * C : \n");
    PrintNumHex(add_result2);


    printf("\n\n# TEST 2");
    bignum temp = StrToBinaryBignum("1");
    bignum two = { 0 };
    LongShiftBitsToHigh(&temp, MSB(&g), &two);


    bignum one = StrToBinaryBignum("1");
    sub_result deg = SubBigNums(&two, &one);

    N_Pow(&num_A, &deg.diff, m, &temp);
    printf("\n\n[+]A^(2^m - 1) (%d bits)= ", MSB(&temp) + 1);
    PrintNumBin(temp);

    Stats_Lab4(m);
}
