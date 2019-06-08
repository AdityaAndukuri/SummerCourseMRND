#include <stdio.h>
#include <stdlib.h>

static int fpower(int a, int n)
{   
	if (n == 1)
		return a;
	if (n == 0)
		return 1;
	//return fpower(a, n / 2) % (1000000007)*fpower(a, n / 2) % (1000000007)*fpower(a, n % 2) % (1000000007);
	int res = fpower(a, n / 2) % (1000000007);
	return res % (1000000007)*res % (1000000007)*fpower(a, n % 2);
}

static void find()
{
	printf("%d", fpower(2, 12));
	//printf("hello");
}