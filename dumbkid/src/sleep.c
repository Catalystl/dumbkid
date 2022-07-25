#include <time.h>

void islp(int i)
{
	struct timespec ts = {i, 0};
	nanosleep(&ts, NULL);
}

void fslp(void)
{
	struct timespec ts = {0, 33333333L};
	nanosleep(&ts, NULL);
}
