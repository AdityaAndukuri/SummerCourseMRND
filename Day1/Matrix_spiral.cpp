#include<stdio.h>
#include<stdlib.h>

static void display(int **mat, int *spiral,int m, int n,int count)
{
	int i;
	for (i = m; i <= n; i++)
	{
		spiral[count++] = mat[m][i];
	}
	for (i = m; i <= n; i++)
	{
		spiral[count++] = mat[i][n];
	}
	for (i = n; i >=m; i--)
	{
		spiral[count++] = mat[n][i];
	}
	for (i = n; i >= m; i--)
	{
		spiral[count++] = mat[i][m];
	}
	display(mat, spiral, m + 1, n - 1, count);
}
/*int main()
{
	int m, n;
	printf("enter m,n\n");
	scanf("%d %d", &m, &n);
	int **mat = (int **)calloc(m, sizeof(int*));
	int i, j;
	for (i = 0; i < m; i++)
		mat[i] = (int*)calloc(n, sizeof(int));
	printf("enter elements\n");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			scanf("%d", &mat[i][j]);
	}
	int *spiral = (int *)calloc(m*n, sizeof(int));
	int top = 0, bottom = m - 1, right = n - 1, left = 0;
	int total = m*n;
	int count = 0;
	/*while (count < total)
	{
		for (i = left; i <= right; i++)
		{
			spiral[count++] = mat[top][i];
		}
		top++;
		for (i = top; i <= bottom; i++)
		{
			spiral[count++] = mat[i][right];
		}
		right--;
		for (i = right; i >= left; i--)
		{
			spiral[count++] = mat[bottom][i];
		}
		bottom--;
		for (i = bottom; i >= top; i--)
		{
			spiral[count++] = mat[i][left];
		}
		left++;
	}
	display(mat, spiral, 0, n - 1,count);
	for (i = 0; i < total; i++)
		printf("%d ", spiral[i]);
	return 0;
}*/