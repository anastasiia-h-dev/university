#include "resource.h"

bignum GenerateRandomBignum()
{

	bignum result;
	result.iNumOfLimbs = 8;
	result.uCapacity = 8;
	result.uLimbs = (uint32_t*)calloc(result.uCapacity, sizeof(uint32_t));


	for (unsigned int i = 0; i < result.iNumOfLimbs; i++)
	{
		if (i == 0)
		{
			result.uLimbs[0] = (uint32_t)(((uint16_t)rand() << 17) + ((uint16_t)rand() << 2) + ((uint16_t)rand() >> 13));
		}
		//result.uLimbs[i] = result.uLimbs[i - 1] ^ (uint32_t)(i);
		result.uLimbs[i] = (uint32_t)(((uint16_t)rand() << 17) + ((uint16_t)rand() << 2) + ((uint16_t)rand() >> 13));


	}

	return result;
}

bignum GenerateRandomSmallBignum()
{
	bignum result;
	result.iNumOfLimbs = 1;
	result.uCapacity = 1;
	result.uLimbs = (uint32_t*)calloc(result.uCapacity, sizeof(uint32_t));

	result.uLimbs[0] = (uint32_t)(((uint16_t)rand() << 16) + ((uint16_t)rand() << 2) + ((uint16_t)rand() >> 13));
	result.uLimbs[0] = result.uLimbs[0] % (uint32_t)(128);

	return result;
}


bignum GenerateRandomNormalBignum(int m)
{
	unsigned int limbs = (m + 31) / 32; // для m = 239 це 8 лімбів
	bignum result = { 0 };
	result.iNumOfLimbs = limbs;
	result.uCapacity = limbs;
	result.uLimbs = (uint32_t*)calloc(result.uCapacity, sizeof(uint32_t));

	for (unsigned int i = 0; i < limbs; i++)
	{
		result.uLimbs[i] = ((uint32_t)(rand() & 0xFFFF) << 16) | (uint32_t)(rand() & 0xFFFF);
	}

	unsigned int rem_bits = m % 32;
	if (rem_bits != 0)
	{
		uint32_t mask = ((uint32_t)1 << rem_bits) - 1;
		result.uLimbs[limbs - 1] &= mask;
	}

	while (result.iNumOfLimbs > 1 && result.uLimbs[result.iNumOfLimbs - 1] == 0)
	{
		result.iNumOfLimbs--;
	}

	return result;
}

void TestOperation(int num, int code)
{
	float res;

	int NUM_OF_ITERATIONS = num;

	int rand_int = rand() % 10;
	int rand_bigger_int = rand() % 100;

	unsigned long long start_cpu, end_cpu;

	start_cpu = __rdtsc();
	clock_t start = clock();
	
	for (unsigned int i = 0; i < NUM_OF_ITERATIONS; i++)
	{
		bignum a = GenerateRandomBignum();
		bignum b = GenerateRandomBignum();
		bignum n = GenerateRandomBignum();

		//bignum result = { 0 };
		//sub_result res = { 0 };
		//switch (code)
		//{
		//case 1:
			//result = AddBigNums(&num1, &num2);
			//free(result.uLimbs);
		//	break;
		//case 2 :
				//res = SubBigNums(&num1, &num2);
				//free(res.diff.uLimbs);
		//	break;
		//}

		//bignum result = LongMulOneDigit(&num1, rand_int);
		//free(result.uLimbs);

		//bignum result = LongMul(&num1, &num2);
		//free(result.uLimbs);

		//bignum result = SquareBignum(&num1);
		//free(result.uLimbs);

		//div_result result = LongDivBignum(num1, num2);
		//free(result.q.uLimbs);
		//free(result.r.uLimbs);

		//bignum result = LongPower(&num1, &num3_small);
		//free(result.uLimbs);

		//Compare(num1, num2);


		//LAB2
		//int k = MSB(&n) + 1;
		//bignum one = SmallConstToBignum(1);
		//bignum myu_to_deg = {0};
		//LongShiftBitsToHigh(&one,2 * k, &myu_to_deg); //myu_to_deg = 2^t, t = deg(a)
		//div_result myu = LongDivBignum(myu_to_deg, n);

		//bignum result = { 0 };
		//switch (code) {
		//case 1:
		//	ModPower(&a, &b, &n, &myu.q);
		//	break;
		//case 2:
		//	LongPowerWindow(&a, &b, n, myu.q, &result);
		//	break;
		//}
		//ModAdd(&a, &b, &n, &result, &myu.q);
		//ModSub(&a, &b, &n, &result, &myu.q);
		//ModMul(&a, &b, &n, &result, &myu.q);
		//ModSquare(&a, &n, &result, &myu.q);
		

		
		
	}


	clock_t end = clock();
	end_cpu = __rdtsc();

	double average = (double)(end - start) / NUM_OF_ITERATIONS;
	unsigned long long cycles = end_cpu - start_cpu;
	
	//STATISTICS
	//switch (code) {
	//case 1:
	//	printf("\n\nFunction : AddBigNums()");
	//	break;
	//}
	printf("\n\n[*]STATISTICS:");
	printf("\n[*]Iterations : %d", NUM_OF_ITERATIONS);
	printf("\nProcessor time taken for all iterations : %f", (double)(end - start)/CLOCKS_PER_SEC);
	printf("\nProcessor time taken for one iteration : %.9f", (double)average/CLOCKS_PER_SEC);
	printf("\nCPU cycles for all iterations : %llu", cycles);
	printf("\nCPU cycles for one iterations : %llu", cycles/NUM_OF_ITERATIONS);


}

void TestLab3(int num, bignum* g, int code)
{
	float res;

	int NUM_OF_ITERATIONS = num;

	int rand_int = rand() % 10;
	int rand_bigger_int = rand() % 100;

	unsigned long long start_cpu, end_cpu;

	start_cpu = __rdtsc();
	clock_t start = clock();

	for (unsigned int i = 0; i < NUM_OF_ITERATIONS; i++)
	{
		bignum a = GenerateRandomBignum();
		bignum b = GenerateRandomBignum();
		bignum c = GenerateRandomSmallBignum();

		bignum result = { 0 };
		
		switch (code)
		{
		case 1:
			AddPoly(a, b, &result);
			break;
		case 2:
			XTime(&a, &b, g, &result);
			break;
		case 3:
			Trace(&a, g);
			break;
		case 4:
			Square(&a, g, &result);
			break;
		case 5:
			PowPolyHorner(&a, &c, g, &result);
			break;
		case 6:
			Inverse(&a, g, &result);
			break;
		}
		
		//
		//
		//
		//
		//

	}


	clock_t end = clock();
	end_cpu = __rdtsc();

	double average = (double)(end - start) / NUM_OF_ITERATIONS;
	unsigned long long cycles = end_cpu - start_cpu;


	printf("\n\n[*]STATISTICS:");
	printf("\n[*]Iterations : %d", NUM_OF_ITERATIONS);
	printf("\nProcessor time taken for all iterations : %f", (double)(end - start) / CLOCKS_PER_SEC);
	printf("\nProcessor time taken for one iteration : %.9f", (double)average / CLOCKS_PER_SEC);
	printf("\nCPU cycles for all iterations : %llu", cycles);
	printf("\nCPU cycles for one iterations : %llu", cycles / NUM_OF_ITERATIONS);


}


void Stats_Lab3(bignum *g)
{
	printf("\n\n#### 1) A + B ####");
	TestLab3(100, g, 1);
	TestLab3(1000, g, 1);
	TestLab3(100000, g, 1);

	printf("\n\n#### 2) A * B ####");
	TestLab3(100, g, 2);
	TestLab3(1000, g, 2);
	TestLab3(10000, g, 2);

	printf("\n\n#### 3) Trace(A) ####");
	TestLab3(100, g, 3);
	//TestLab3(1000, g, 3);
	//TestLab3(10000, g, 3);

	printf("\n\n#### 4) A^2 ####");
	TestLab3(100, g, 4);
	//TestLab3(1000, g, 4);
	//TestLab3(10000, g, 4);

	printf("\n\n#### 5) A^C ####");
	TestLab3(100, g, 5);
	//TestLab3(1000, g, 5);
	//TestLab3(10000, g, 5);

	printf("\n\n#### 6) INVERSE(A) ####");
	TestLab3(100, g, 6);
	//TestLab3(1000, g, 6);
	//TestLab3(10000, g, 6);
}


void TestLab4(int num, int m, int code)
{
	float res;

	int NUM_OF_ITERATIONS = num;

	int rand_int = rand() % 10;
	int rand_bigger_int = rand() % 100;

	unsigned long long start_cpu, end_cpu;

	start_cpu = __rdtsc();
	clock_t start = clock();

	for (unsigned int i = 0; i < NUM_OF_ITERATIONS; i++)
	{
		bignum a = GenerateRandomNormalBignum(m);
		bignum b = GenerateRandomNormalBignum(m);
		bignum c = GenerateRandomNormalBignum(m);

		bignum result = { 0 };

		switch (code)
		{
		case 1:
			N_AddPoly(a, b, &result);
			break;
		case 2:
			N_Mul(&a, &b, m, &result);
			break;
		case 3:
			N_Trace(&a);
			break;
		case 4:
			N_Square(&a, m, &result);
			break;
		case 5:
			N_Pow(&a, &b, m, &result);
			break;
		case 6:
			N_Inverse(&a, m, &result);
			break;
		}
	}

	clock_t end = clock();
	end_cpu = __rdtsc();

	double average = (double)(end - start) / NUM_OF_ITERATIONS;
	unsigned long long cycles = end_cpu - start_cpu;


	printf("\n\n[*]STATISTICS:");
	printf("\n[*]Iterations : %d", NUM_OF_ITERATIONS);
	printf("\nProcessor time taken for all iterations : %f", (double)(end - start) / CLOCKS_PER_SEC);
	printf("\nProcessor time taken for one iteration : %.9f", (double)average / CLOCKS_PER_SEC);
	printf("\nCPU cycles for all iterations : %llu", cycles);
	printf("\nCPU cycles for one iterations : %llu", cycles / NUM_OF_ITERATIONS);


}


void Stats_Lab4(int m)
{
	printf("\n\n#### 1) A + B ####");
	TestLab4(100, m, 1);
	//TestLab4(1000, m, 1);
	//TestLab4(10000, m, 1);

	printf("\n\n#### 2) A * B ####");
	TestLab4(100, m, 2);
	//TestLab4(1000, m, 2);
	//TestLab4(10000, m, 2);

	printf("\n\n#### 3) Trace(A) ####");
	TestLab4(100, m, 3);
	//TestLab4(1000, m, 3);
	//TestLab4(10000, m, 3);

	printf("\n\n#### 4) A^2 ####");
	TestLab4(100, m, 4);
	//TestLab4(1000, m, 4);
	//TestLab4(10000, m, 4);

	printf("\n\n#### 5) A^C ####");
	TestLab4(10, m, 5);
	//TestLab4(1000, m, 5);
	//TestLab4(10000, m, 5);

	printf("\n\n#### 6) INVERSE(A) ####");
	TestLab4(10, m, 6);
	//TestLab4(1000, m, 6);
	//TestLab4(10000, m, 6);
}