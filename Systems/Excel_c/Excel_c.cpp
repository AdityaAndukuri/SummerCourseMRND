// Excel_c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "utilities.h"
#include "operations.h"
#include <string.h>
#include <stdlib.h>
//#include <unistd.h>
#include <iostream>
#include <unordered_map>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	char *exit = "exit";
	unordered_map<string, int> umap;
	umap["get"] = 1;
	umap["set"] = 2;
	umap["print"] = 3;
	umap["export"] = 4;
	umap["import"] = 5;
	umap["exit"] = 6;
	umap["save"] = 7;
	char operators[4] = { '+', '/', '-', '/' };
	int row = 10, col = 10;
	cell **mat = createMat(row,col);
	char *choice = (char*)calloc(10, sizeof(char));
	char *row_col = (char*)calloc(5, sizeof(char));
	char *sfname = (char*)calloc(20, sizeof(char));
	char *dfname = (char*)calloc(20, sizeof(char));
	do{
		printf(">");
		scanf("%s", choice);
		choice = _strlwr(choice);
		int command = umap[choice];
		switch(command)
		{
		case 1:
			scanf("%s", row_col);
			printf("%s\n", get(row_col, mat,operators));
			break;
		case 2:
			scanf("%s", row_col);
			set(row_col, mat, operators);
			break;
		case 3:
			print(row, col, mat, operators);
			break;
		case 4:
			scanf("%s", dfname);
			convertfname(dfname);
			if (strcmp(sfname, dfname) == 0)
			{
				export(dfname, mat, row, col, operators);
			}
			else{
				
				FILE *fptr = fopen(dfname, "r");
				if (fptr)
				{
					printf("Do you want to overwrite?(Y?N):");
					char ch;
					scanf("\n%c", &ch);
					if (ch == 'Y' || ch == 'y')
					{
						export(dfname, mat, row, col, operators);
					}
				}
				else
					export(dfname, mat, row, col, operators);
			}
			break;
		case 5:
			scanf("%s", sfname);
			convertfname(sfname);
			import(sfname, row, col, mat, operators);
			break;
		case 6:
			break;
		case 7:
			if (strlen(sfname) != 0)
			{
				export(sfname, mat, row, col, operators);
			}
			else{
				printf("enter file name\n");
				scanf("%s", dfname);
				convertfname(dfname);
				/*if (access(dfname, F_OK) != -1) {
					// file exists
				}
				else {
					// file doesn't exist
				}*/
				FILE *fptr = fopen(dfname, "r");
				if (fptr)
				{
					printf("Do you want to overwrite?(Y?N):");
					char ch;
					scanf("\n%c", &ch);
					if (ch == 'Y' || ch == 'y')
					{
						export(dfname, mat, row, col, operators);
					}
				}
				else
				export(dfname, mat, row, col, operators);
			}
			break;
		default:
			printf("Invalid command\n");
		}
	} while (strcmp(choice, exit) != 0);
	return 0;
}

