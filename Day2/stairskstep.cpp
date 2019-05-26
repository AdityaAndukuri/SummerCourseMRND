#include <stdio.h>
#include <stdlib.h>

static int findways(int remain, int k)
{
	/*int res;
	printf("%d %d\n",remain,k);
	if (k <= 2)
	{
		return k;
	}
	if (remain >= k)
	{
		res = 1 + findways(remain - k, k - 1) + findways(remain, k - 1);
	}
	else{
		findways(remain, k - 1);
	}
	return res;
	*/
	int res = 0;
	if (remain==0||remain == 1)
		return 1;
	for (int i = 1; i <= k; i++)
	{
		if (remain - i < 0)
			break;
		res += findways(remain - i, k);
	}
	return res;
}

static void findway()
{
	printf("%d is ans\n", findways(5, 3));
}