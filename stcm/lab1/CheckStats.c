#include "BigNumArithmetic.h"

bignum GenerateRandomBignum()
{

	bignum result;
	result.iNumOfLimbs = 64;
	result.uCapacity = 64;
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



void TestOperation(int num)
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
		int k = MSB(&n) + 1;
		bignum one = SmallConstToBignum(1);
		bignum myu_to_deg = {0};
		LongShiftBitsToHigh(&one,2 * k, &myu_to_deg); //myu_to_deg = 2^t, t = deg(a)
		div_result myu = LongDivBignum(myu_to_deg, n);

		bignum result = { 0 };
		//ModAdd(&a, &b, &n, &result, &myu.q);
		//ModSub(&a, &b, &n, &result, &myu.q);
		//ModMul(&a, &b, &n, &result, &myu.q);
		//ModSquare(&a, &n, &result, &myu.q);
		ModPower(&a, &b, &n, &result, &myu.q);
		//bignum result = { 0 };
		//LongPowerWindow(&num1, &num3_small, &result);
		
		
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
