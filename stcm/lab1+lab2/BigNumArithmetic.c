#include "BigNumArithmetic.h"

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
    unsigned int index_in_limb = bit_index % 32;
    unsigned int limb_index = bit_index / 32;

    if (limb_index >= num->uCapacity)
    {
        BignumReserve(num, limb_index + 1);
    }
    if (bit == 1)
    {
        num->uLimbs[limb_index] |= ((uint32_t)1 << index_in_limb);
    }
    else
    {
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

        SetBit(&result, bit_idx, remainder);
        bit_idx++;

        int zero = 0;
        while(temp_number[zero] == '0' && zero < idx - 1)
        {
            zero++;
        }

        curlen = idx - zero;
        memmove(current, temp_number + zero, curlen + 1);
        current[curlen] = '\0';
        
    }
    free(current);
    free(temp_number);

    return result;
}

bignum StrHexToBignum(char* hex_str)
{
    int len = (int)strlen(hex_str);
    if (len == 0)
    {
        return SmallConstToBignum(0);
    }

    bignum result;
    result.iNumOfLimbs = (len + 7) / 8;
    result.uCapacity = result.iNumOfLimbs + 1;
    result.uLimbs = (uint32_t*)calloc(result.uCapacity, sizeof(uint32_t));

    int limb_idx = 0;
    for (int end = len; end > 0; end -= 8)
    {
        int start = (end >= 8) ? (end - 8) : 0;
        uint32_t limb_val = 0;

        for (int i = start; i < end; i++)
        {
            char c = hex_str[i];
            uint8_t val = 0;

            if (c >= '0' && c <= '9') val = c - '0';
            else if (c >= 'a' && c <= 'f') val = c - 'a' + 10;
            else if (c >= 'A' && c <= 'F') val = c - 'A' + 10;
            else continue;

            limb_val = (limb_val << 4) | val;
        }

        result.uLimbs[limb_idx++] = limb_val;
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
    unsigned int na = a.iNumOfLimbs;
    unsigned int nb = b.iNumOfLimbs;

    while (a.iNumOfLimbs != 0 && a.uLimbs[na - 1] == 0)
    {
        a.iNumOfLimbs--;
        na--;
    }
    while (b.iNumOfLimbs != 0 && b.uLimbs[nb - 1] == 0)
    {
        b.iNumOfLimbs--;
        nb--;
    }
    if (na > nb)
    {
        return 1;
    }
    if (nb > na)
    {
        return -1;
    }

    for (int i = na - 1; i >= 0; i--)
    {
        if (a.uLimbs[i] > b.uLimbs[i]) return 1;
        if (a.uLimbs[i] < b.uLimbs[i]) return -1;
    }

    return 0;
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

int MSB(const bignum* a)
{
    if (a == NULL || a->uLimbs == NULL ||
        a->iNumOfLimbs == 0)
    {
        return -1;
    }

    int i = (int)a->iNumOfLimbs - 1;

    while (i >= 0 && a->uLimbs[i] == 0)
    {
        i--;
    }

    if (i < 0)
    {
        return -1; // Число дорівнює нулю
    }

    uint32_t top_limb = a->uLimbs[i];
    int count = 0;

    while (top_limb != 0)
    {
        count++;
        top_limb >>= 1;
    }

    return i * 32 + count - 1;
}

//it could be used as an equivalent to lsr, if powers of two are passed as an argument
void LongShiftBitsToHigh(const bignum *src, unsigned int shift_bits, bignum *dest)
{

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

    dest->uCapacity = src->iNumOfLimbs;
    dest->iNumOfLimbs = dest->uCapacity;
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



//LAB2
void gcd(bignum a, bignum b, bignum* res)
{

    //ініціалізація
    int d = 1;
    bignum two = SmallConstToBignum(2);
    bignum one = SmallConstToBignum(1);

    //ділю спочатку на два, це сильно не змінить роботу циклу він і так ділить на два, якщо зараз поділю і вийде непарне, ну то значить в цикл навіть не зайде програма
    //якщо виявиться, що обидва парні, то заходжу в цикл, щоб звести один з них (або два) остаточно до непарного

    div_result div_res_a = LongDivBignum(a, one);
    div_result div_res_b = LongDivBignum(b, one);

    //bignum div_res;
    //div_res.iNumOfLimbs = 2;
    //div_res.uCapacity = div_res.iNumOfLimbs + 1;
    //div_res.uLimbs = (uint32_t*)calloc(div_res.uCapacity, sizeof(uint32_t));

    while (isEven(a) && isEven(b))
    {

        //div_res.uLimbs = div_res_a.q.uLimbs;
        div_res_a = LongDivBignum(a, two);

        //div_res.uLimbs = div_res_b.q.uLimbs;
        div_res_b = LongDivBignum(b, two);
        a = div_res_a.q;
        b = div_res_b.q;

        d *= 2;
    }

    //отримали, що a - непарне та/або b - непарне

    while (isEven(a))
    {
        div_res_a = LongDivBignum(div_res_a.q, two);
        a = div_res_a.q;
    }

    while (b.uLimbs[0] != 0)
    {
        while (isEven(b))
        {
            div_res_b = LongDivBignum(b, two);
            b = div_res_b.q;
        }

        bignum min;
        sub_result sub_res;
        if (Compare(a, b) == -1)
        {
            min = a;
            sub_res = SubBigNums(&b, &min);

        }
        else
        {
            min = b;
            sub_res = SubBigNums(&a, &min);
        }

        a = min;
        b = sub_res.diff;
    }
    bignum result = { 0 };
    result = LongMulOneDigit(&a, d);

    BignumReserve(res, result.iNumOfLimbs);

    for (unsigned int i = 0; i < result.iNumOfLimbs; i++)
    {
        res->uLimbs[i] = result.uLimbs[i];
    }

    res->iNumOfLimbs = result.iNumOfLimbs;
}

void lcm(bignum a, bignum b, bignum *result)
{
    

    bignum g = { 0 };
    bignum quotient = { 0 };
    bignum product = { 0 };

    // g = gcd(a, b)
    gcd(a, b, &g);

    // quotient = a / g
    div_result div = LongDivBignum(a, g);
    quotient = div.q;

    product = LongMul(&div.q, &b);


    BignumReserve(result, product.iNumOfLimbs);
    for (int i = 0; i < product.iNumOfLimbs; i++)
    {
        result->uLimbs[i] = product.uLimbs[i];
    }
    while (result->iNumOfLimbs >= 1 && result->uLimbs[result->iNumOfLimbs - 1] == 0)
    {
        result->iNumOfLimbs--;
    }
}

bool isEven(bignum a)
{
    bignum two = SmallConstToBignum(2);
    div_result div_res_a = LongDivBignum(a, two);
    if (div_res_a.r.uLimbs[0] == 0)
    {
        return true;
    }
    else return false;
}

void reduct(bignum* a, bignum* mod, bignum* result, bignum* myu)
{
    // Якщо a < mod, редукція не потрібна
    if (Compare(*a, *mod) < 0)
    {
        BignumReserve(result, a->iNumOfLimbs);
        memcpy(result->uLimbs, a->uLimbs, a->iNumOfLimbs * sizeof(uint32_t));
        result->iNumOfLimbs = a->iNumOfLimbs;
        return;
    }

    int k = MSB(mod) + 1;
    bignum shifted_a = { 0 };
    bignum shifted_q = { 0 };
    
    
    LongShiftBitsToLow(a, k - 1, &shifted_a);

    bignum product_1 = LongMul(&shifted_a, myu);
    free(shifted_a.uLimbs);

    LongShiftBitsToLow(&product_1, k + 1, &shifted_q);
    free(product_1.uLimbs);

    bignum product_2 = LongMul(&shifted_q, mod);
    free(shifted_q.uLimbs);

    sub_result r = SubBigNums(a, &product_2);
    free(product_2.uLimbs);

    bignum cur_r = r.diff;

    while (Compare(cur_r, *mod) >= 0)
    {
        sub_result sub_step = SubBigNums(&cur_r, mod);
        free(cur_r.uLimbs);
        cur_r = sub_step.diff;
    }

    BignumReserve(result, cur_r.iNumOfLimbs);
    for (int i = 0; i < cur_r.iNumOfLimbs; i++)
    {
        result->uLimbs[i] = cur_r.uLimbs[i];
    }
    
    result->iNumOfLimbs = cur_r.iNumOfLimbs;

    free(cur_r.uLimbs);
}

bignum ExtractBitWindow(const bignum* a, unsigned int start_bit, unsigned int num_bits)
{
//зсуваю потрібне вікно до молодших бітів та створюю маску з одиниць 
//bits & mask = біти у вікні

    bignum shifted = { 0 };
    bignum one = SmallConstToBignum(1);
    bignum power = { 0 };
    
    LongShiftBitsToLow(a, start_bit, &shifted);
    LongShiftBitsToHigh(&one, num_bits, &power);

    sub_result s = SubBigNums(&power, &one);
    free(power.uLimbs);
    free(one.uLimbs);

    bignum mask = s.diff;

    //залишаю тільки молодші num_bits
    if (shifted.iNumOfLimbs > mask.iNumOfLimbs) {
        shifted.iNumOfLimbs = mask.iNumOfLimbs;
    }
    for (unsigned int i = 0; i < shifted.iNumOfLimbs; i++) {
        shifted.uLimbs[i] &= mask.uLimbs[i];
    }
    while (shifted.iNumOfLimbs > 1 && shifted.uLimbs[shifted.iNumOfLimbs - 1] == 0) {
        shifted.iNumOfLimbs--;
    }

    free(mask.uLimbs);
    return shifted;
}

void BarrettMod(bignum* a, bignum* n, bignum* myu, bignum* result)
{
    // Якщо a < n — повертаємо точну копію a
    if (Compare(*a, *n) < 0)
    {
        BignumReserve(result, a->iNumOfLimbs);
        for(int i = 0; i < a->iNumOfLimbs; i++)
        {
        result->uLimbs[i] = a->uLimbs[i];
        }
        result->iNumOfLimbs = a->iNumOfLimbs;
        return;
    }

    int k = MSB(n) + 1;
    int a_bits = MSB(a) + 1;

    if (a_bits <= 2*k)
    {
        result->iNumOfLimbs = 1;
        result->uCapacity = n->iNumOfLimbs + 1;
        result->uLimbs = (uint32_t*)calloc(result->uCapacity, sizeof(uint32_t));
        reduct(a, n, result, myu);
        return;
    }

    int first_block_len = (a_bits % k == 0) ? k : (a_bits % k);
    int window_start = a_bits - first_block_len;

    bignum remainder = ExtractBitWindow(a, window_start, first_block_len);
    int current_bit = window_start;

    while (current_bit > 0)
    {
        int chunk_size = (current_bit >= k) ? k : current_bit;
        current_bit -= chunk_size;

        bignum shifted_rem = { 0 };
        LongShiftBitsToHigh(&remainder, chunk_size, &shifted_rem);
        free(remainder.uLimbs);

        bignum chunk = ExtractBitWindow(a, current_bit, chunk_size);

        bignum temp = AddBigNums(&shifted_rem, &chunk);
        free(shifted_rem.uLimbs);
        free(chunk.uLimbs);

        // Підготовка буфера під результат перед викликом
        remainder.iNumOfLimbs = 1;
        remainder.uCapacity = n->iNumOfLimbs + 1;
        remainder.uLimbs = (uint32_t*)calloc(remainder.uCapacity, sizeof(uint32_t));

        reduct(&temp, n, &remainder, myu);
        free(temp.uLimbs);
    }

    BignumReserve(result, a->iNumOfLimbs);
    for(int i = 0; i < remainder.iNumOfLimbs; i++)
    {
     result->uLimbs[i] = remainder.uLimbs[i];
    }
    result->iNumOfLimbs = remainder.iNumOfLimbs;
    free(remainder.uLimbs);
}



void ModAdd(bignum *a, bignum *b, bignum *n, bignum *result, bignum *myu)
 {
     bignum num = AddBigNums(a, b);
     BarrettMod(&num, n, myu, result);
 }

int ModSub(bignum *a, bignum *b, bignum *n, bignum *result, bignum *myu)
 {
     sub_result sub_res = SubBigNums(a, b);
     if (sub_res.iBorrow != 0)
     {
         return - 1;
     }
     BarrettMod(&sub_res.diff, n, myu, result);
     return 0;
 }

void ModMul(bignum* a, bignum* b, bignum* n, bignum* result, bignum* myu)
 {

     bignum mul = LongMul(a, b);
     BarrettMod(&mul, n, myu, result);
 }

 void ModSquare(bignum* a, bignum* n, bignum* result, bignum* myu)
 {
     bignum square = SquareBignum(a);
     BarrettMod(&square, n, myu, result);
 }

 void Copy(bignum* src, bignum* dest)
 {
     BignumReserve(dest, src->iNumOfLimbs);
     for (int i = 0; i < src->iNumOfLimbs; i++)
     {
         dest->uLimbs[i] = src->uLimbs[i];
     }
 }

void ModPower(bignum* a, bignum* b, bignum* n, bignum* res, bignum* myu)
 {
     bignum C = SmallConstToBignum(1);

     for (int i = MSB(b); i >= 0; i--)
     {
         if (GetBit(b, i) == 1)
         {

             bignum temp = LongMul(&C, a);
             BarrettMod(&temp, n, myu, &C);
             //free(temp.uLimbs);
         }
         if (i != 0)
         {
             bignum temp = SquareBignum(&C);
             //free(result.uLimbs);
             BarrettMod(&temp, n, myu, &C);
             //free(temp.uLimbs);

         }
     }

     BignumReserve(res, C.iNumOfLimbs);
     for (int i = 0; i < C.iNumOfLimbs; i++)
     {
         res->uLimbs[i] = C.uLimbs[i];
     }
     res->iNumOfLimbs = C.iNumOfLimbs;
 }

 void LongPowerWindow(bignum *a, bignum *b, bignum *result)
 {
     //t = 4
     bignum C = SmallConstToBignum(1);

     DegTable D;
     D[0].num = SmallConstToBignum(1);
     D[1].num.iNumOfLimbs = a->iNumOfLimbs;
     D[1].num.uCapacity = a->uCapacity;
     D[1].num.uLimbs = (uint32_t*)calloc(D[1].num.uCapacity, sizeof(uint32_t));

     for (int i = 0; i < a->iNumOfLimbs; i++)
     {  
         
         D[1].num.uLimbs[i] = a->uLimbs[i];  
     }
     //i <= 2^4 - 1
     for(int i = 2; i <= 15; i++)
     {
         D[i].num = LongMul(&D[i-1].num, a);
     }

     int m = MSB(b) + 1;
     int first_block_len = (m % 4 == 0) ? 4 : (m % 4);
     int window_start = m - first_block_len;


     for (int i = window_start; i >= 0; i -= 4)
     {
         bignum window = ExtractBitWindow(b, i, 4);
         unsigned int idx = window.uLimbs[0];

         for (int j = 0; j < 4; j++)
         {
             C = SquareBignum(&C);
         }

         C = LongMul(&C, &D[idx].num);

         free(window.uLimbs);
     }
     BignumReserve(result, C.iNumOfLimbs);
     for (int i = 0; i < C.iNumOfLimbs; i++)
     {
         result->uLimbs[i] = C.uLimbs[i];
     }
     result->iNumOfLimbs = C.iNumOfLimbs;
 }
