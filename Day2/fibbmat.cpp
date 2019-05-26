#include <stdio.h>
#include <stdlib.h>


static int **mul(int **res, int **restemp)
{
	int **res2 = (int**)calloc(2, sizeof(int*));
	res2[0] = (int*)calloc(2, sizeof(int));
	res2[1] = (int*)calloc(2, sizeof(int));
	int i, j, k;
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			for (k = 0; k < 2; k++)
			{
				res2[i][j] += res[i][k] * restemp[k][j];
			}
		}
	}
	return res2;
}
static int **matmul(int n)
{
	if (n == 1||n==2)
	{
		int **res = (int**)calloc(2, sizeof(int*));
		res[0] = (int*)calloc(2, sizeof(int));
		res[1] = (int*)calloc(2, sizeof(int));
		res[0][0] = 0;
		res[0][1] = 1;
		res[1][0] = 1;
		res[1][1] = 1;
		if (n == 1)
		{
			
			return res;
		}
		int **res2 = (int**)calloc(2, sizeof(int*));
		res2[0] = (int*)calloc(2, sizeof(int));
		res2[1] = (int*)calloc(2, sizeof(int));
		int i, j, k;
		for (i = 0; i < 2; i++)
		{
			for (j = 0; j < 2; j++)
			{
				for (k = 0; k < 2; k++)
				{
					res2[i][j] += res[i][k] * res[k][j];
				}
			}
		}
		return res2;
	}
	else
	if (n & 1)
	{
		int **ans = matmul(n / 2);
		ans = mul(ans,ans);
		int **res = (int**)calloc(2, sizeof(int*));
		res[0] = (int*)calloc(2, sizeof(int));
		res[1] = (int*)calloc(2, sizeof(int));
		res[0][0] = 0;
		res[0][1] = 1;
		res[1][0] = 1;
		res[1][1] = 1;
		ans = mul(ans, res);
		return ans;
	}
	else{
		int **ans = matmul(n / 2);
		ans = mul(ans, ans);
		return ans;
	}
}

static void findfibbmat()
{
	for (int n = 1; n < 10; n++)
	{
		int **ans = matmul(n);
		int **res = (int**)calloc(2, sizeof(int*));
		res[0] = (int*)calloc(1, sizeof(int));
		res[1] = (int*)calloc(1, sizeof(int));
		res[0][0] = 0;
		res[1][0] = 1;
		int **res2 = (int**)calloc(2, sizeof(int*));
		res2[0] = (int*)calloc(1, sizeof(int));
		res2[1] = (int*)calloc(1, sizeof(int));
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				for (int k = 0; k < 2; k++)
					res2[i][j] += ans[i][k] * res[k][j];
			}
		}
		printf("%d\n", res2[1][0]);
	}
	

}