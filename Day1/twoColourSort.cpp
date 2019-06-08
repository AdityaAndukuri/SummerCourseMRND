#include "twoColourSort.h"

#include<stdio.h>
#include<stdlib.h>

void method1(int *arr, int length)
{
	int i, j, temp;
	for (i = 0; i < length - 1; i++)
	{
		for (j = 0; j < length - i - 1; j++)
		{
			if (arr[j]>arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void method2(int *arr, int length)
{
	int start = 0, end = length - 1;
	while (start <= end)
	{
		if (arr[start] == 1 && arr[end] == 0)
		{
			arr[start] = 0;
			arr[end] = 1;
		}
		else{
			if (arr[start] == 0)
			{
				start++;
			}
			if (arr[end] == 1)
			{
				end--;
			}
		}
	}
}

void method3(int *arr, int length)
{
	int sum = 0;
	int index;
	for (index = 0; index < length; index++)
	{
		if (arr[index])
			sum++;
	}
	int no_zero = length - sum;
	for (index = 0; index < no_zero; index++)
	{
		arr[index] = 0;
	}
	for (; index < length; index++)
	{
		arr[index] = 1;
	}
}

void print_array(int *arr, int length)
{
	int index;
	for (index = 0; index < length; index++)
	{
		printf("%d ", arr[index]);
	}
	printf("\n");
}

void coloursort()
{
	int length;
	printf("enter length of the array\n");
	scanf_s("%d", &length);
	int *arr = (int*)calloc(length, sizeof(int));
	printf("enter elements of array\n");
	int ind;
	for (ind = 0; ind < length; ind++)
		scanf_s("%d", &arr[ind]);
	method1(arr, length);
	printf("sorted array by method1\n");
	print_array(arr, length);
	printf("enter elements of array\n");
	for (ind = 0; ind < length; ind++)
		scanf_s("%d", &arr[ind]);
	method2(arr, length);
	printf("sorted array by method2\n");
	print_array(arr, length);
	printf("enter elements of array\n");
	for (ind = 0; ind < length; ind++)
		scanf_s("%d", &arr[ind]);
	method3(arr, length);
	printf("sorted array by method3\n");
	print_array(arr, length);
}
