#include "resource.h"

void p2bf(char* poly, bignum *r)
{
	// # define the degree of the polynomial
	
	char str_deg[6];
	sprintf(str_deg, "%c%c%c", poly[2], poly[3], poly[4]);
	int deg = atoi(str_deg);
	printf("[+]The degree of the polynom : %d\n", deg);


	BignumReserve(r, deg / 32);
	r->iNumOfLimbs = r->uCapacity;

	int idx = 0;
	for (int i = 0; i < strlen(poly); i++)
	{
		int current_deg = 0;
		
		if (poly[i] != 'x' && poly[i] != '+' && poly[i] != ' ' && poly[i] != '^')
		{
			str_deg[idx] = poly[i];
			idx++;
		}
		else if (i != 0 && i != 1)
		{
			deg = atoi(str_deg);
			SetBit(r, deg, 1);
			memset(str_deg, 0, strlen(str_deg) * sizeof(char));
			//sprintf(str_deg, " ");
			idx = 0;
			deg = 0;
		}
		else continue;
	}
}


void bf2p(bignum* p)
{

}

void Reduct(bignum* p, bignum* g, bignum *result)
{
	//p(x) mod g(x)
	int bits_p = MSB(p);
	int bits_g = MSB(g);

	bignum temp_p = { 0 };
	bignum temp_g = { 0 };
	Copy(p, &temp_p);
	Copy(g, &temp_g);


	while (bits_p > bits_g)
	{
		// XOR =: a - b ~ a + b
		bignum temp1 = { 0 };
		LongShiftBitsToHigh(&temp_g, bits_p - bits_g, &temp1);
		bignum temp2 = { 0 };
		AddPoly(temp_p, temp1, &temp2);
		Copy(&temp2, &temp_p);
		bits_p = MSB(&temp_p);
		
	}
	BignumReserve(result, temp_p.iNumOfLimbs);
	Copy(&temp_p, result);
	return;

}

void AddPoly(bignum a, bignum b, bignum* result)
{
	int max = 0;
	if (Compare(a, b) == 0) //a = b
	{
		bignum temp = SmallConstToBignum(0);
		Copy(result, &temp);
		return;
	}
	else if (Compare(a, b) == 1) //a > b
	{
		max = a.iNumOfLimbs;
		BignumReserve(result, max);
	}
	else
	{
		max = b.iNumOfLimbs;
		BignumReserve(result, max);

	}

	for (int i = 0; i < max; i++)
	{
		result->uLimbs[i] = a.uLimbs[i] ^ b.uLimbs[i];
	}
	
	result->iNumOfLimbs = max;
	while (result->iNumOfLimbs > 1 && result->uLimbs[result->iNumOfLimbs - 1] == 0)
	{
		result->iNumOfLimbs--;
	}
	return;
}

void Square(bignum* p, bignum* r)
{
	int m = MSB(p);
	int idx = 0;

	BignumReserve(r, 2 * m - 1);

	for (int i = 0; i < m; i++)
	{
		int bit = GetBit(p, idx);
		if (i % 2 == 0) SetBit(r, i, bit);
		else SetBit(r, i, 0);
	}

}



//int Trace(bignum* p)
//{
//	int m = MSB(p);
//	int result = 0;
//	for (int i = 0; i < m; i++)
//	{
//		result += ToPower(p, a);
//	}
//	if (result % 2 == 0) return 0;
//	else return 1;
//}