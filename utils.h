#ifndef _UTILS_H
#define _UTILS_H
#include <stdio.h>
#include <stdint.h>

uint8_t countBits(uint64_t bytebuffer);

#ifndef DEBUG
#define ASSERT(n)
#define DEBUGprintf(msg, ...)
#else
#define ASSERT(n) \
	if(!(n)) { \
		printf("ASSERT(%s) - Failed\n", #n); \
		printf("\tOn %s ", __DATE__); \
		printf("at %s\n", __TIME__); \
		printf("\tIn file %s", __FILE__); \
		printf(":%d\n", __LINE__); \
		exit(1);}
#define DEBUGprintf(msg, ...) printf(msg, ##__VA_ARGS__)
#endif /* ifndef DEBUG */

#endif
