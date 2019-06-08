#include "utilities.h"
#ifndef _OPERATIONS_H
	#define _OPERATIONS_H
char* get(char *row_col, cell **mat, char* operators);
void set(char *row_col, cell **mat, char* operators);
void print(int row, int col, cell **mat, char* operators);
void import(char *fname, int row, int col, cell **mat, char* operators);
void export(char *fname, cell **mat, int row, int col, char* operators);
#endif