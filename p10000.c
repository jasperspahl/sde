#include <stdio.h>
#include <stdbool.h>
#include <memory.h>

#define N 10000
#define SQRT_N 100

int main(void)
{
	bool primes[N+1] = {0};
	size_t i, j;
	size_t pc = 0;
	
	memset(primes, true, sizeof(primes));

	primes[0]= false;
	primes[1]= false;

	for (i = 2; i < SQRT_N; ++i)
	{
		if(primes[i])
		{
			for (j = i*i; j <=N; j+=i)
			{
				primes[j]=false;
			}
		}
	}

	for (i = 0; i <= N; ++i)
	{
		if (primes[i])
			pc++;
	}
	printf("Found %zu primes in 0..%d\n", pc, N);

}
