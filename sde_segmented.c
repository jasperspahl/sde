#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

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
	size_t i, j;
	double t_start, t_stop;
	double init, alg, count;
	uint64_t offset=0, primeCount=0;
	uint64_t * nc = NULL;
	uint64_t * oc = NULL;
	size_t nobSize = 0;
	t_start = gettime();
	initPrimeArray();
	arr[0] ^= (1ULL|1ULL<<1);
	t_stop = gettime();
	init = t_stop - t_start;
	t_start = gettime();
	for (i = 2; i < SQRT_N; ++i) {
		if(arr[i/S] & (1ULL<<(i%S)))
		{
			for (j = i*i; j < SEQ_SIZE; j+=i) {
				arr[j/S] &= ~(1ULL<<(j%S));
			}
			nc = realloc(nc, ++nobSize * sizeof(uint64_t));
			oc = realloc(oc, nobSize * sizeof(uint64_t));
			nc[nobSize-1] = i;
			if (j < SEQ_SIZE) {DEBUGprintf("j = %zu\n", j);}
			ASSERT(j >= SEQ_SIZE);
			oc[nobSize-1] = j;
		}
	}
	t_stop = gettime();
	alg = t_stop - t_start;
	t_start = gettime();
	primeCount += countPrimeArray();
	t_stop = gettime();
	count = t_stop - t_start;

	t_start = gettime();
	for (i = 1; i < N/SEQ_SIZE; ++i)
	{
		if (i % 10 == 0 || i == 1) {DEBUGprintf("%7zu primes in 0..%9zu\n", primeCount, i * SEQ_SIZE);}
		offset += SEQ_SIZE;
		t_stop = gettime();
		alg += t_stop - t_start;
		t_start = gettime();
		initPrimeArray();
		t_stop = gettime();
		init += t_stop - t_start;

		t_start = gettime();
		for(j=0; j < nobSize; ++j)
		{
			uint64_t num = nc[j];
			uint64_t * off = &oc[j];
			int k=*off - offset;
			
			//DEBUGprintf("num=%zu\t",num);
			//DEBUGprintf("k=%d\n",k);
			while(k < SEQ_SIZE)
			{
				arr[k/S] &= ~(1ULL<<(k%S));
				k+=num;
			}
			if (k < SEQ_SIZE) {DEBUGprintf("k = %d\noffset = %zu\n", k, offset);}
			ASSERT(k >= SEQ_SIZE);
			*off = k+offset;
		}
		t_stop = gettime();
		alg += t_stop - t_start;

		t_start = gettime();
		primeCount += countPrimeArray();
		t_stop = gettime();
		count += t_stop - t_start;

		t_start = gettime();
		
	}
	printf("Init  took %.3lfsec\n", init);
	printf("Alg   took %.3lfsec\n", alg);
	printf("Count took %.3lfsec\n", count);
	printf("--------------------\n");
	printf("Total took %.3lfsec\n\n", init + alg + count);
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
