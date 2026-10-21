#include "BigNumArithmetic.h"
#include <stdio.h>


int main()
{
  //bignum a = StrToBinaryBignum("66946724917025018536804507050755969805075596980507559698050755969805102985241019041355911744351358200666102508923687115613227742337650577049173524475605856356143555634848353581890116030607217378309896984293924720722564468258404402351464682269515747138514555398827920372461624268471657711498194355701935292912542337939133411220470166836935656");
  //bignum b = StrHexToBignum("16482755264268635138843877971149688482178188995678615705058837669191734747294599647732595397930929778053533965105012647503085036285340931300872901385928133503233316838620031808340045221660367214046393609121717175504139921673426953016226778411456265511604869992333461651843142317950740969655595774684626456955774454895429692729000856988690942");
  //bignum mod = StrHexToBignum("162817349102837465192837465102938475610293847561029384756102938475610293847561029384756102933");
  //bignum c = StrHexToBignum("83889870047121237358393355963179412025156708933145532941988513237067418482960930963348147502384998256637325592737728028355830056531923442626194590957021884874265636885073118302091094176994486795373681504492424370236335506502161556638487982996896211972553251927113361087354892038100034067521427131405865691978584327387161629600011294261507038");

  ////bignum from_site = StrToBinaryBignum("19322337836372117309330124532149032320776630525308637927761838668007158742031690749434143950174389270248413802255816255456556500776630525308637927761838668007158742031690749434143950174389270248413802255816255456556500776630525308637927761838668007158742031690749434143950174389270248413802255816255456556500776630525308637927761838668007158472201126999420853094133188932294244276348004710753380754193918358537972118972377495015818032620162086380596491756639932294244276348004710753380754193918358537972118972377495015818032620162086380596491756639932294244276348004710753380754193918358537972118972377495015818032620162086380596491756639932294244276348004710753380754193918358537973");
  ////printf("\n\nfrom_site : ");
  ////PrintNumHex(from_site);

  //int bits = MSB(&a) + 1;
  //printf("\nbits : %d", bits);
  //printf("\na : ");
  //PrintNumHex(a);

  //bits = MSB(&b) + 1;
  //printf("\n\nbits : %d", bits);
  //printf("\nb : ");
  //PrintNumHex(b);

  //bits = MSB(&c) + 1;
  //printf("\n\nbits : %d", bits);
  //printf("\nc : ");
  //PrintNumHex(c);

  //bits = MSB(&mod) + 1;
  //printf("\n\nbits : %d", bits);
  //printf("\nn : ");
  //PrintNumHex(mod);

  //////передобчислення мю
  //int k = MSB(&mod) + 1;
  //bignum one = SmallConstToBignum(1);
  //bignum myu_to_deg = {0};
  //LongShiftBitsToHigh(&one,2 * k, &myu_to_deg); //myu_to_deg = 2^t, t = deg(a)
  //div_result myu = LongDivBignum(myu_to_deg, mod);

  //bignum gcd_result = { 0 };
  //printf("\n\ngcd() : ");
  //gcd(a, b, gcd_result);
  //PrintNumHex(gcd_result);

  //bignum lcm_result = { 0 };
  //printf("\n\nlcm() : ");
  //gcd(a, b, lcm_result);
  //PrintNumHex(lcm_result);

  //bignum barrett_result = { 0 };
  //printf("\n\na mod n = ");
  //BarrettMod(&a, &mod, &myu.q, &barrett_result);
  //PrintNumHex(barrett_result);

  //bignum add_result = { 0 };
  //printf("\n\na + b mod n = ");
  //ModAdd(&a, &b, &mod, &add_result, &myu.q);
  //PrintNumHex(add_result);

  //bignum sub_result = { 0 };
  //printf("\n\na - b mod n = ");
  //int code = ModSub(&a, &b, &mod, &sub_result, &myu.q);
  //if (code != 0) {
  //    printf("[!]Error : can't subtract bigger from lesser");
  //}
  //else PrintNumHex(sub_result);

  //bignum mul_result = { 0 };
  //printf("\n\na * b mod n = ");
  //ModMul(&a, &b, &mod, &mul_result, &myu.q);
  //PrintNumHex(mul_result);


  //bignum sq_result = { 0 };
  //printf("\n\na^2 mod n = ");
  //ModSquare(&a,&mod, &sq_result, &myu.q);
  //PrintNumHex(sq_result);

  //bignum pow_result = { 0 };
  //printf("\n\na^b mod n = ");
  //ModPower(&a, &b, &mod, &pow_result, &myu.q);
  //PrintNumHex(pow_result);

  //LongPowerWindow(&a, &b, &result);
  //PrintNumHex(result);


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
	srand(time(NULL));
    TestOperation(100);
    TestOperation(1000);
    TestOperation(10000);
  return 0;
}