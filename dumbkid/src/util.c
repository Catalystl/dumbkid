#include <time.h>

#include "util.h"

// Sleep for i seconds
void islp(int i)
{
	struct timespec ts = {i, 0};
	nanosleep(&ts, NULL);
}

// Sleep for 1/30 of a second
void fslp(void)
{
	struct timespec ts = {0, 33333333L};
	nanosleep(&ts, NULL);
}
