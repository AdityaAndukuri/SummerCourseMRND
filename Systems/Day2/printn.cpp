#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <unordered_map>
using namespace std;

/*static void print(int n)
{
	if (n > 0)
		print(n - 1);
	else{
		printf("%d\n", n);
		return;
	}
}
static void findprint(int n)
{
	n = (int)pow(10.0, n);
	print(n-1);

}*/
/*static void print(char *str, int n)
{
	if (strlen(str) == n)
	{
		printf("%s\n", str);
		return;
	}
	for (int i = 0; i <= 9; i++)
	{   
		char *temp = (char*)calloc(n, sizeof(char));
		strcpy(temp, str);
		char *temp2 = (char*)malloc(2 * sizeof(char));
		temp2[0] = '0' + i;
		temp2[1] = '\0';
		strcat(temp, temp2);
		print(temp,n);
	}
}
static void findprint(int n)
{
	char *str = (char*)calloc(n, sizeof(char));
	int i;
	for (i = 0; i <= 9; i++)
	{
		char *temp = (char*)malloc(2*sizeof(char));
		temp[0] = '0' + i;
		temp[1] = '\0';
		strcat(str, temp);
		//printf("%s\n", str);
		print(temp,n);
	}
}*/

static void print(int *arr, int curr, int limit,unordered_map<int, char> umap)
{
	if (curr >= limit)
	{
		int i;
		for (i = 0; i <= limit; i++)
		{
			if (arr[i])
				break;
		}
		for (; i <= limit;i++)
			printf("%c", umap[arr[i]]);
		printf("\n");
	}
	else{
		for (int i = 0; i <= 9; i++)
		{
			arr[curr] = i;
			print(arr, curr + 1, limit, umap);
		}
	}
}
static void findprint(int n)
{
	int *arr = (int *)calloc(n - 1, sizeof(int));
	n--;
	int i, curr = 0;
	unordered_map<int, char> umap;
	umap[0] = '0';
	umap[1] = '1';
	umap[2] = '2';
	umap[3] = 'E';
	umap[4] = 'h';
	umap[5] = '5';
	umap[6] = '9';
	umap[7] = 'L';
	umap[8] = '8';
	umap[9] = '6';

	for (i = 0; i <= 9; i++)
	{
		arr[curr] = i;
		print(arr, curr + 1, n,umap);
	}
}
