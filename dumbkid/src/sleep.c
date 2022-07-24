#include <time.h>

void islp(int i)
{
	struct timespec ts = {i, 0};
	nanosleep(&ts, NULL);
}
