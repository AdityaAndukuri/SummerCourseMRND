#include<stdio.h>
#include<stdlib.h>

/*int main()
{
	int m, n;
	printf("enter m,n\n");
	scanf("%d %d", &m, &n);
	int **mat = (int **)calloc(m, sizeof(int*));
	int i, j;
	for (i = 0; i < n; i++)
		mat[i] = (int*)calloc(n, sizeof(int));
	printf("enter elements\n");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			scanf("%d", &mat[i][j]);
	}
	int **mat2 = (int **)calloc(n, sizeof(int*));
	for (i = 0; i < n; i++)
		mat2[i] = (int*)calloc(m, sizeof(int));
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			mat2[i][j] = mat[j][i];
	}
	printf("transpose is\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			printf("%d ",mat2[i][j]);
		printf("\n");
	}

	return 0;
}
*/