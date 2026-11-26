#include "resource.h"

bignum P_ConstOne(bignum *g)
{
	int m = MSB(g) + 1;
	bignum res = { 0 };

	BignumReserve(&res, m / 32);
	res.iNumOfLimbs = m / 32 + 1;

	SetBit(&res, 0, 1);

	for (int i = 1; i < m; i++)
	{
		SetBit(&res, i, 0);
	}
	return res;
}

bignum P_ConstZero(bignum* g)
{
	int m = MSB(g) + 1;
	bignum res = { 0 };
	BignumReserve(&res, m / 32);
	res.iNumOfLimbs = m / 32;
	for (int i = 0; i < m; i++)
	{
		SetBit(&res, i, 0);
	}

	return res;
}

void Print(bignum a, int m)
{
	for (int j = m-1; j >= 0; j--)
	{
		// if(idx % 32 == 0) printf(" ");
		int bit = GetBit(&a, j);
		printf("%d", bit);
	}

}

void p2bf(char* poly, bignum *r)
{
	// # define the degree of the polynomial
	
	char str_deg[6];
	sprintf(str_deg, "%c%c%c", poly[2], poly[3], poly[4]);
	int deg = atoi(str_deg);


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
	int idx = 0;
	int bits = MSB(p);

	printf("x^%d ", bits);
	for (int j = bits - 1; j >= 0; j--)
	{
		
		// if(idx % 32 == 0) printf(" ");
		int bit = GetBit(p, j);
		if (j == 0 && bit == 1)
		{
			printf("+ 1");
			break;
		}
		if (bit == 0)
		{
			continue;
		}
		printf("+ x^%d ", j);
		idx++;
	}

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


void PrintInHex(char *A, char* B, char* C, bignum g)
{
	bignum num_A = StrHexToBignum(A);
	bignum num_B = StrHexToBignum(B);
	bignum num_C = StrHexToBignum(C);

	int bits_A = MSB(&num_A) + 1;
	int bits_B = MSB(&num_B) + 1;
	int bits_C = MSB(&num_C) + 1;
	//39     + 51
	//100111 ^ 110011 = 010100
	//A = 32 + 0 + 0 + 4 + 2 + 1  = 39
	//B = 32 + 16 + 0 + 0 + 2 + 1 = 51

	bignum add_without_reduction_result = { 0 };
	AddPoly(num_A, num_B, &add_without_reduction_result);

	printf("\nA (binary, %d bits) = ", bits_A);
	PrintNumHex(num_A);
	printf("\n\nB (binary, %d bits) = ", bits_B);
	PrintNumHex(num_B);
	printf("\n\nC (binary, %d bits) = ", bits_C);
	PrintNumHex(num_C);
	printf("\n\n ### POLYNOMIAL FORM ### \n");
	printf("g = ");
	bf2p(&g);
	printf("\nA = ");
	bf2p(&num_A);
	printf("\nB = ");
	bf2p(&num_B);
	printf("\nC = ");
	bf2p(&num_C);

	bignum reduction = { 0 };
	Reduct(&add_without_reduction_result, &g, &reduction);

	printf("\n\n[+]A + B (binary, %d bits) = ", MSB(&reduction) + 1);
	PrintNumHex(reduction);
	printf("\n");

	bignum mul_res = { 0 };
	XTime(&num_A, &num_B, &g, &mul_res);
	printf("\n\n[+]A * B (binary, %d bits) = ", MSB(&mul_res) + 1);
	PrintNumHex(mul_res);


	bignum sqr = { 0 };
	Square(&num_A, &g, &sqr);
	printf("\n\n[+]A^2 (%d bits): ", MSB(&sqr) + 1);
	PrintNumHex(sqr);


	bignum pow_res = { 0 };
	//PowPoly(&num_A, 123, &g, &pow_res);
	PowPolyHorner(&num_A, &num_C, &g, &pow_res);
	printf("\n\n[+]A^C (%d bits)= ", MSB(&pow_res) + 1);
	PrintNumHex(pow_res);

	bignum p = { 0 };
	Copy(&g, &p);
	int trace = Trace(&num_A, &g);
	printf("\n\n[+]Trace(%c) : %d", 'A', trace);


	bignum inverse = { 0 };
	Inverse(&num_A, &g, &inverse);
	printf("\n\n[+]INVERSE(%c)  (%d bits) = ", 'A', MSB(&inverse) + 1);
	PrintNumHex(inverse);
}

void PrintFromBin(char* A, char* B, char* C, bignum g)
{
	bignum num_A = StrBinaryToBignum(A);
	bignum num_B = StrBinaryToBignum(B);
	bignum num_C = StrBinaryToBignum(C);

	int bits_A = MSB(&num_A) + 1;
	int bits_B = MSB(&num_B) + 1;
	int bits_C = MSB(&num_C) + 1;


	bignum add_without_reduction_result = { 0 };
	AddPoly(num_A, num_B, &add_without_reduction_result);

	printf("\nA (binary, %d bits) = ", bits_A);
	PrintNumBin(num_A);
	printf("\n\nB (binary, %d bits) = ", bits_B);
	PrintNumBin(num_B);
	printf("\n\nC (binary, %d bits) = ", bits_C);
	PrintNumBin(num_C);
	printf("\n\n ### POLYNOMIAL FORM ### \n");
	printf("g = ");
	bf2p(&g);
	printf("\n\nA = ");
	bf2p(&num_A);
	printf("\n\nB = ");
	bf2p(&num_B);
	printf("\n\nC = ");
	bf2p(&num_C);

	bignum reduction = { 0 };
	Reduct(&add_without_reduction_result, &g, &reduction);

	printf("\n\n[+]A + B (binary, %d bits) = ", MSB(&reduction) + 1);
	PrintNumBin(reduction);
	printf("\n");

	bignum mul_res = { 0 };
	XTime(&num_A, &num_B, &g, &mul_res);
	printf("\n\n[+]A * B (binary, %d bits) = ", MSB(&mul_res) + 1);
	PrintNumBin(mul_res);


	bignum sqr = { 0 };
	Square(&num_A, &g, &sqr);
	printf("\n\n[+]A^2 (%d bits): ", MSB(&sqr) + 1);
	PrintNumBin(sqr);


	bignum pow_res = { 0 };
	//PowPoly(&num_A, 123, &g, &pow_res);
	PowPolyHorner(&num_A, &num_C, &g, &pow_res);
	printf("\n\n[+]A^C (%d bits)= ", MSB(&pow_res) + 1);
	PrintNumBin(pow_res);

	bignum p = { 0 };
	Copy(&g, &p);
	int trace = Trace(&num_A, &g);
	printf("\n\n[+]Trace(%c) : %d", 'A', trace);


	bignum inverse = { 0 };
	Inverse(&num_A, &g, &inverse);
	printf("\n\n[+]INVERSE(%c)  (%d bits) = ", 'A', MSB(&inverse) + 1);
	PrintNumBin(inverse);
}




// ### LAB 4 ###

void N_AddPoly(bignum a, bignum b, bignum* result)
{
	AddPoly(a, b, result);
}

bignum N_ConstOne(int m)
{
	bignum temp = { 0 };
	BignumReserve(&temp, m / 32);
	temp.iNumOfLimbs = m / 32;

	for (int i = 0; i < m; i++)
	{
		SetBit(&temp, i, 1);
	}

	return temp;
}
	


void CircularShiftRight(
    const bignum* src,
    unsigned int shift_bits,
	int  m,
    bignum* dest)
{
	BignumReserve(dest, src->iNumOfLimbs);
	memset(dest->uLimbs, 0, dest->uCapacity * sizeof(uint32_t));
    dest->iNumOfLimbs = src->iNumOfLimbs;

	for (int i = 0; i < m; i++)
	{
		int bit = GetBit(src, (i + shift_bits) % m);
		SetBit(dest, i, bit);
	}

}

void N_Square(
	const bignum* src,
	int  m,
	bignum* dest)
{
	CircularShiftRight(src, 1, m, dest);
}


int N_Trace(bignum* a)
{
	int m = MSB(a);
	int res = 0;

	for (int i = 0; i < m; i++)
	{
		res += GetBit(a, i);
	}

	return res;
}





int** N_allocate_matrix(int m)
{

	int** board = (int**)malloc(m * sizeof(int*));
	int row;

	for (row = 0; row < m; row++) {
		board[row] = (int*)malloc(m * sizeof(int));
	}

	return board;
}


int** N_InitMatrix(int m)
{
	int** matrix = N_allocate_matrix(m);
	int p = 2 * m + 1; // 479

	int* pow2 = (int*)malloc(m * sizeof(int));
	pow2[0] = 1;
	for (int k = 1; k < m; k++) {
		pow2[k] = (pow2[k - 1] * 2) % p;
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			int sum = (pow2[i] + pow2[j]) % p;
			int diff1 = (pow2[i] - pow2[j] + p) % p;
			int diff2 = (pow2[j] - pow2[i] + p) % p;

			if (sum == 1  || sum == p - 1 ||  diff1 == 1 || diff2 == 1) {
				matrix[i][j] = 1;
			}
			else {
				matrix[i][j] = 0;
			}
		}
	}

	free(pow2);
	return matrix;
}

void N_Mul(bignum* u, bignum* v, int m, bignum* result)
{
	unsigned int limbs = (m + 31) / 32;
	BignumReserve(result, limbs);
	memset(result->uLimbs, 0, result->uCapacity * sizeof(uint32_t));
	result->iNumOfLimbs = limbs;

	int** matrix = N_InitMatrix(m);
	int* temp_vec = (int*)malloc(m * sizeof(int));

	for (int k = 0; k < m; k++)
	{
		int shift = (m - k) % m;
		bignum u_shift = { 0 };
		bignum v_shift = { 0 };
		CircularShiftRight(u, shift, m, &u_shift);
		CircularShiftRight(v, shift, m, &v_shift);

		for (int j = 0; j < m; j++)
		{
			int sum = 0;
			for (int i = 0; i < m; i++)
			{
				if (matrix[i][j] && GetBit(&u_shift, m - 1 - i))
				{
					sum ^= 1;
				}
			}
			temp_vec[j] = sum;
		}

		int res_bit = 0;
		for (int j = 0; j < m; j++)
		{
			if (temp_vec[j] && GetBit(&v_shift, m - 1 - j))
			{
				res_bit ^= 1;
			}
		}

		SetBit(result, m - 1 - k, res_bit);

		free(u_shift.uLimbs);
		free(v_shift.uLimbs);
	}

	free(temp_vec);
	for (int i = 0; i < m; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

void N_Inverse(bignum *a, int m, bignum *result)
{
	bignum temp = StrToBinaryBignum("1");
	bignum two_pow_m = { 0 };
	LongShiftBitsToHigh(&temp, m, &two_pow_m);


	bignum two = StrToBinaryBignum("2");
	sub_result deg = SubBigNums(&two_pow_m, &two);

	N_Pow(a, &deg.diff, m, result);
}


void N_Pow(bignum* a, bignum* b, int m, bignum* result)
{
	bignum tmp = { 0 };
	unsigned int limbs = (m + 31) / 32;
	BignumReserve(&tmp, limbs);
	tmp.iNumOfLimbs = limbs;

	for (int j = 0; j < m; j++) {
		SetBit(&tmp, j, 1);
	}

	int bits_b = MSB(b);
	for (int i = bits_b; i >= 0; i--)
	{
		bignum sqr = { 0 };
		N_Square(&tmp, m, &sqr);
		free(tmp.uLimbs);
		tmp = sqr;

		if (GetBit(b, i) == 1)
		{
			bignum mul = { 0 };
			N_Mul(&tmp, a, m, &mul);
			free(tmp.uLimbs);
			tmp = mul;
		}
	}

	Copy(&tmp, result);
	free(tmp.uLimbs);
}
