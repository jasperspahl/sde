#include <stdio.h>
#include <stdint.h>

#define N 100000000
#define SQRT_N 10000
#define S 64
#define T uint64_t

#include "gettime.h"

static T primes[N/S] = {0};

uint64_t countBits(T bb);

int main(void)
{
	size_t i, j;
	double t_start, t_init, t_alg, t_count;
	uint64_t primeCount=0;
	t_start = gettime();
	for (i = 0; i < N/S; ++i) {
		primes[i] |= ~0ULL;
	}
	primes[0] ^= (1ULL|(1ULL<<1));
	t_init = gettime();
	for (i = 2; i < SQRT_N; ++i) {
		if(primes[i/S] & (1ULL<<(i%S)))
		{
			for (j = i*i; j<=N; j+=i){
				primes[j/S] &= ~(1ULL<<(j%S));
			}
		}
	}
	t_alg = gettime();
	for (i = 0; i < N/S; ++i)
	{
		primeCount += countBits(primes[i]);
	}

	t_count = gettime();

	printf("Init  took %.3lfsec\n", t_init - t_start);
	printf("Alg   took %.3lfsec\n", t_alg - t_init);
	printf("Count took %.3lfsec\n", t_count - t_alg);
	printf("--------------------\n");
	printf("Total took %.3lfsec\n\n", t_count - t_start);
	printf("Found %zu primes in 0..%d\n", primeCount, N);
	
	return 0;
}

uint64_t countBits(T bb)
{
#ifdef __GNUC__
	return __builtin_popcountll(bb);
#else
#ifdef _MSC_VER
	return _mm_popcnt_u64(bb);
#else
	uint64_t t = 0;
	if(bb)
	{
		for(size_t i = 0; i < S; ++i)
		{
			t += bb & 1;
			bb >>=1;
		}
	}
	return t;
#endif
#endif
}
