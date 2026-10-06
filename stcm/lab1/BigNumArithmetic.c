#include "BigNumArithmetic.h"

//TODO:
//1) переведення констант у формат великого числа, зокрема 0 та 1
//2) шістнадцяткове представлення


bignum ZERO = { 0,0,0 };


void PrintNumDec(bignum a)
{
    for (unsigned int i = a.iNumOfLimbs; i > 0; i--)
    {
        printf("%08X", a.uLimbs[i - 1]);
    }
}

void PrintNumHex(bignum a)
{

    printf("0x");

    int i = (int)a.iNumOfLimbs - 1;
    printf("%X", a.uLimbs[i]);
    for (i = i-1; i >= 0; i--)
    {
        printf("%08X", a.uLimbs[i]);
    }
}



unsigned int BignumReserve(bignum *n, unsigned int new_capacity)
{
    if (new_capacity <= n->uCapacity) return 1;
    uint32_t* new_limbs = (uint32_t*)realloc(n->uLimbs, new_capacity * sizeof(uint32_t));
    if (!new_limbs)
    {
        printf("BignumReserve : Memory Allocation Failed");
        return -1;
    }
    memset(new_limbs + n->uCapacity, 0, (new_capacity - n->uCapacity) * sizeof(uint32_t));
    n->uLimbs = new_limbs;
    n->uCapacity = new_capacity;
    return 0;
}


void SetBit(bignum* num, unsigned int bit_index, unsigned int bit)
{
    //num->uLimbs[bit_index] = bit;
    //if bit_index exceeds the allowed space -> create new limb
    unsigned int index_in_limb = bit_index % 32;
    unsigned int limb_index = bit_index / 32;

    if (limb_index >= num->uCapacity)
    {
        BignumReserve(num, limb_index + 1);
        //we created new limb where we can store our byte
    }
    //set the bit 'bit' at index 'bit_index' in limb 'limb_index'
    if (bit == 1)
    {
        num->uLimbs[limb_index] |= ((uint32_t)1 << index_in_limb);
    }
    else
    {
        //nothing, because there is no sense in adding 0 manually
        //or....
        num->uLimbs[limb_index] &= ~((uint32_t)1 << index_in_limb);
    }

    if (limb_index >= num->iNumOfLimbs && bit == 1)
    {
        num->iNumOfLimbs = limb_index + 1;
    }
}

bignum SmallConstToBignum(int small)
{
    bignum result;
    result.iNumOfLimbs = 1;
    result.uCapacity = 1;
    result.uLimbs = (uint32_t*)calloc(result.uCapacity, sizeof(uint32_t));

    result.uLimbs[0] = small;
    return result;
}

bignum StrToBinaryBignum(char* str)
{
    unsigned int len = (unsigned int)strlen(str);
    char* temp_number = (char*)malloc(len + 1);
    char* current = (char *)malloc(len + 1); //number which I will be working with
    strcpy(current, str);

    unsigned int bit_idx = 0; //index where the current binary digit will be stored

    bignum result; //that's where my binary number will be stored and that's what will be returned
    result.iNumOfLimbs = 1;
    result.uCapacity = 4;
    result.uLimbs = (uint32_t*)calloc(result.uCapacity, sizeof(uint32_t));

    unsigned int curlen = len;
    while (!(current[0] == '0' && current[1] == '\0') && current[0] != '\0')
    {
        int remainder = 0;
        int idx = 0;

        for (unsigned int i = 0; i < curlen; i++)
        {
                int temp = 10*remainder + (current[i] - '0');
                temp_number[idx++] = (temp / 2) + '0';
                remainder = temp % 2;
        }
        temp_number[idx] = '\0';

        //the iteration is over - input number is divided by 2 and remainder is our bit that needs to be stored in our resulting bignum
        SetBit(&result, bit_idx, remainder);
        bit_idx++;


        //we need to update temp_number with new array where number is divided by 2
        //also we have to delete all the leading zeroes 
        //for example 1 2 3 -> 0 6 1
        //                     ^

        //how to iterate through our array to find all the zeroes
        //and move array left for the amount of zeroes
        //suppose we have counter
        //we need to copy from temp_number to current

        unsigned int zero = 0;
        while(temp_number[zero] == '0' && zero < idx - 1)
        {
            zero++; //it's called zero because it's iterating through zeroes 
                    //  until we find the first nonzero
        }

        curlen = idx - zero;
        memmove(current, temp_number + zero, curlen + 1);
        current[curlen] = '\0';
        
    }
    free(current);
    free(temp_number);

    return result;

    //congrats, now I have a binary num in little-endian
}


bignum AddBigNums(bignum *a, bignum *b)
{
   //a = a + b
   //carry = 0

   //i'll just overwrite a
    unsigned int max_limbs = 0;
    if (a->iNumOfLimbs > b->iNumOfLimbs)
    {
        max_limbs = a->iNumOfLimbs;
    }
    else
    {
        max_limbs = b->iNumOfLimbs;
    }

    bignum result;
    result.iNumOfLimbs = 0;
    result.uCapacity = max_limbs + 1;
    result.uLimbs = (uint32_t*)calloc(result.uCapacity, sizeof(uint32_t));

    uint64_t carry = 0;

    
    for(unsigned int i = 0; i < max_limbs; i++)
    {
        uint64_t word_a = (i < a->iNumOfLimbs) ? a->uLimbs[i] : 0;
        uint64_t word_b = (i < b->iNumOfLimbs) ? b->uLimbs[i] : 0;
        uint64_t sum = (uint64_t)word_a + word_b + carry;

        result.uLimbs[i] = (uint32_t)sum;
        carry = sum >> 32;
    }

    if (carry > 0)
    {
        result.uLimbs[max_limbs] = (uint32_t)carry;
        result.iNumOfLimbs = max_limbs + 1;
    }
    else 
    {
        result.iNumOfLimbs = max_limbs;
    }

    while (result.iNumOfLimbs > 1 && result.uLimbs[result.iNumOfLimbs - 1] == 0)
    {
        result.iNumOfLimbs--;
    }

   return result;
}


sub_result SubBigNums(bignum* a, bignum* b)
{
    //є три варіанти
    //a > b => беззнакове віднімання, розмір результуючого bignum = розмір а
    //a < b => не оброблюється, у нас числа беззнакові
    //a = b => повертаємо нуль
    sub_result res;
    //відразу відкидаємо варіант a > b, якщо бачимо, що лімбів у b більше, ніж у а
    if (b->iNumOfLimbs > a->iNumOfLimbs)
    {
        printf("\nSubBigNums() : [!]Can't subtract bigger value from lesser.");
        res.diff = ZERO;
        res.iBorrow = -1;
        return res;
    }


    bignum result;
    result.iNumOfLimbs = a->iNumOfLimbs;
    result.uCapacity = a->iNumOfLimbs + 1;
    result.uLimbs = (uint32_t*)calloc(result.uCapacity, sizeof(uint32_t));

    int64_t borrow = 0;
    for (unsigned int i = 0; i < a->iNumOfLimbs;  i++)
    {
        uint64_t ai = a->uLimbs[i];
        uint64_t bi = (i < b->iNumOfLimbs) ? b->uLimbs[i] : 0;

        int64_t sub = (int64_t)ai - (int64_t)bi - borrow;

        //віднімали менше від більшого, або два однакових - > все ок
        if (sub >= 0)
        {
            result.uLimbs[i] = (uint32_t)sub;
            borrow = 0;
        }

        //віднімали більше від меншого
        else
        {
            result.uLimbs[i] = (uint32_t)(sub + ((int64_t)1 << 32));
            borrow = 1;
        }
    }
    if (borrow != 0)
    {
        printf("\n[!]Subtracted bigger from lesser. Undefined behaviour.");
        free(result.uLimbs);
        res.diff = ZERO;
        res.iBorrow = borrow;
        return res;

    }
    while (result.iNumOfLimbs > 1 && result.uLimbs[result.iNumOfLimbs - 1] == 0)
    {
       result.iNumOfLimbs--;
    }

    res.diff = result;
    res.iBorrow = borrow;
    return res;
}


int Compare(bignum a, bignum b)
{
    sub_result res = SubBigNums(&a, &b);
    if (res.iBorrow != 0)
    {
        return -1;
    }

    if (res.iBorrow == 0)
    {
        //a > b or a = b
        if (res.diff.uLimbs[0] == 0 && res.diff.iNumOfLimbs == 1)
        {
            return 0;
        }
        return 1;
    }
}


bignum LongMulOneDigit(bignum * a, unsigned int b)
{
    unsigned int max_limbs = a->iNumOfLimbs;


    bignum result;
    result.iNumOfLimbs = 0;
    result.uCapacity = max_limbs + 1;
    result.uLimbs = (uint32_t*)calloc(result.uCapacity, sizeof(uint32_t));

    uint64_t carry = 0;


    for (unsigned int i = 0; i < max_limbs; i++)
    {
        uint64_t word_a = (i < a->iNumOfLimbs) ? a->uLimbs[i] : 0;
        uint64_t sum = (uint64_t)word_a * b + carry;

        result.uLimbs[i] = (uint32_t)sum;
        carry = sum >> 32;
    }

    if (carry > 0)
    {
        result.uLimbs[max_limbs] = (uint32_t)carry;
        result.iNumOfLimbs = max_limbs + 1;
    }
    else
    {
        result.iNumOfLimbs = max_limbs;
    }

    while (result.iNumOfLimbs > 1 && result.uLimbs[result.iNumOfLimbs - 1] == 0)
    {
        result.iNumOfLimbs--;
    }

    return result;
}


void LongShiftDigitsToHigh(bignum *a, unsigned int shift_idx)
{

    if (shift_idx == 0 || a->iNumOfLimbs == 0) return;

    unsigned int old_len = a->iNumOfLimbs;
    unsigned int new_len = old_len + shift_idx;

    BignumReserve(a, new_len);
    for (int i = (int)old_len - 1; i >= 0; i--)
    {
        a->uLimbs[i + shift_idx] = a->uLimbs[i];
    }


    for (unsigned int i = 0; i < shift_idx; i++)
    {
        a->uLimbs[i] = 0;
    }

    a->iNumOfLimbs = new_len;
}


bignum LongMul(bignum* a, bignum* b)
{
    bignum result;
    result.iNumOfLimbs = 1;
    result.uCapacity = 4;
    result.uLimbs = (uint32_t*)calloc(result.uCapacity, sizeof(uint32_t));

    for (unsigned int i = 0; i < b->iNumOfLimbs; i++)
    {
        if (b->uLimbs[i] == 0) continue; 


        bignum temp = LongMulOneDigit(a, b->uLimbs[i]);

        LongShiftDigitsToHigh(&temp, i);

        bignum old_res = result;
        result = AddBigNums(&old_res, &temp);


        free(old_res.uLimbs);
        free(temp.uLimbs);
    }

    return result;
}


bignum SquareBignum(bignum* a)
{
    return LongMul(a, a);
}
