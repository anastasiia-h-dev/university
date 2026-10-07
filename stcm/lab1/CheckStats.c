#include "BigNumArithmetic.h"


//TODO:
//1. створити генератор рандомних великих чисел
//2. середній час виконання арифметичних операцій
//3. підрахувати кількість тактів процесора на кожну операцію



bignum GenerateRandomBignum()
{

	bignum result;
	result.iNumOfLimbs = 64;
	result.uCapacity = 64;
	result.uLimbs = (uint32_t*)calloc(result.uCapacity, sizeof(uint32_t));

	for (unsigned int i = 0; i < result.iNumOfLimbs; i++)
	{
		result.uLimbs[i] = (uint32_t)(((uint16_t)rand() << 17) + ((uint16_t)rand() << 2) + ((uint16_t)rand() >> 13));

	}

	return result;
}



void TestOperation(int num)
{
	float res;

	int NUM_OF_ITERATIONS = num;
	bignum num1 = GenerateRandomBignum();
	bignum num2 = GenerateRandomBignum();

	int rand_int = rand() % 10;
	int rand_bigger_int = rand() % 100;

	unsigned long long start_cpu, end_cpu;

	start_cpu = __rdtsc();
	clock_t start = clock();
	
	for (unsigned int i = 0; i < NUM_OF_ITERATIONS; i++)
	{
		//bignum result = AddBigNums(&num1, &num2);
		//free(result.uLimbs);

		/*sub_result result = SubBigNums(&num1, &num2);
		free(result.diff.uLimbs);*/

		//bignum result = LongMulOneDigit(&num1, rand_int);
		//free(result.uLimbs);

		//bignum result = LongMul(&num1, &num2);
		//free(result.uLimbs);

		//bignum result = SquareBignum(&num1);
		//free(result.uLimbs);

		//div_result result = LongDivBignum(num1, num2);
		//free(result.q.uLimbs);
		//free(result.r.uLimbs);

		bignum result = LongPower(&num1, &rand_bigger_int);
		free(result.uLimbs);

		//Compare(num1, num2);

		//PrintNumHex(result);
		
	}

	clock_t end = clock();
	end_cpu = __rdtsc();

	double average = (double)(end - start) / NUM_OF_ITERATIONS;
	unsigned long long cycles = end_cpu - start_cpu;
	
	//STATISTICS
	
	printf("\n\n[*]STATISTICS:");
	printf("\n[*]Iterations : %d", NUM_OF_ITERATIONS);
	printf("\nProcessor time taken for all iterations : %f", (double)(end - start)/CLOCKS_PER_SEC);
	printf("\nProcessor time taken for one iteration : %.9f", (double)average/CLOCKS_PER_SEC);
	printf("\nCPU cycles for all iterations : %llu", cycles);
	printf("\nCPU cycles for one iterations : %llu", cycles/NUM_OF_ITERATIONS);


}
