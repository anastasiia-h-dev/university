#include <stdio.h>
#include "BigNumArithmetic.h"

int main(){


    bignum num1 = StrToBigNum("123");
    bignum num2 = StrToBigNum("90");
    AddBigNums(num1, num2);

    return 0;
}