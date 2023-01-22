#include "utils.h"

uint8_t countBits(uint64_t bytebuffer)
{
#ifdef __GNUC__
	return __builtin_popcountll(bytebuffer);
#else
	uint8_t t = 0;
	while(bytebuffer)
	{
		t += bb & 1;
		bytebuffer >>= 1;
	}
	return t;
#endif
}
