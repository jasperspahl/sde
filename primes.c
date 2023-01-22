#include <stdio.h>
#include <stdint.h>

#include "utils.h"
#include "gettime.h"

#define N 100000000
#define SQRT_N 10000
#define S 64

static uint64_t primes[N/S] = {0};

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

