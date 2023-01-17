#include "gettime.h"
#include <sys/timeb.h>

double gettime(void)
{
	struct timeb tb;
	ftime(&tb);
	return (double)tb.time + (double)tb.millitm / 1000.0;
}
