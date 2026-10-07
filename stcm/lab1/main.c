#include "BigNumArithmetic.h"




int main()
{
    bignum num1 = StrToBinaryBignum("118674932019485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485761");
    bignum num2 = StrToBinaryBignum("338674932019485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039485762039448576203948576203945762039485762039485761");
    bignum num3 = StrToBinaryBignum("1628173491028374651928374651029384756102938475610293847561029384756102938475610293847561029384756102938475610293847561029384756102938475610293847561029384756102938475610293847561029384756102938475610293847561029384756102938475610293847561029384756102938475610293847561029384756102938475610293847561029384756102938756102938475610293");


    srand(time(NULL));

    //bignum add_result = AddBigNums(&num1, &num2);
    //PrintNumHex(add_result);

    //sub_result sub_res = SubBigNums(&num2, &num1);
    //PrintNumHex(sub_res.diff);

    //int num7 = Compare(num1, num2);
    //printf("\n[+]Comparing results : %i", num7);
    // 
    ////bignum num4 = LongMulOneDigit(&num1, 4);
    //printf("\n[+]LongMulOneDigit : ");
    //PrintNumHex(num4);
    // 
    //bignum num5 = LongMul(&num2, &num1);
    //printf("\n[+]LongMul : ");
    //PrintNumHex(num5);
   
    //bignum square = SquareBignum(&num1);
    //printf("\n[+]SquareBignum() : ");
    //PrintNumHex(square);

    //div_result div = LongDivBignum(num1, num2);
    //printf("\nQ = ");
    //PrintNumHex(div.q);
    //printf("\nR = ");
    //PrintNumHex(div.r);
     
    //bignum pow = LongPower(&num1, &num2);
    //printf("\n[+]LongPower : ");
    //PrintNumHex(pow);


    //bignum res;
    //LongShiftBitsToLow(&num1, &num2, &res);
    //printf("\n[+]LongShiftBitsToLow : ");
    //PrintNumHex(res);

    //TestOperation(100);
    //TestOperation(1000);
    //TestOperation(100000);




    //TEST1
    //printf("\n[+]num1 :\n ");
    //PrintNumHex(num1);

    //printf("\n[+]num2 :\n ");
    //PrintNumHex(num2);

    //printf("\n[+]num3 :\n ");
    //PrintNumHex(num3);


    //bignum add_result = AddBigNums(&num1, &num2);
    //bignum num5 = LongMul(&add_result, &num3);
    //printf("\n[+](num1 + num2) * num3 : \n");
    //PrintNumHex(num5);

    //bignum num6 = LongMul(&num1, &num3);
    //bignum num7 = LongMul(&num2, &num3);
    //bignum add_result1 = AddBigNums(&num6, &num7);
    //printf("\n[+]num1 * num3 + num2 * num3 : \n");
    //PrintNumHex(add_result1);


    //TEST2
    //printf("\n[+]num1 :\n ");
    //PrintNumHex(num1);
    //printf("\n[+]n : %d \n", 220);

    //bignum num4 = LongMul(&num1, 220);
    //printf("\n[+]num1 * 220 : \n");
    //PrintNumHex(num4);
    //
    //bignum temp = SmallConstToBignum(0);
    //for (int i = 0; i < 220; i++)
    //{
    //    bignum old = temp;
    //    temp = AddBigNums(&temp, &num1);
    //    free(old.uLimbs);
    //}


    //printf("\n[+]num1  + ... + num1 (220 times) : \n");
    //PrintNumHex(temp);

    return 0;
}
