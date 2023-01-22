#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#include "utils.h"
#include "gettime.h"

#define N 100000000
#define SQRT_N 10000
#define SEQ_SIZE 10000
#define S 64

static uint64_t arr[SEQ_SIZE/S] = {0};

uint64_t countPrimeArray();
void initPrimeArray();

int main(void)
{
	size_t i, j, k;
	double t_start, t_init, t_alg;
	uint64_t offset=0, primeCount=0;
	uint64_t * nc = NULL;
	uint64_t * oc = NULL;
	size_t nobSize = 0;
	t_start = gettime();
	initPrimeArray();
	arr[0] ^= (1ULL|1ULL<<1);
	t_init = gettime();
	for (i = 2; i < SQRT_N; ++i) {
		if(arr[i/S] & (1ULL<<(i%S)))
		{
			for (j = i*i; j < SEQ_SIZE; j+=i) {
				arr[j/S] &= ~(1ULL<<(j%S));
			}
			nc = realloc(nc, ++nobSize * sizeof(uint64_t));
			oc = realloc(oc, nobSize * sizeof(uint64_t));
			nc[nobSize-1] = i;
			oc[nobSize-1] = i - (SEQ_SIZE%i) + SEQ_SIZE;
		}
	}
	for (i = 1; i < N/SEQ_SIZE; ++i)
	{
		primeCount += countPrimeArray();
		offset += SEQ_SIZE;
		initPrimeArray();
		for(j=0; j < nobSize; ++j)
		{
			uint64_t num = nc[j];
			uint64_t * off = &oc[j];
			
			for(k = *off - offset;
					k <= SEQ_SIZE;
					k += num)
			{
				arr[k/S] &= ~(1ULL<<(k%S));
			}
			*off = k+offset;
		}
		
	}
	primeCount += countPrimeArray();
	t_alg = gettime();
	printf("Init        took %.3lfsec\n", t_init - t_start);
	printf("Alg + Count took %.3lfsec\n", t_alg - t_init);
	printf("--------------------\n");
	printf("Total took %.3lfsec\n\n", t_alg - t_start);
	printf("Found %zu primes in 0..%d\n", primeCount, N);
	return 0;
}

uint64_t countPrimeArray()
{
	uint64_t pc = 0;
	for (size_t i = 0; i < SEQ_SIZE/S; ++i)
	{
		pc +=countBits(arr[i]);
	}
	return pc;
}

void initPrimeArray()
{
	for (size_t i = 0; i < SEQ_SIZE/S; ++i) {
		arr[i] = ~0ULL;
	}
}
