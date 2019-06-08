#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void find_occur(char **grid, int dir, int row_id, int col_id, int row, int col, char *str, int length, int *ans)
{
	//printf("%c %d\n", grid[row_id][col_id],length);
	if (row_id < 0 || row_id >= row || col_id < 0 || col_id >= col || str[length]=='\0')
	{
		//printf("%c fail\n", grid[row_id][col_id]);
		return;
	}
	if (strlen(str)==length+1&&str[length]==grid[row_id][col_id])
	{
		//printf("%c hello\n", grid[row_id][col_id]);
		*ans=1;
		printf("\nsuccess\n");
		printf("\nend %d %d\n", row_id, col_id);
	}
	char temp = grid[row_id][col_id];
	if (*ans == 0)
	{
		if (str[length] == grid[row_id][col_id] && dir == 1)
		{
			find_occur(grid, dir, row_id, col_id + 1, row, col, str, length + 1, ans);
		}
		if (str[length] == grid[row_id][col_id] && dir == 2)
		{
			find_occur(grid, dir, row_id + 1, col_id, row, col, str, length + 1, ans);
		}
		if (str[length] == grid[row_id][col_id] && dir == 3)
		{
			find_occur(grid, dir, row_id, col_id - 1, row, col, str, length + 1, ans);
		}
		if (str[length] == grid[row_id][col_id] && dir == 4)
		{
			find_occur(grid, dir, row_id - 1, col_id, row, col, str, length + 1, ans);
		}
		if (str[length] == grid[row_id][col_id] && dir == 5)
		{
			find_occur(grid, dir, row_id + 1, col_id + 1, row, col, str, length + 1, ans);
		}
		if (str[length] == grid[row_id][col_id] && dir == 6)
		{
			find_occur(grid, dir, row_id - 1, col_id - 1, row, col, str, length + 1, ans);
		}
		if (str[length] == grid[row_id][col_id] && dir == 7)
		{
			find_occur(grid, dir, row_id - 1, col_id + 1, row, col, str, length + 1, ans);
		}
		if (str[length] == grid[row_id][col_id] && dir == 8)
		{
			find_occur(grid, dir, row_id + 1, col_id - 1, row, col, str, length + 1, ans);
		}
	}
}

static void pattern()
{
	//char *grid[5] = { "abcdef","ghimij","kielmn","opqlls","xyzmoo" };
	char *grid[] = { "hihih", "eehee" };
	int dir = 1;
	int i, j;
	int count = 0;
	char *search = "hi";
		for (i = 0; i < 2; i++)
		{
			for (j = 0; j < 5; j++)
			{
				if (grid[i][j] == search[0])
				{
					dir = 1;
					while (dir < 9)
					{
						int *ans = (int*)calloc(1, sizeof(int));
						find_occur(grid, dir, i, j, 2, 5, search, 0,ans);
						if (*ans == 1)
						{
							count++;
							printf("start %d %d", i, j);

						}
						dir++;
					}

				}
			}
		}
		if (!count)
	printf("fail\n");
		else{
			printf("\n%d is count\n", count);
		}
}