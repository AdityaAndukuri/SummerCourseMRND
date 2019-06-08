#include "operations.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

bool isope(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%'||ch=='('||ch==')')
		return true;
	else
		return false;
}




void infixtopostfix(char *infix, post* post_exp)
{
	post_exp->postfix = (char**)calloc(30, sizeof(char*));
	for (int i = 0; i < 30; i++)
		post_exp->postfix[i] = (char*)calloc(30, sizeof(char));
	char *stack = (char*)calloc(20, sizeof(char));
	char *operand = (char*)calloc(5, sizeof(char));
	int ind = 0;
	int operand_ind = 0;
	int dind = 0;
	int top = -1;
	
	//printf("\n%s\t\n", infix);
	while (infix[ind] != '\0')
	{

		if (isope(infix[ind]))
		{
			//printf("\n%d is top %c is char\n", top,infix[ind]);
			if (operand_ind)
			{
				operand[operand_ind] = '\0';
				//postfix[dind] = (char*)calloc(5, sizeof(char));
				strcpy(post_exp->postfix[dind++], operand);
				operand_ind = 0;
			}
			if (infix[ind] == '(')
			{
				push(stack, &top, infix[ind]);
			}
			else{
				if (infix[ind] == ')')
				{
					while (top > -1 && stack[top] != '(')
					{
						//postfix[dind] = (char*)calloc(5, sizeof(char));
						char *ope = (char*)calloc(2, sizeof(char));
						ope[0] = pop(stack, &top);
						ope[1] = '\0';
						strcpy(post_exp->postfix[dind++], ope);
						//printf("\n%d is dind %s is ope\n", dind, ope);
					}
					pop(stack, &top);
				}
				else{
					while (top > -1 && precedence(infix[ind]) <= precedence(stack[top]))
					{
						//postfix[dind] = (char*)calloc(5, sizeof(char));
						char *ope = (char*)calloc(2, sizeof(char));
						ope[0] = pop(stack, &top);
						ope[1] = '\0';
						strcpy(post_exp->postfix[dind++], ope);
						
					}
					push(stack, &top, infix[ind]);
				}
			}
		}
		else{
			operand[operand_ind++] = infix[ind];
			//printf("\n%c is ope\n", infix[ind]);
		}
		ind++;

	}
	if (operand_ind){
		operand[operand_ind] = '\0';
		//postfix[dind] = (char*)calloc(5, sizeof(char));
		strcpy(post_exp->postfix[dind++], operand);
		operand_ind = 0;
	}
	while (top > -1)
	{
		//postfix[dind] = (char*)calloc(5, sizeof(char));
		char *ope = (char*)calloc(2, sizeof(char));
		ope[0] = pop(stack, &top);
		ope[1] = '\0';
		strcpy(post_exp->postfix[dind++], ope);
	}
	//for (int i = 0; i < dind; i++)
		//printf("%s", post_exp->postfix[i]);
	post_exp->length = dind;
	//printf("%d is lenght\n", dind);
	//return post_exp;
}
int postfix_evaluate(post *postfix_exp, cell** mat)
{
	
	if (postfix_exp == NULL)
		return 0;
	char **stack = (char**)calloc(20, sizeof(char));
	for (int i = 0; i < 20; i++)
	{
		stack[i] = (char*)calloc(20, sizeof(char));
	}
	int ind;
	int top = -1;
	for (ind = 0; ind < postfix_exp->length; ind++)
	{
		if (!isope(postfix_exp->postfix[ind][0]))
		{
			push_post(stack, &top, postfix_exp->postfix[ind]);
			//printf("\n%s pushed\n", postfix_exp->postfix[ind]);
		}
		else{
			char* ope1 = (char*)calloc(10, sizeof(char));
			char* ope2 = (char*)calloc(10, sizeof(char));
			int leftdigitflag = 1, rightdigitflag = 1;
			strcpy(ope2, pop_post(stack, &top));
			strcpy(ope1, pop_post(stack, &top));
			//printf("\n%s %s\n", ope1, ope2);
			int i;
			for (i = 0; i < strlen(ope1); i++)
			{
				if (isalpha(ope1[i]))
				{
					leftdigitflag = 0;
					break;
				}
			}
			for (i = 0; i < strlen(ope2); i++)
			{
				if (isalpha(ope2[i]))
				{
					rightdigitflag = 0;
					break;
				}
			}
			int left, right;
			if (leftdigitflag == 0)
			{
				if (ope1[0] >= 'a' && ope1[0] <= 'z')
					ope1[0] -= 32;
			    left = postfix_evaluate(mat[ope1[1] - '1'][ope1[0] - 'A'].postfix_form,mat);
			}
			else
				left = atoi(ope1);
			if (rightdigitflag == 0)
			{
				if (ope2[0] >= 'a' && ope2[0] <= 'z')
					ope2[0] -= 32;
				right = postfix_evaluate(mat[ope2[1] - '1'][ope2[0] - 'A'].postfix_form, mat);
			}
			else
				right = atoi(ope2);
			//printf("\n%d %d is left right\n", left, right);
			int result;
			char ope = postfix_exp->postfix[ind][0];
					switch (ope)
					{
					case '*':
						result=left*right;
						break;
					case '/':
						result = left / right;
						break;
					case '+':
						result = left + right;
						break;
					case '-':
						result = left - right;
						break;
					}
					char *res = (char*)calloc(10, sizeof(char));
					_itoa(result, res, 10);
					push_post(stack, &top, res);

			}
		}
	return atoi(pop_post(stack, &top));
}

int cycle_exists(int row, int col, cell** mat, char *formula)
{
	
	if (!formula)
	{
		mat[row][col].isvisited = 0;
		return 0;
	}
	if (mat[row][col].isvisited)
	{
		mat[row][col].isvisited = 0;
		return 1;
	}
	mat[row][col].isvisited = 1;
	char *operand = (char*)calloc(5, sizeof(char));
	int operand_ind = 0;
	int res = 0;
	for (int i = 0; formula[i] != '\0'; i++)
	{
		
		if (isope(formula[i]))
		{
			if (operand_ind)
			{
				operand[operand_ind] = '\0';
				int j;
				
				for (j = 0; operand[j] != '\0'; j++)
					if (isalpha(operand[j]))
						break;
				if (j != strlen(operand))
				{
					
					//postfix[dind] = (char*)calloc(5, sizeof(char));
					if (operand[0] >= 'a' && operand[0] <= 'z')
						operand[0] -= 32;
					int row_2 = operand[1] - '1';
					int col_2 = operand[0] - 'A';
					res = cycle_exists(row_2, col_2, mat, mat[row_2][col_2].formula);
					if (res)
					{
						operand_ind = 0;
						break;
					}
				}
				operand_ind = 0;
			}
		}
		else{
			operand[operand_ind++] = formula[i];
		}
	}
	if (operand_ind)
	{
		operand[operand_ind] = '\0';
		int j;

		for (j = 0; operand[j] != '\0'; j++)
			if (isalpha(operand[j]))
				break;
		if (j != strlen(operand))
		{
			
			//postfix[dind] = (char*)calloc(5, sizeof(char));
			if (operand[0] >= 'a' && operand[0] <= 'z')
				operand[0] -= 32;
			int row_2 = operand[1] - '1';
			int col_2 = operand[0] - 'A';
			res = cycle_exists(row_2, col_2, mat, mat[row_2][col_2].formula);
			if (res)
			{
				mat[row][col].isvisited = 0;
				return 1;
			}
		}
		operand_ind = 0;
	}
	mat[row][col].isvisited = 0;
	return res;
}
void set(char *row_col, cell **mat, char* operators)
{
	if (row_col[0] >= 'a' && row_col[0] <= 'z')
		row_col[0] -= 32;
	int row = row_col[1] - '1';
	int col = row_col[0] - 'A';
	row_col += 3;
	char *prev = (char*)calloc(20, sizeof(char));
	if (mat[row][col].formula)
	{
		strcpy(prev, mat[row][col].formula);
	}
	mat[row][col].formula = (char*)calloc(20, sizeof(char));
	mat[row][col].isvisited = 0;
	
	strcpy(mat[row][col].formula, row_col);
	if (!cycle_exists(row, col, mat, row_col))
	{
		
		mat[row][col].postfix_form = (post*)malloc(sizeof(post));
		infixtopostfix(mat[row][col].formula, mat[row][col].postfix_form);
		
	}
	else{
		if (prev)
			strcpy(mat[row][col].formula, prev);
		else
			mat[row][col].formula = NULL;
		printf("cycle exists so set not possible\n");

	}
	//printf("\n%s is string\n", mat[row][col].postfix_form->postfix[0]);
	//mat[row][col].formula = row_col;
	//printf("%s\n", row_col);

	return;
}
int evaluate(cell **mat, int row, int col)
{
	if (mat[row][col].formula == NULL)
		return 0;
	char *formula = mat[row][col].formula;
	char* ope1 = (char*)calloc(10, sizeof(char));
	char* ope2 = (char*)calloc(10, sizeof(char));
	int ind, ind1 = 0, ind2 = 0, flag = 0, leftdigitflag = 1, rightdigitflag=1;
	char ope;
	if (formula)
	{

		for (ind = 0; formula[ind] != '\0'; ind++)
		{
			if (formula[ind] != '/'&&formula[ind] != '+'&&formula[ind] != '*'&&formula[ind] != '-')
			{
				if (flag == 0)
				{
					ope1[ind1++] = formula[ind];
					if (isalpha(formula[ind]))
					{
						leftdigitflag = 0;
					}
				}
				else{
					ope2[ind2++] = formula[ind];
					if (isalpha(formula[ind]))
					{
						rightdigitflag = 0;
					}
				}

			}
			else{
				if (flag == 0)
				{
					ope = formula[ind];
					flag = 1;
				}
				
			}
		}
		ope1[ind1] = '\0';
		ope2[ind2] = '\0';
		if (flag == 0)
		{

			if (leftdigitflag == 0)
			{
				if (ope1[0] >= 'a' && ope1[0] <= 'z')
					ope1[0] -= 32;
				return evaluate(mat, ope1[1] - '1', ope1[0] - 'A');
			}
			else
				return atoi(ope1);

		}
		else{
			int left, right;
			if (leftdigitflag == 0)
			{
				if (ope1[0] >= 'a' && ope1[0] <= 'z')
					ope1[0] -= 32;
				left = evaluate(mat, ope1[1] - '1', ope1[0] - 'A');
			}
			else
				left = atoi(ope1);
			if (rightdigitflag == 0)
			{
				if (ope2[0] >= 'a' && ope2[0] <= 'z')
					ope2[0] -= 32;
				right = evaluate(mat, ope2[1] - '1', ope2[0] - 'A');
			}
			else
				right = atoi(ope2);
			switch (ope)
			{
			case '*':
				return left*right;
				break;
			case '/':
				return left / right;
				break;
			case '+':
				return left + right;
				break;
			case '-':
				return left - right;
				break;
			}

		}
	}
	else{
		return 0;
	}
}

char* get(char *row_col, cell **mat, char* operators)
{
	if (row_col[0] >= 'a' && row_col[0] <= 'z')
		row_col[0] -= 32;
	int row = row_col[1] - '1';
	int col = row_col[0] - 'A';
	//printf("%d %d\n", row, col);
	//printf("\n%s is string\n", mat[row][col].postfix_form->postfix[0]);
	int res = postfix_evaluate(mat[row][col].postfix_form, mat);
	printf("%d ", res);
	if (mat[row][col].formula)
	for (int i = 0; mat[row][col].formula[i] != '\0';i++)
		if (isalpha(mat[row][col].formula[i]))
			return mat[row][col].formula;
	return "";
}


void print(int row, int col, cell **mat, char* operators)
{
	int i, j;
	for (i = 0; i <= row; i++)
	{
		for (j = 0; j <= col; j++)
		{
			if (i == 0&&j>0)
			{
				printf("%c\t", j + 'A'-1);
			}
			else{
				if (j == 0 && i > 0)
				{
					printf("%d\t", i);
				}
				else{
					if (i > 0 && j > 0)
					{
						//printf("%d\t", evaluate(mat,i-1,j-1));
						//printf("%s\t", mat[i - 1][j-1].formula);
						if (mat[i - 1][j - 1].formula!=NULL && mat[i-1][j-1].isvisited==0)
						{
							//printf("\n%s is string\n", mat[i-1][j-1].postfix_form->postfix[0]);
							//infixtopostfix(mat[i - 1][j - 1].formula);
							//printf("\n%s\n", mat[i - 1][j - 1].postfix_form);
							//printf("%dhello world\t", 0);
							int res = postfix_evaluate(mat[i-1][j-1].postfix_form, mat);
							printf("%d\t", res);
						}
						else
						{
							printf("%d\t", 0);
						}
					}
					else{
						if (i == 0 && j == 0)
							printf("\t");
					}
				}
			}


		}
		printf("\n");
	}
}

void export(char *fname, cell **mat, int row, int col, char* operators)
{
	
	//printf("%s", fname);
	FILE *fptr = fopen(fname, "w");
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
				fprintf(fptr, "%s ,", mat[i][j].formula);
				//fprintf(fptr, " ,");
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
	return;

}


void import(char *fname, int row, int col, cell **mat, char* operators)
{
	
	//printf("%s", fname);
	FILE *fptr = fopen(fname, "r");
	if (fptr==NULL)
	{
		printf("file does not exists\n");
		return;
	}
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			
			char *temp = (char*)calloc(20, sizeof(char));
			fscanf(fptr, "%s ,", temp);
			if (temp)
			{
				mat[i][j].formula = (char*)calloc(20, sizeof(char));
				strcpy(mat[i][j].formula, temp);
			}
		}
		fscanf(fptr, "\n");
	}
	fclose(fptr);
	return;
}
