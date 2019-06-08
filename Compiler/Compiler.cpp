// Compiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static int address = 0;
#define byte_size 1
#define ins_count 14
#define const_count 4
#define register_count 7
#define max_tokens 100



typedef struct {
	int start_address;
	char name[10];
	int no_bytes;

}token;

typedef struct {
	int int_no;
	int opcode;
	int parameters[5];
}intermediate;

typedef struct{
	char name[10];
	int address;
}label;

void push(int *stack, int *top, int data)
{
	*top = *top + 1;
	stack[*top] = data;
	return;
}

int pop(int *stack, int *top)
{
	if(*top == -1)
		return -1;
	int x = stack[*top];
	*top = *top - 1;
	return x;


}



int tokenizer(char *command, char *instruction, char** arguments)
{
	int start_ind = 0;
	int arg_count = 0;
	while (command[start_ind] == ' ')
		start_ind++;
	sscanf(command+start_ind, "%s", instruction);
	int i = 0;
	for (i = 0; command[i] != '\0'; i++)
		if (command[i] == ',')
			command[i] = '  ';
	while (command[start_ind] != '\0')
	{
		while (command[start_ind] != ' '&&command[start_ind] != '\0')
		{
			
			start_ind++;
		}
		if (command[start_ind] == '\0')
			break;
		while (command[start_ind] == ' '&&command[start_ind] != '\0')
		{
			
			start_ind++;
		}
		sscanf(command+start_ind, "%s", arguments[arg_count]);
		arg_count++;
	}
	printf("\n");
	return arg_count;
}
int comm_ind(char **commands, char* command, int n)
{
	for (int i = 0; i < n; i++)
		if (strcmp(command, commands[i]) == 0)
			return i + 1;
	return -1;
}




int buildTable(token *table, char *token_inp,int token_count,char *instruction)
{
	token curr_token;
	int size = 0, start_ind=0, end_ind;
	if (strcmp(instruction, "DATA") == 0)
	{
		if (token_inp[strlen(token_inp) - 1] == ']'){
			token_inp[strlen(token_inp) - 1] = '\0';
			while (token_inp[start_ind] != '[')
				start_ind++;
			end_ind = start_ind;
			start_ind++;
			size = atoi(token_inp + start_ind);
			token_inp[end_ind] = '\0';
			sscanf(token_inp, "%s", curr_token.name);
			if (token_count == 0)
			{
				curr_token.start_address = address;
				
			}
			else{
				if (table[token_count - 1].no_bytes!=0)
					curr_token.start_address = table[token_count - 1].start_address + table[token_count - 1].no_bytes;
				else
					curr_token.start_address = table[token_count - 1].start_address + 1;
				

			}
			curr_token.no_bytes = byte_size*size;
			if (token_count >= max_tokens)
			{
				table = (token*)realloc(table, max_tokens * 2);
			}
			table[token_count++] = curr_token;
		}
		else{
			strcpy(curr_token.name, token_inp);
			if (token_count == 0)
			{
				curr_token.start_address = address;
				
			}
			else{
				if (table[token_count - 1].no_bytes != 0)
					curr_token.start_address = table[token_count - 1].start_address + table[token_count - 1].no_bytes;
				else
					curr_token.start_address = table[token_count - 1].start_address + 1;
				

			}
			curr_token.no_bytes = byte_size;
			if (token_count >= max_tokens)
			{
				table = (token*)realloc(table, max_tokens * 2);
			}
			table[token_count++] = curr_token;

		}
	}
	else{
		strcpy(curr_token.name, token_inp);
		if (token_count == 0)
		{
			curr_token.start_address = address;
			
		}
		else{
			if (table[token_count - 1].no_bytes != 0)
				curr_token.start_address = table[token_count - 1].start_address + table[token_count - 1].no_bytes;
			else
				curr_token.start_address = table[token_count - 1].start_address + 1;
		}
		curr_token.no_bytes = 0;
		if (token_count >= max_tokens)
		{
			table = (token*)realloc(table, max_tokens * 2);
		}
		table[token_count++] = curr_token;
	}
	return token_count;
	

}

int find_start_address(token *symboltable, char *operand, int token_count)
{
	int i;
	for (i = 0; i < token_count; i++)
	{
		if (strcmp(symboltable[i].name, operand) == 0)
			return symboltable[i].start_address;
	}
	return -1;
}


int parsePrint(token *symboltable, char **args, char **commands, char **registers, intermediate *int_table, int int_count, int token_count, char *instruction)
{
	char *operand1 = args[0];
	intermediate inter;
	inter.int_no = int_count + 1;
	int start_ind = 0, end_ind, size = 0;
	inter.opcode = comm_ind(commands, instruction, ins_count);
	//printf("poe is %s\n", operand1);
	if (operand1[strlen(operand1) - 1] == ']')
	{
		operand1[strlen(operand1) - 1] = '\0';
		while (operand1[start_ind] != '[')
			start_ind++;
		end_ind = start_ind;
		start_ind++;
		size = atoi(operand1 + start_ind);
		size;
		operand1[end_ind] = '\0';
	}
	int start = find_start_address(symboltable, operand1, token_count);
	inter.parameters[0] = start + size*byte_size;
	if (start != -1)
		inter.parameters[0] = start;
	else{
		inter.parameters[0] = comm_ind(registers, operand1, register_count) - 1;
	}
	int_table[int_count++] = inter;
	return int_count;

}

int parseRead(token *symboltable, char **args, char **commands, char **registers, intermediate *int_table, int int_count, int token_count, char *instruction)
{
	char *operand1 = args[0];
	intermediate inter;
	inter.int_no = int_count + 1;
	inter.opcode = comm_ind(commands, instruction, ins_count);
	inter.parameters[0] = comm_ind(registers, operand1, register_count) - 1;
	int_table[int_count++] = inter;
	return int_count;

}
int parseArithmetic(token *symboltable, char **args, char **commands, char **registers, intermediate *int_table, int int_count,int token_count, char *instruction)
{
	char *operand1 = args[0];
	char *operand2 = args[1];
	char *operand3 = args[2];
	intermediate inter;
	inter.int_no = int_count + 1;
	inter.opcode = comm_ind(commands, instruction, ins_count);
	int start = find_start_address(symboltable, operand1,token_count);
	if (start != -1)
		inter.parameters[0] = start;
	else{
		inter.parameters[0] = comm_ind(registers, operand1, register_count)-1;
	}
	start = find_start_address(symboltable, operand2, token_count);
	if (start != -1)
		inter.parameters[1] = start;
	else{
		inter.parameters[1] = comm_ind(registers, operand2, register_count) - 1;
	}
	start = find_start_address(symboltable, operand3, token_count);
	if (start != -1)
		inter.parameters[2] = start;
	else{
		inter.parameters[2] = comm_ind(registers, operand3, register_count) - 1;
	}
	int_table[int_count++] = inter;
	return int_count;
}

int parseMov1(token *symboltable, char **args, char **commands, char **registers, intermediate *int_table, int int_count, int token_count, char *instruction)
{
	char *operand1 = args[0];
	char *operand2 = args[1];
	intermediate inter;
	inter.int_no = int_count + 1;
	int start_ind = 0, end_ind, size=0;
	inter.opcode = comm_ind(commands, instruction, ins_count);
	//printf("%d is opcode poe is %s\n",inter.opcode, operand1);
	if (operand1[strlen(operand1) - 1] == ']')
	{
		operand1[strlen(operand1) - 1] = '\0';
		while (operand1[start_ind] != '[')
			start_ind++;
		end_ind = start_ind;
		start_ind++;
		size = atoi(operand1 + start_ind);
		size;
	    operand1[end_ind] = '\0';
	}
	int start = find_start_address(symboltable, operand1, token_count);
	inter.parameters[0] = start+size*byte_size;
	inter.parameters[1] = comm_ind(registers, operand2, register_count) - 1;
	int_table[int_count++] = inter;
	return int_count;
}

int parseMov2(token *symboltable, char **args, char **commands, char **registers, intermediate *int_table, int int_count, int token_count, char *instruction)
{
	char *operand1 = args[0];
	char *operand2 = args[1];
	intermediate inter;
	inter.int_no = int_count + 1;
	inter.opcode = comm_ind(commands, instruction, ins_count);
	int start_ind = 0, end_ind, size = 0;
	if (operand2[strlen(operand2) - 1] == ']')
	{
		operand2[strlen(operand2) - 1] = '\0';
		while (operand2[start_ind] != '[')
			start_ind++;
		end_ind = start_ind;
		start_ind++;
		size = atoi(operand2 + start_ind);
		size;
		operand2[end_ind] = '\0';
	}
	int start = find_start_address(symboltable, operand2, token_count);
	inter.parameters[1] = start + size*byte_size;
	inter.parameters[0] = comm_ind(registers, operand1, register_count) - 1;
	int_table[int_count++] = inter;
	return int_count;
}

int buildLabel(label *label_table, int label_count, int instructions_count, char* instruction)
{
	label lbl;
	lbl.address = instructions_count+1;
	if (instruction[strlen(instruction) - 1] == ':'){
		instruction[strlen(instruction) - 1] = '\0';
	}
	strcpy(lbl.name, instruction);
	label_table[label_count++] = lbl;
	return label_count;
}

int parseJmp(token *symboltable, char **args, char **commands, int token_count, char *instruction, label *label_table, int label_count, intermediate *int_table, int int_count)
{
	int i;
	char *operand = args[0];
	intermediate inter;
	inter.int_no = int_count + 1;
	inter.opcode = comm_ind(commands, instruction, ins_count);
	for (i = 0; i < label_count; i++)
	{
		if (strcmp(operand, label_table[i].name) == 0)
		{
			inter.parameters[0] = label_table[i].address;
			int_table[int_count++] = inter;
			return int_count;
		}

	}
}

int parseRelational(char **args, char **commands, char **registers, intermediate *int_table, int int_count)
{
	char *operand1 = args[0];
	char *operand2 = args[2];
	char *instruction = args[1];
	intermediate inter;
	inter.int_no = int_count + 1;
	inter.opcode = comm_ind(commands, instruction, ins_count);
	inter.parameters[0] = comm_ind(registers, operand1, register_count) - 1;
	inter.parameters[1] = comm_ind(registers, operand2, register_count) - 1;
	int_table[int_count++] = inter;
	return int_count;
}

int parseElse(label *label_table, int label_size, char **commands, int *int_count, intermediate *int_table, char *instruction,int *stack, int *top)
{
	push(stack, top, *int_count+1);
	intermediate inter;
	inter.int_no = *int_count + 1;
	inter.opcode = comm_ind(commands, "JMP", ins_count);
	int_table[*int_count++] = inter;
	return buildLabel(label_table, label_size, *int_count, instruction);
}

int parseIf(int *stack, int *top, char **commands, intermediate *int_table, int int_count, char **args, char *instruction,char **registers)
{
	push(stack, top, int_count+1);
	intermediate inter;
	inter.int_no = int_count + 1;
	inter.opcode = comm_ind(commands, instruction, ins_count);
	char *operand1 = args[0];
	char *operand2 = args[2];
	char *relational = args[1];
	inter.parameters[0] = comm_ind(registers, operand1, register_count) - 1;
	inter.parameters[1] = comm_ind(registers, operand2, register_count) - 1;
	inter.parameters[2] = comm_ind(commands, relational, ins_count);
	int_table[int_count++] = inter; 
	return int_count;

}

int parseEndIf(int *stack, int *top, int label_cnt, label *label_table, intermediate *int_table, int int_count,char *instruction,char **commands)
{
	int instruction_no = pop(stack, top);
	intermediate inter;
	int i;
	for (i = 0; i < int_count; i++)
	{
		if (int_table[i].int_no == instruction_no)
		{
			break;
		}
	}
	if (strcmp(commands[int_table[i].opcode - 1], "ELSE") == 0)
	{
		int_table[i].parameters[3] = int_count + 1;
		instruction_no = pop(stack, top);
		for (i = 0; i < int_count; i++)
		{
			if (int_table[i].int_no == instruction_no)
			{
				break;
			}
		}
		int_table[i].parameters[3] = int_count + 1;
	}
	else{
		int_table[i].parameters[3] = int_count + 1;
	}
	return buildLabel(label_table, label_cnt, int_count, instruction);
}

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *fptr = fopen("inp.txt", "rb+");
	FILE *output = fopen("output.txt", "wb+");
	char *command = (char*)calloc(20, sizeof(char));
	char line[256];
	char *instruction = (char*)calloc(20, sizeof(char));
	char **arguments = (char**)calloc(10, sizeof(char*));
	for (int i = 0; i < 10; i++)
		arguments[i] = (char*)calloc(20, sizeof(char));
	int arg_count = 0, i;
	int instructions_count=0;
	int *stack = (int *)calloc(max_tokens, sizeof(int));
	int top = -1;

	char *commands[] = {
		"MOV1",
		"MOV2",
		"ADD",
		"SUB",
		"MUL",
		"JMP",
		"IF",
		"EQ",
		"LT",
		"GT",
		"LTEQ",
		"GTEQ",
		"PRINT",
		"READ"
	};
	char *registers[] = {
		"AX",
		"BX",
		"CX",
		"DX",
		"EX",
		"FX",
		"GX",
		"HX"
	};
	char *constants[] = {
		"DATA",
		"CONST",
		"ELSE",
		"ENDIF"
	};
	int no_tokens = 0;
	token *symbol_table = (token *)calloc(max_tokens, sizeof(token));
	intermediate *int_table = (intermediate*)calloc(max_tokens, sizeof(intermediate));
	label *label_table = (label*)calloc(max_tokens, sizeof(label));
	int label_count = 0;
	for (int i = 0; i < max_tokens; i++)
		for (int j = 0; j < 5; j++)
			int_table[i].parameters[j] = 0;
	while (fgets(line, sizeof(line), fptr)) {
		arg_count = tokenizer(line, instruction, arguments);

		if (strcmp(instruction, "MOV") == 0)
		{
			char *operand1 = (char*)calloc(20, sizeof(char));
			char *operand2 = (char*)calloc(20, sizeof(char));
			strcpy(operand1, arguments[0]);
			strcpy(operand2, arguments[1]);
			if (comm_ind(registers, operand1, register_count) != -1)
			{
			
				instructions_count = parseMov2(symbol_table, arguments, commands, registers, int_table, instructions_count, no_tokens, "MOV2");
			}
			else{
				
				instructions_count = parseMov1(symbol_table, arguments, commands, registers, int_table, instructions_count, no_tokens, "MOV1");
			}
		}
		else{
			int command_ind = comm_ind(commands, instruction,ins_count);
			if (command_ind != -1)
			{
				
				switch (command_ind)
				{
				case 3:
					instructions_count = parseArithmetic(symbol_table, arguments, commands, registers, int_table, instructions_count, no_tokens, instruction);
					break;
				case 4:
					instructions_count = parseArithmetic(symbol_table, arguments, commands, registers, int_table, instructions_count, no_tokens, instruction);
					break;
				case 5:
					instructions_count = parseArithmetic(symbol_table, arguments, commands, registers, int_table, instructions_count, no_tokens, instruction);
					break;
				case 6:
					instructions_count = parseJmp(symbol_table, arguments, commands, no_tokens, instruction, label_table, label_count, int_table, instructions_count);
					break;
				case 7:
					
					instructions_count = parseIf(stack, &top, commands, int_table, instructions_count, arguments, instruction, registers);
					break;
				case 13:
					instructions_count = parsePrint(symbol_table, arguments, commands, registers, int_table, instructions_count, no_tokens, instruction);
					break;
				case 14:
					instructions_count = parseRead(symbol_table, arguments, commands, registers, int_table, instructions_count, no_tokens, instruction);
					break;
				}
			}
			else
			{
				command_ind = comm_ind(constants, instruction, const_count);
				if (command_ind != -1)
				{
					switch (command_ind)
					{
					case 1:
						no_tokens = buildTable(symbol_table, arguments[0], no_tokens, instruction);
						break;
					case 2:
						no_tokens = buildTable(symbol_table, arguments[0], no_tokens, instruction);
						break;
					case 3:
						label_count = parseElse(label_table,label_count,commands,&instructions_count,int_table,instruction,stack,&top);
						break;
					case 4:
						label_count = parseEndIf(stack,&top,label_count,label_table,int_table,instructions_count,instruction,commands);
						break;

					}
				}
				else{
					
					label_count = buildLabel(label_table, label_count, instructions_count, instruction);
				}
			}
			
		}
		
		

	}
	printf("SYMBOL TABLE\n");
	for (int i = 0; i < no_tokens; i++)
		printf("%s %d %d\n", symbol_table[i].name, symbol_table[i].start_address, symbol_table[i].no_bytes);
	printf("\n\n");
	printf("INSTRUCTION TABLE\n");
	for (int i = 0; i < instructions_count; i++)
	{
		printf("%d %d ", int_table[i].int_no, int_table[i].opcode);
		for (int j = 0; j < 4; j++)
			if (int_table[i].parameters[j]>=0)
			printf("%d ", int_table[i].parameters[j]);
		printf("\n");
	}
	printf("\n");
	printf("LABEL TABLE\n");
	for (int i = 0; i < label_count; i++)
		printf("%s %d\n", label_table[i].name, label_table[i].address);
	fclose(fptr);
	char *length = (char*)calloc(20, sizeof(char));
	_itoa(no_tokens, length, 10);
	fwrite(length, sizeof(char), 1, output);
	fwrite(symbol_table, sizeof(token), no_tokens,output);
	_itoa(instructions_count, length, 10);
	fwrite(length, sizeof(char), 1, output);
	fwrite(int_table, sizeof(intermediate), instructions_count, output);
	_itoa(label_count, length, 10);
	fwrite(length, sizeof(char), 1, output);
	fwrite(label_table, sizeof(label), label_count, output);
	fclose(output);
	getchar();
	return 0;
}

