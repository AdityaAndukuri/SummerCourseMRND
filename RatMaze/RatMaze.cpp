// RatMaze.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
void print_path(int **mat, int **path, int row, int col, int m, int n,int count,int *min,int flag)
{
	if (row >= m || row < 0 || col >= n || col < 0 || mat[row][col] == 0)
		return;
	path[row][col] = 1;
	if (mat[row][col] == 2)
	{
		printf("\n");
		path[row][col] = 2;
		if (flag == 0)
		{
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < n; j++)
					printf("%d ", path[i][j]);
				printf("\n");
			}

			if (count > *min)
				*min = count;
		}
		else{
			if (count == *min)
			{
				for (int i = 0; i < m; i++)
				{
					for (int j = 0; j < n; j++)
						printf("%d ", path[i][j]);
					printf("\n");
				}
			}
		}
		
	}
	else{
		mat[row][col] = 0;
		print_path(mat, path, row, col + 1, m, n, count + 1, min,flag);
		print_path(mat, path, row, col - 1, m, n, count + 1, min, flag);
		print_path(mat, path, row + 1, col, m, n, count + 1, min, flag);
		print_path(mat, path, row - 1, col, m, n, count + 1, min, flag);
		mat[row][col] = 1;
		
		
	}
	path[row][col] = 0;

}
int _tmain(int argc, _TCHAR* argv[])
{
	int **mat = (int**)calloc(3, sizeof(int*));
	for (int i = 0; i < 3; i++)
		mat[i] = (int*)calloc(4, sizeof(int));
	int **path = (int**)calloc(3, sizeof(int*));
	for (int i = 0; i < 3; i++)
		path[i] = (int*)calloc(4, sizeof(int));
	int min = 1000;
	int count = 0;
	int flag = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			scanf("%d", &mat[i][j]);
		}
	}
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i==0&&j==0)
			{
				path[i][j] = 1;
				print_path(mat, path, i, j + 1, 3, 4, count + 1, &min , flag);
				print_path(mat, path, i, j - 1, 3, 4, count + 1, &min , flag);
				print_path(mat, path, i + 1, j, 3, 4, count + 1, &min , flag);
				print_path(mat, path, i - 1, j, 3, 4, count + 1, &min, flag);
				path[i][j] = 0;
				
			}
		}
	}
	flag = 1;
	printf("min\n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == 0 && j == 0)
			{
				path[i][j] = 1;
				print_path(mat, path, i, j + 1, 3, 4, count + 1, &min);
				print_path(mat, path, i, j - 1, 3, 4, count + 1, &min);
				print_path(mat, path, i + 1, j, 3, 4, count + 1, &min);
				print_path(mat, path, i - 1, j, 3, 4, count + 1, &min);
				path[i][j] = 0;

			}
		}
	}

	getchar();
	getchar();
	return 0;
}

