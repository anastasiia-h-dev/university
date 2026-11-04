#include "BigNumArithmetic.h"
#include <stdio.h>


int main()
{
    bignum a = StrHexToBignum("8F1A2B3C4D5E6F708192A3B4C5D6E7F8091A2B3C4D5E6F708192A3B4C5D6E7F8FEEDFACEDEADBEEFCAFEBABEDEADBEEF0102030405060708090A0B0C0D0E0F10AA55AA55AA55AA5555AA55AA55AA55AA112233445566778899AABBCCDDEEFF0000FFEEDDCCBBAA998877665544332211A1B2C3D4E5F607182938475610293847");
    bignum b = StrHexToBignum("C4B9E2568F3A01D78B2E49C1045F98A2DE67104B8C9A3E0F1245789ABCDEF0123456789ABCDEF012456789ABCDEF012389ABCDEF01234567FEDCBA9876543210A1B2C3D4E5F607182938475610293847BBAACCDDEEFF00112233445566778899FF00EE11DD22CC33BB44AA5599668877123456789ABCDEF0FEDCBA987654321F");
    bignum mod = StrHexToBignum("D5C8A79E2B1F4C3D8E9A0B1C2D3E4F5A6B7C8D9E0F1A2B3C4D5E6F708192A3B4C5D6E7F8091A2B3C4D5E6F708192A3B4C5D6E7F8FEEDFACEDEADBEEFCAFEBABE0102030405060708090A0B0C0D0E0F10AA55AA55AA55AA5555AA55AA55AA55AA112233445566778899AABBCCDDEEFF0000FFEEDDCCBBAA998877665544332211A1B2C3D4E5F607182938475610293847FF00EE11DD22CC33BB44AA5599668877123456789ABCDEF0FEDCBA987654321FAABBCCDDEEFF001122334455667788998F3A01D78B2E49C1045F98A2DE67104B8C9A3E0F1245789ABCDEF0123456789ABCDEF012456789ABCDEF012389ABCDEF01234567FEDCBA9876543210DEADBEEF");
    //bignum c = StrHexToBignum("83889870047121237358393355963179412025156708933145532941988513237067418482960930963348147502384998256637325592737728028355830056531923442626194590957021884874265636885073118302091094176994486795373681504492424370236335506502161556638487982996896211972553251927113361087354892038100034067521427131405865691978584327387161629600011294261507038");

    ////bignum from_site = StrToBinaryBignum("19322337836372117309330124532149032320776630525308637927761838668007158742031690749434143950174389270248413802255816255456556500776630525308637927761838668007158742031690749434143950174389270248413802255816255456556500776630525308637927761838668007158742031690749434143950174389270248413802255816255456556500776630525308637927761838668007158472201126999420853094133188932294244276348004710753380754193918358537972118972377495015818032620162086380596491756639932294244276348004710753380754193918358537972118972377495015818032620162086380596491756639932294244276348004710753380754193918358537972118972377495015818032620162086380596491756639932294244276348004710753380754193918358537973");
    ////printf("\n\nfrom_site : ");
    ////PrintNumHex(from_site);

    int bits = MSB(&a) + 1;
    printf("\nbits : %d", bits);
    printf("\na : ");
    PrintNumHex(a);

    bits = MSB(&b) + 1;
    printf("\n\nbits : %d", bits);
    printf("\nb : ");
    PrintNumHex(b);

    //bits = MSB(&c) + 1;
    //printf("\n\nbits : %d", bits);
    //printf("\nc : ");
    //PrintNumHex(c);

    bits = MSB(&mod) + 1;
    printf("\n\nbits : %d", bits);
    printf("\nn : ");
    PrintNumHex(mod);

    //////передобчислення мю
    int k = MSB(&mod) + 1;
    bignum one = SmallConstToBignum(1);
    bignum myu_to_deg = { 0 };
    LongShiftBitsToHigh(&one, 2 * k, &myu_to_deg); //myu_to_deg = 2^t, t = deg(a)
    div_result myu = LongDivBignum(myu_to_deg, mod);

    //bignum gcd_result = { 0 };
    //gcd(a, b, &gcd_result);
    //printf("\n\ngcd() : ");
    //PrintNumHex(gcd_result);

    //bignum lcm_result = { 0 };
    //printf("\n\nlcm() : ");
    //lcm(a, b, &lcm_result);
    //PrintNumHex(lcm_result);

    bignum barrett_result = { 0 };
    printf("\n\na mod n = ");
    reduct(&a, &mod, &barrett_result, &myu.q);
    PrintNumHex(barrett_result);

    //bignum add_result = { 0 };
    //printf("\n\na + b mod n = ");
    //ModAdd(&a, &b, &mod, &add_result, &myu.q);
    //PrintNumHex(add_result);

    bignum sub_result = { 0 };
    printf("\n\na - b mod n = ");
    ModSub(&a, &b, &mod, &sub_result, &myu.q);
    PrintNumHex(sub_result);

    bignum mul_result = { 0 };
    printf("\n\na * b mod n = ");
    ModMul(&a, &b, &mod, &mul_result, &myu.q);
    PrintNumHex(mul_result);


    bignum sq_result = { 0 };
    printf("\n\na^2 mod n = ");
    ModSquare(&a,&mod, &sq_result, &myu.q);
    PrintNumHex(sq_result);

    bignum pow_result = ModPower(&a, &b, &mod, &myu.q);

    printf("\n\na^b mod n = ");
    PrintNumHex(pow_result);

    printf("\n\nLongPowerWindow() : ");
    bignum result = { 0 };
    LongPowerWindow(&a, &b, mod, myu.q, &result);
    PrintNumHex(result);


    //TEST1
      //printf("\n[+]num1 :\n ");
      //PrintNumHex(num1);

      //printf("\n[+]num2 :\n ");
      //PrintNumHex(num2);

      //printf("\n[+]num3 :\n ");
      //PrintNumHex(num3);


      //printf("\n\nTESTS");
      //printf("\n\n1)");
      //bignum add= { 0 };
      //ModAdd(&a, &b, &mod, &add, &myu.q);
      //bignum num5 = { 0 };
      //ModMul(&add, &c, &mod, &num5, &myu.q);
      //printf("\n[+](a + b) * c  mod n = ");
      //PrintNumHex(num5);

      //bignum num6 = { 0 };
      //ModMul(&a, &c, &mod, &num6, &myu.q);
      //bignum num7 = { 0 };
      //ModMul(&b, &c, &mod, &num7, &myu.q);
      //bignum add_result1 = { 0 };
      //ModAdd(&num6, &num7, &mod, &add_result1, &myu.q);
      //printf("\n[+]a * c + b * c  = ");
      //PrintNumHex(add_result1);


      //printf("\n\n2)");
      //bignum num4 = { 0 };
      //bignum n220 = StrToBinaryBignum("220");
      //ModMul(&a, &n220, &mod, &num4, &myu.q);
      //printf("\n\n[+]a * 220  mod n =  ");
      //PrintNumHex(num4);
      //
      //bignum temp = SmallConstToBignum(0);
      //for (int i = 0; i < 220; i++)
      //{
      //    bignum old = { 0 };
      //    Copy(&temp, &old);
      //    old.iNumOfLimbs = temp.iNumOfLimbs;
      //    //bignum temp_result = { 0 };
      //    ModAdd(&a, &old, &mod, &temp, &myu.q);
      //    //free(old.uLimbs);
      //}


      //printf("\n[+]a  + ... + a (220 times) = ");
      //PrintNumHex(temp);

      //CHECK STATS
      //srand(time(NULL));
      //TestOperation(5);
      //TestOperation(300);
      //TestOperation(10000);
    return 0;
}
