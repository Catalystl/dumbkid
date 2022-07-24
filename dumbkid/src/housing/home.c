#include <stdio.h>

#define	dprintf(x)	printf(#x " value: %d\n", x)

void joinroomhouse()
{
	printf("hey bruh\n");
}

void addnums(int a, int b)
{
	int sum;

	dprintf(a);
	dprintf(b);
	sum = a + b;
	dprintf(sum);
}
