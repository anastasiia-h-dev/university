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
	Copy(p, &temp_p);


	while (bits_p >= bits_g)
	{
		// XOR =: a - b ~ a + b
		bignum temp1 = { 0 };
		LongShiftBitsToHigh(g, bits_p - bits_g, &temp1);
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
	int min = 0;
	if (Compare(a, b) == 0) //a = b
	{
		bignum temp = SmallConstToBignum(0);
		Copy(result, &temp);
		return;
	}
	else if (Compare(a, b) == 1) //a > b
	{
		min = b.iNumOfLimbs;
		Copy(&a, result);
	}
	else
	{
		min = a.iNumOfLimbs;
		Copy(&b, result);

	}

	for (int i = 0; i < min; i++)
	{
		result->uLimbs[i] = a.uLimbs[i] ^ b.uLimbs[i];
	}

	while (result->iNumOfLimbs > 1 && result->uLimbs[result->iNumOfLimbs - 1] == 0)
	{
		result->iNumOfLimbs--;
	}
	return;
}


void Square(bignum* p, bignum *g, bignum* r)
{
	int m = MSB(p);
	int idx = 0;

	bignum temp = { 0 };
	BignumReserve(&temp, (2 * m + 2)/32 + 2);
	temp.iNumOfLimbs = (2 * m + 2) / 32 +2;
	for (int i = 0; i <= 2*m; i++)
	{
		if (i % 2 == 0)
		{
			int bit = GetBit(p, idx);
			SetBit(&temp, i, bit);
			idx++;
		}
		else SetBit(&temp, i, 0);
		
	}
	Reduct(&temp, g, r);

}


int Trace(bignum* p, bignum *g)
{
	int m = MSB(g);
	bignum tmp = {0};
	Reduct(p, g, &tmp);

	bignum c= SmallConstToBignum(0);

	for (int i = 0; i < m; i++)
	{
		bignum temp1 = { 0 };
		AddPoly(c, tmp, &temp1);
		Copy(&temp1, &c);

		bignum temp2 = { 0 };
		Square(&tmp, g, &temp2);
		Copy(&temp2, &tmp);
		free(temp1.uLimbs);
		free(temp2.uLimbs);
	}
	bignum temp3 = { 0 };
	Reduct(&c, g, &temp3);
	if (c.iNumOfLimbs == 0) return 0;
	else	return temp3.uLimbs[0];
	/*if (result % 2 == 0) return 0;
	else return 1;*/
}


void XTime(bignum* a, bignum* b, bignum* g, bignum* r)
{
	bignum temp_a = { 0 }, temp_b = { 0 }, temp_g = { 0 };
	Reduct(a, g, &temp_a);
	Reduct(b, g, &temp_b); //temp_b == b
	Copy(g, &temp_g);

	
	int m = MSB(g);
	bignum result = { 0 };
	BignumReserve(&result, m / 32 + 1);
	result.iNumOfLimbs = m / 32 + 1;

	for (int i = 0; i < m; i++)
	{
		if (GetBit(&temp_a, i) == 1)
		{
			bignum temp = { 0 };
			Copy(&result, &temp);
			AddPoly(temp, temp_b, &result);
			free(temp.uLimbs);
		}

		bignum temp = { 0 };
		LongShiftBitsToHigh(&temp_b, 1, &temp);

		Reduct(&temp, g, &temp_b);

		free(temp.uLimbs);
	}
	Reduct(&result, g, r);
}

void PowPoly(bignum* a, int c, bignum* g, bignum* r)
{
	int bits_a = MSB(a);

	bignum tmp = { 0 };
	tmp = SmallConstToBignum(1);

	for (int i = 0; i < c; i++)
	{
		bignum prev_a = { 0 };
		Copy(&tmp, &prev_a);
		XTime(a, &prev_a, g, &tmp);
		free(prev_a.uLimbs);
	}

	Reduct(&tmp, g, r);
}


void PowPolyHorner(bignum* a, bignum* c, bignum* g, bignum* r)
{
	int bits_c = MSB(c);

	bignum tmp = { 0 };
	tmp = SmallConstToBignum(1);

	for (int i = bits_c; i >= 0; i--)
	{
		bignum temp = { 0 };
		Square(&tmp, g, r);
		Copy(r, &tmp);
		if (GetBit(c, i) == 1)
		{
			XTime(a, &tmp, g, r);
			Copy(r, &tmp);
		}
		
	}

	Reduct(&tmp, g, r);
}

void Inverse(bignum* a, bignum* g, bignum* r)
{
	bignum temp = StrToBinaryBignum("1");
	bignum two = { 0 };
	LongShiftBitsToHigh(&temp,MSB(g), &two);


	bignum one = StrToBinaryBignum("2");
	sub_result deg = SubBigNums(&two, &one);

	PowPolyHorner(a, &deg.diff, g, &temp);
	Reduct(&temp, g, r);
}
