#include <stdio.h>
#include <stdlib.h>

static long findsum(int *arr, int index)
{
//	index >= 0 ? (return arr[index] + findsum(arr, index - 1)) : (return 0)
		if (index >= 0)
		{
			//printf("%d\n", arr[index]);
			return arr[index] + findsum(arr, index - 1);
			//return 0;
		}
		else{
			return 0;
		}
}

static void calsum()
{
	int arr[6] = { 1, 2, 3, 4, 5, 6 };
	printf("%ld is sum\n", findsum(arr, 5));
}