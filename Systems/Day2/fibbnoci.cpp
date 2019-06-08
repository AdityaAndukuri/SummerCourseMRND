#include <stdio.h>
#include <stdlib.h>

static long find_fib(long *arr,long n)
{
	/*if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return find_fib(n - 1) + find_fib(n - 2);*/
	int i;
	for (i = 2; i < n; i++)
	{
		arr[i] = arr[i - 1] + arr[i - 2];
	}
	return arr[n-1];

}

static void fibb()
{
	long *arr = (long *)calloc(6, sizeof(long));
	arr[1] = 1;
	printf("%ld\n", find_fib(arr,5));

}