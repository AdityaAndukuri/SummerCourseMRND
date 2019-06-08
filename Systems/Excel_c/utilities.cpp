#include "utilities.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unordered_map>
using namespace std;



cell **createMat(int row, int col)
{
	cell **mat = (cell **)calloc(row, sizeof(cell*));
	int i;
	for (i = 0; i < row; i++)
	{
		mat[i] = (cell*)calloc(col, sizeof(cell));
	}
	return mat;
}

/*unordered_map<string,int> commands_list()
{
	unordered_map<string, int> umap;
	umap["get"] = 1;
	umap["set"] = 2;
	umap["print"] = 3;
	umap["export"] = 4;
	umap["import"] = 5;
	umap["exit"] = 6;
	return umap;

}*/

void convertfname(char *fname)
{
	char *ext = ".csv";
	if (strlen(fname) < 4)
	{
		strcat(fname, ext);
	}
	else{
		char *temp = fname + (strlen(fname) - strlen(ext));
		if (strcmp(temp, ext) != 0)
		{
			strcat(fname, ext);
		}
	}
}


int precedence(char ope)
{
	switch (ope)
	{
	case '*':
		return 2;
	case '/':
		return 2;
	case '+':
		return 1;
	case '-':
		return 1;
	default:
		return -1;
	}
}

void push(char *stack, int *top, char ope)
{
	*top = *top + 1;
	stack[*top] = ope;
	
}

char pop(char *stack, int *top)
{
	if (*top < 0)
		return NULL;
	char c = stack[*top];
	*top = *top - 1;
	return c;
}

void push_post(char **stack, int *top, char *ope)
{
	*top = *top + 1;
	stack[*top] = (char*)calloc(20, sizeof(char));
	
	strcpy(stack[*top], ope);
	//printf("\nhello world %s\n", stack[*top]);

}

char *pop_post(char **stack, int *top)
{
	if (*top < 0)
		return NULL;
	char* ch = (char*)calloc(20, sizeof(char));
	strcpy(ch, stack[*top]);
	*top = *top - 1;
	return ch;
}

