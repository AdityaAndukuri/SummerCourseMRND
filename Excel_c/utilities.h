#ifndef _UTILITIES_H
	#define _UTILITIES_H


typedef struct post
{
	char **postfix;
	int length;
};
struct cell{
	char *formula;
	post *postfix_form;
	int isvisited;

};

typedef struct cell cell;


cell **createMat(int row, int col);
void convertfname(char *fname);
//enum commands{get,set,print,import,export};
//unordered_map<string, int> commands_list();
void push(char *stack, int *top, char ope);
char pop(char *stack, int *top);
int precedence(char ope);
void push_post(char **stack, int *top, char *ope);
char *pop_post(char **stack, int *top);
#endif