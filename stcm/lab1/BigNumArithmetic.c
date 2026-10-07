#include "BigNumArithmetic.h"

//TODO:
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

bignum StrHexToBignum(char* hex_str)
{
    int len = (unsigned int)strlen(hex_str);
    unsigned int bit_idx = 0;

    bignum result;
    result.iNumOfLimbs = (len + 7) / 8;
    result.uCapacity = result.iNumOfLimbs + 1;
    result.uLimbs = (uint32_t*)calloc(result.uCapacity, sizeof(uint32_t));

    int i = 0;
    int idx = result.iNumOfLimbs - 1;
    while (i < len)
    {
        uint8_t hex_byte;

        if (i == 0 && (len % 8 != 0))
        {
            for (int j = 0; j < (len % 8); j++)
            {
                if (hex_str[i] == 'A') hex_byte = 10;
                else if (hex_str[i] == 'B') hex_byte = 11;
                else if (hex_str[i] == 'C') hex_byte = 12;
                else if (hex_str[i] == 'D') hex_byte = 13;
                else if (hex_str[i] == 'E') hex_byte = 14;
                else if (hex_str[i] == 'F') hex_byte = 15;
                else hex_byte = hex_str[i] - '0';

                result.uLimbs[idx] = (result.uLimbs[idx] << 4) | hex_byte;
                i++;
            }
            continue;
        }

        for (int j = 0; j < 8; j++)
        {
            if (hex_str[i] == 'A') hex_byte = 10;
            else if (hex_str[i] == 'B') hex_byte = 11;
            else if (hex_str[i] == 'C') hex_byte = 12;
            else if (hex_str[i] == 'D') hex_byte = 13;
            else if (hex_str[i] == 'E') hex_byte = 14;
            else if (hex_str[i] == 'F') hex_byte = 15;
            else hex_byte = hex_str[i] - '0';

            result.uLimbs[idx] = (result.uLimbs[idx] << 4) | hex_byte;
            i++;
        }
        idx--;
    }


    while (result.iNumOfLimbs > 1 && result.uLimbs[result.iNumOfLimbs - 1] == 0)
    {
        result.iNumOfLimbs--;
    }

    return result;
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
        //printf("\nSubBigNums() : [!]Can't subtract bigger value from lesser.");
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
        //printf("\n[!]Subtracted bigger from lesser. Undefined behaviour.");
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


void LongShiftDigitsToHigh(bignum *a, unsigned int limb_shifts)
{

    if (limb_shifts == 0 || a->iNumOfLimbs == 0) return;

    int old_len = (int)a->iNumOfLimbs;
    unsigned int new_len = old_len + limb_shifts;

    BignumReserve(a, new_len);
    for (int i = old_len - 1; i >= 0; i--)
    {
        a->uLimbs[i + limb_shifts] = a->uLimbs[i];
    }


    for (unsigned int i = 0; i < limb_shifts; i++)
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


int MSB(const bignum *a)
{
    //so, basically i need to count limbs and multiply it by 32 (because uint32_t, ok)
    //but what if there are leading zeroes in the last limb
    //like 0000000000011 or smth

    //lets just multiply: (a.iNumOfLimbs - 1) * 32
    //and in the last limb I will count bits manually by shifting limb to the left until it becomes 0
    //the amount of shifts will be the amount of bits

    int count = 0;
    if (a->iNumOfLimbs == 0) return -1;
    uint32_t top_limb = a->uLimbs[a->iNumOfLimbs - 1];
    while ( top_limb != 0)
    {
        count++;
        top_limb >>= 1;

    }

    int length = (a->iNumOfLimbs - 1) * 32 + count - 1;
    return length - 1;
}


//it could be used as an equivalent to lsr, if powers of two are passed as an argument
void LongShiftBitsToHigh(const bignum *src, unsigned int shift_bits, bignum *dest)
{
    //if there is no bits to shift for -> simply copy bignum from src to dest
    //otherwise the procedure is a bit complicated
    //i have to condsider shifts of the limbs and shifts inside those limbs
    //shifts of the limbs depend on how much the shift_bits will be larger than the size of one limb, in  my case 32 bits
    //if shift_bits == 64 => there will be two additional limbs and the first two will be zeroes, because we shifted original two limbs to the "right"
    //inside those limbs we are limited with only 32 bytes of possible shifts, so we have to calculate remainder  of shift_bits % 32


    if (shift_bits == 0)
    {
        dest->uCapacity = src->iNumOfLimbs + 1;
        dest->iNumOfLimbs = src->iNumOfLimbs;
        dest->uLimbs = (uint32_t*)calloc(dest->uCapacity, sizeof(uint32_t));
        memcpy(dest->uLimbs, src->uLimbs, src->iNumOfLimbs * sizeof(uint32_t));
        return;
    }

    unsigned int limb_shifts = shift_bits / 32;
    unsigned int bit_shifts  = shift_bits % 32;

    dest->uCapacity = src->iNumOfLimbs + limb_shifts + 2;
    dest->iNumOfLimbs = src->iNumOfLimbs + limb_shifts + 1;
    dest->uLimbs = (uint32_t*)calloc(dest->uCapacity, sizeof(uint32_t));


    //when the bits in the limb are shifted we have to carry bytes that go "out of scope" to the next limb
    //but we have to store "out of scope" bytes somewhere to write them into the next limb
    //we can extend our 32bit limb to 64 bit, in this case first 32 bits will be zeroes
    //if we shift this bits to the left:
    // (suppose originally we had 8bit number, after the extension 110110001 -> 00000000 11011001 and after the shift of 3 -> 00000110 11001000
    //right part is what have to be stored in the current limb, left - what need to be carried, we can add carry with OR
    uint32_t carry = 0;
    for (unsigned int i = 0; i < src->iNumOfLimbs; i++)
    {
        uint64_t current = ((uint64_t)src->uLimbs[i] << bit_shifts) | carry; //store shifted bytes in the extended variable, add carry if any, carry is added to the last 32 bit
        dest->uLimbs[i + limb_shifts] = (uint32_t)current;
        carry = (uint32_t)(current >> 32);
    }
    if (carry > 0)
    {
        dest->uLimbs[src->iNumOfLimbs + limb_shifts] = carry;
    }
    while (dest->iNumOfLimbs > 1 && dest->uLimbs[dest->iNumOfLimbs - 1] == 0)
    {
        dest->iNumOfLimbs--;
    }
}

void LongShiftBitsToLow(const bignum* src, unsigned int shift_bits, bignum* dest)
{
    //if there is no bits to shift for -> simply copy bignum from src to dest
    if (shift_bits == 0)
    {
        dest->uCapacity = src->iNumOfLimbs;
        dest->iNumOfLimbs = src->iNumOfLimbs;
        dest->uLimbs = (uint32_t*)calloc(dest->uCapacity, sizeof(uint32_t));
        memcpy(dest->uLimbs, src->uLimbs, src->iNumOfLimbs * sizeof(uint32_t));
        return;
    }

    //otherwise
    unsigned int limb_shifts = shift_bits / 32;
    unsigned int bit_shifts = shift_bits % 32;

    dest->uCapacity = src->iNumOfLimbs - limb_shifts + 1;
    dest->iNumOfLimbs = src->iNumOfLimbs - limb_shifts;
    dest->uLimbs = (uint32_t*)calloc(dest->uCapacity, sizeof(uint32_t));

    uint32_t carry = 0;
    for (int i = (int)src->iNumOfLimbs - 1; i >= (int)limb_shifts; i--)
    {
        uint64_t current = ((uint64_t)src->uLimbs[i] >> bit_shifts) | carry;
        dest->uLimbs[i - limb_shifts] = (uint32_t)current;

        if (bit_shifts > 0)
        {
            carry = (uint32_t)(src->uLimbs[i] << (32 - bit_shifts));

        }
    }
    while (dest->iNumOfLimbs > 1 && dest->uLimbs[dest->iNumOfLimbs - 1] == 0)
    {
        dest->iNumOfLimbs--;
    }
}

//this function returns two results in one structure: quotient and remainder
div_result LongDivBignum(bignum a, bignum b)
{
    //a = b*q + r
    //неважливо, чи a > b, чи b > a

    int k = MSB(&b);

    //have to copy a into r
    bignum r;
    r.iNumOfLimbs = a.iNumOfLimbs;
    r.uCapacity = a.uCapacity;
    r.uLimbs = (uint32_t*)calloc(r.uCapacity, sizeof(uint32_t));
    memcpy(r.uLimbs, a.uLimbs, a.iNumOfLimbs * sizeof(uint32_t));

    //and q is just initialized
    bignum q;
    q.iNumOfLimbs = 1;
    q.uCapacity = 1;
    q.uLimbs = (uint32_t*)calloc(q.uCapacity, sizeof(uint32_t));
    //calloc automatically sets all the bits to zero, so I do not need to set q to zero manually

    while (Compare(r, b) >= 0)
    {
        int t = MSB(&r);
        int shift = t - k;

        bignum c;

        LongShiftBitsToHigh(&b, t - k, &c);
        if (Compare(r, c) == -1)
        {
            free(c.uLimbs);
            t -= 1;
            LongShiftBitsToHigh(&b, t -k, &c);
        }

        sub_result subres;
        subres = SubBigNums(&r, &c);
        r = subres.diff;
        free(c.uLimbs);
        unsigned int bit = 0;
        SetBit(&q, t - k , 1);
    }

    div_result result;
    result.q = q;
    result.r = r;

    return result;
}


unsigned int GetBit(bignum *a, unsigned int bit_index)
{
    unsigned int index_in_limb = bit_index % 32;
    unsigned int limb_index = bit_index / 32;

    if (limb_index >= a->iNumOfLimbs) return 0;
    return (a->uLimbs[limb_index] >> index_in_limb ) & (uint32_t)1;
}


bignum LongPower(bignum * a, bignum *b)
{
    bignum result;
    result.iNumOfLimbs = 1;
    result.uCapacity = 4;
    result.uLimbs = (uint32_t*)calloc(result.uCapacity, sizeof(uint32_t));
    result.uLimbs[0] = 1;

   
    for(int i = MSB(b); i >= 0; i--)
    {
        if(GetBit(b, i) == 1)
        {
            bignum temp = LongMul(&result, a);
            free(result.uLimbs);
            result = temp;
        }
        if(i != 0)
        {
            bignum temp = LongMul(&result, &result);
            free(result.uLimbs);
            result = temp;
        }
    }

    return result;

}
