#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


static void printp(int *ques, int *arr, int curr, int limit)
{
	if (curr > limit)
	{
		for (int i = 0; i <= limit; i++)
			printf("%d", arr[i]);
		printf("\n");
	}
	else{
		int search_ind;
		for (int ind = 0; ind <3; ind++)
		{
			for (search_ind = 0; search_ind < ind; search_ind++)
			{
				if (ques[ind] == ques[search_ind])
					break;
			}
			if (search_ind == ind && ques[ind] != -1000)
			{
				arr[curr] = ques[ind];
				int x = ques[ind];
				ques[ind] = -1000;
				printp(ques, arr, curr + 1, 2);
				ques[ind] = x;
			}
		}
	}
}


static void findperm()
{
	int *arr = (int *)calloc(3, sizeof(int));
	int ques[3] = { 3, 9, 5 };
	int ind, curr = 0;
	int search_ind;
	for (ind = 0; ind <3; ind++)
	{
		for (search_ind = 0; search_ind < ind; search_ind++)
		{
			if (ques[ind] == ques[search_ind])
				break;
		}
		if (search_ind == ind && ques[ind] != -1000)
		{
			arr[curr] = ques[ind];
			int x = ques[ind];
			ques[ind] = -1000;
			printp(ques, arr, curr + 1, 2);
			ques[ind] = x;
		}
	}
}
