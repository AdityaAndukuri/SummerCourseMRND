#include "StringCompress.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void stringcompress()
{
	char *str = (char*)calloc(100, sizeof(char));
	printf("enter the string\n");
	scanf("%s", str);
	int count = 1;
	int start = 0, ind;
	for (ind = 0; ind < strlen(str); ind++)
	{
		if (ind<strlen(str) && str[ind] == str[ind + 1])
		{
			count++;
		}
		else{
			str[start++] = str[ind];
			if (count > 1)
			{
				str[start++] = '0' + count;
			}
			count = 1;
		}
	}
	str[start] = '\0';
	printf("result is %s\n", str);
}