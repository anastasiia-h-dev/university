#include <stdio.h>
#include "BigNumArithmetic.h"

int main(){


    bignum num1 = StrToBigNum("5000000000000000000");
    bignum num2 = StrToBigNum("5000000000000000001");
    AddBigNums(num1, num2);
    Compare(num1, num2);

    return 0;
}