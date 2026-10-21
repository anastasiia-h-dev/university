#include <stdlib.h>
#include <string.h>
#include "BigNumArithmetic.h"

// turm small constants into big number format
// int SmallToBigNum(){}
const bignum ZERO = {0, 0, NULL};


bignum AllocateBigNum(unsigned int capacity){
    bignum num;

    num.iCapacity   = capacity;
    num.iNumOfDigits = 0;
    num.cDigits = malloc(capacity * sizeof(char));

    return num;
}


bignum StrToBigNum(char* str){
   unsigned int len = strlen(str);
   int idx = 0;

   bignum aux = AllocateBigNum(2048);

   while (!(len == 1 && str[0] == '0'))
    {
       char* temp_number = malloc(len + 1);
        
        int remainder = 0;

        for (int i = 0; i < len; i++)
        {
            //printf("str[i]  =  %d\n", str[i] - '0');


            if (remainder == 1)
            {
                //printf(" >>>>> remainder = 1 <<<<<<\n");
                int temp = 10 + (str[i] - '0');
                temp_number[i] = (temp / 2) + '0';
                remainder = temp - 2 * (temp_number[i] - '0');
            }
            else
            {
                int temp = str[i] - '0';
                temp_number[i] = ((str[i] - '0') / 2) + '0';
                remainder = temp - 2 * (temp_number[i] - '0');

            }
        }

        aux.cDigits[idx] = remainder;
        //printf("remainder %d\n", remainder);

        int is_zero = 1;

        for (int i = 0; i < len; i++)
        {
            if (temp_number[i] != '0')
            {
                is_zero = 0;
                break;
            }
        }
        

        temp_number[len] = '\0';
        str = temp_number;
        idx++;

        if (is_zero) break;
   }
   free(str);

   bignum binary_form = AllocateBigNum(idx);
   binary_form.iNumOfDigits = idx;
   for (int i = 0; i < idx; i++)
   {
       binary_form.cDigits[i] = aux.cDigits[i];
   }

   printf("bin :");
   for (int i = 0; i < idx; i++)
   {
       printf("%d",  binary_form.cDigits[i]);

   }
   printf("\n");


   return binary_form;
}

//// operations

bignum AddBigNums(bignum FirstNum, bignum SecondNum)
{

    unsigned int iMaxNumOfDigits = MAX(FirstNum.iNumOfDigits, SecondNum.iNumOfDigits) + 1;
    //якщо довжини чисел не рівні треба доповнювати нуьовимии байтами
    //поки що функція робоча для чисел, що мають однакову довжину у бінарному вигляді
    
    printf("\nMAX : %d\n", iMaxNumOfDigits);

    bignum result = AllocateBigNum(iMaxNumOfDigits);
    result.iNumOfDigits = iMaxNumOfDigits;
    printf("\n");
    int carry = 0;
    for(unsigned int idx = 0; idx < result.iNumOfDigits; idx++)
    {
        result.cDigits[idx] = FirstNum.cDigits[idx] ^ SecondNum.cDigits[idx] ^ carry;
        printf("%d", result.cDigits[idx]);
        //printf("addition %d result[%d] : %d\n", idx, idx, result.cDigits[idx]);
        carry = (FirstNum.cDigits[idx] & SecondNum.cDigits[idx]) || ( carry & ( FirstNum.cDigits[idx] ^ SecondNum.cDigits[idx] ));
    }
    return result;
}


sub_result SubBigNums(bignum a, bignum b)
{
    //поки вважаємо, що FirstNum більше за SecondNum за замовчуванням
   

    unsigned int iNumOfDigits = a.iNumOfDigits;
    bignum res = AllocateBigNum(iNumOfDigits);
    res.iNumOfDigits = iNumOfDigits;
    
    unsigned int borrow = 0;
    printf("\nsubtruction result\n");
    for (unsigned int idx = 0; idx < res.iNumOfDigits; idx++)
    {
        res.cDigits[idx] = a.cDigits[idx] ^ b.cDigits[idx] ^ borrow;
        printf("%d",res.cDigits[idx]);
        borrow = (!(a.cDigits[idx]) & b.cDigits[idx]) || (borrow & ((!a.cDigits[idx]) ^ b.cDigits[idx]));
    }

    sub_result result;
    result.bNum = res;
    result.borrow = borrow;
    return result;
}


int Compare(bignum a, bignum b) 
{
    sub_result result = SubBigNums(a, b);

    if (result.borrow == 1)
    {
        printf("\na < b");
        return -1;
    }
    else if (result.borrow == 0)
    {
        printf("\na = b, or a > b");
        return 0; //ніпанятна чи a == b, чи a > b
    }
    return 0;
}


//
//int MultiplyBigNums(){
//
//}
//
//int DivideBigNums(){
//
//}
//
//int SquareBigNums(){
//
//}
//
//int ToPowerBigNums(){
//
//}
//
//int RemainderBigNums(){
//
//}
