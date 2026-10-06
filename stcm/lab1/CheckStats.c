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



void TestOperation()
{
	float res;

	int NUM_OF_ITERATIONS = 1000000;
	bignum num1 = GenerateRandomBignum();
	bignum num2 = GenerateRandomBignum();

	unsigned long long start_cpu, end_cpu;

	start_cpu = __rdtsc();
	clock_t start = clock();
	
	for (unsigned int i = 0; i < NUM_OF_ITERATIONS; i++)
	{
		bignum result = AddBigNums(&num1, &num2);
		//PrintNumHex(result);
		free(result.uLimbs);
	}

	clock_t end = clock();
	end_cpu = __rdtsc();

	double average = (double)(end - start) / NUM_OF_ITERATIONS;
	unsigned long long cycles = end_cpu - start_cpu;
	
	//STATISTICS
	
	printf("\n[*]STATISTICS:");
	printf("\nProcessor time taken for all iterations : %f", (double)(end - start)/CLOCKS_PER_SEC);
	printf("\nProcessor time taken for one iteration : %.9f", (double)average/CLOCKS_PER_SEC);
	printf("\nCPU cycles for all iterations : %llu", cycles);
	printf("\nCPU cycles for one iterations : %llu", cycles/NUM_OF_ITERATIONS);


}
