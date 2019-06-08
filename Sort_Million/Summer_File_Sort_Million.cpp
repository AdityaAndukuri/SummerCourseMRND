// Summer_File_Sort_Million.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include<string.h>

#define LENGTH 1000000
#define LIMIT 32768
#define _CRT_SECURE_NO_WARNINGS

int cmp(const void * a, const void * b) {
	return (*(int*)a - *(int*)b);
}

void sortwords(FILE *inp_file, FILE *out_file)
{
	int *arr = (int *)calloc(LIMIT, sizeof(int));
	int *arr2 = (int *)calloc(LIMIT, sizeof(int));
	FILE **tmp = (FILE**)calloc(LENGTH / LIMIT + 2, sizeof(FILE*));
	for (int i = 0; i < LENGTH / LIMIT + 2; i++)
		tmp[i] = (FILE*)malloc(sizeof(FILE));
	int f_ind = 0;
	for (int i = 0; i < LENGTH / LIMIT; i++)
	{
		for (int j = 0; j < LIMIT; j++)
		{
			fscanf(inp_file, "%d", &arr[j]);
		}
		qsort(arr, LIMIT, sizeof(int), cmp);
		char *fname = (char*)calloc(20, sizeof(char));
		char *buff = (char*)calloc(20, sizeof(char));
		strcpy(fname, "file");
		sprintf(buff, "%d.txt", f_ind);
		strcat(fname, buff);
		tmp[f_ind] = fopen(fname, "w+");
		for (int k = 0; k < LIMIT; k++)
		{
			
			fprintf(tmp[f_ind], "%d\n", arr[k]);
		}
		//fclose(tmp[f_ind]);
		rewind(tmp[f_ind]);
		f_ind++;
	}
	int top = f_ind - 1;
	int temp_ind = 0;
	while (top > 0)
	{
		char *fname = (char*)calloc(20, sizeof(char));
		char *buff = (char*)calloc(20, sizeof(char));
		strcpy(fname, "filetemp");
		sprintf(buff, "%d.txt", temp_ind);
		strcat(fname, buff);
		FILE *temp = fopen(fname, "w+");
		int a, b, x=0, y=0;
		fscanf(tmp[top], "%d", &a);
		//printf("\nhello%d\n", a);
		fscanf(tmp[top - 1], "%d", &b);
		//fprintf(temp, "%d\n", b);
		while (!feof(tmp[top]) && !feof(tmp[top-1]) && top>0)
		{
			
			if (a <= b)
			{
				fprintf(temp, "%d\n", a);
				fscanf(tmp[top], "%d", &a);
				
				

			}
			else
			{
				fprintf(temp, "%d\n", b);
				fscanf(tmp[top-1], "%d", &b);
				
				
			}
		}
		if (feof(tmp[top]))
		{
			if (top>0)
				while (!feof(tmp[top - 1]))
				{
					fprintf(temp, "%d\n", b);
					fscanf(tmp[top - 1], "%d", &b);
					
				}
		}
		else{
			if (top>-1)
				while (!feof(tmp[top]))
				{
					fprintf(temp, "%d\n", a);
					fscanf(tmp[top], "%d", &a);
					
				}
		}
		rewind(temp);
		rewind(tmp[top]);
		if (top>0)
		rewind(tmp[top - 1]);
		top--;
		tmp[top] = temp;
		temp_ind++;
		
	}

	rewind(tmp[top]);
	int i = 1;
	while (!feof(tmp[top]))
	{
		int x;
		fscanf(tmp[top], "%d", &x);
		printf("%d\n", x);
		fprintf(out_file, "%d\n", x);
	}
	//fclose(tmp[0]);
	for (int i = 0; i < f_ind; i++)
		fclose(tmp[i]);
	
}
int _tmain(int argc, _TCHAR* argv[])
{
	FILE *inp_file = fopen("input_words.txt", "r");
	FILE *out_file = fopen("output_words.txt", "w");
	sortwords(inp_file, out_file);
	fclose(inp_file);
	fclose(out_file);
	getchar();
	return 0;
}

