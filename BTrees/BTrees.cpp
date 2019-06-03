// BTrees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define PAGESIZE 32



typedef struct{
	char pagetype;
	char unused[3];
	int data[3];
	int childpages[4]; //(3+4)*4=28 appx eq pagesize
}NonLeafpage;

struct s2 {
	int i;
	char ch;
	double d;
};

struct s3 {
	int i; //8
	double d;//8
	char ch;
	int j; //ch+j = 8
};



 
typedef struct{
	char pagetype;
	char unused[3];
	//int data[(PAGESIZE / sizeof(int))-1];
	int student_id[3];
	char student_name[3][5];
	char unused2;
}LeafPage;

typedef struct{
	char pagebuffer[PAGESIZE];
	bool used;
	time_t seconds;
	int pageid;
	
}PageInfo;

#pragma pack(1) //it applies to all structures below it
struct s1 {
	int i;
	char ch;
	double d;
};

int _tmain(int argc, _TCHAR* argv[])
{
	//printf("size of nonleafpage is %d\nsizeof leaf page is %d\n", sizeof(NonLeafpage), sizeof(LeafPage));
	//printf("size of s1 is %d\nsize of s2 is %d\nsize of s3 is %d\n", sizeof(s1), sizeof(s2),sizeof(s3));
	FILE *fptr = fopen("testbtree.txt", "rb+");
	FILE *input = fopen("students_info.txt", "rb+");
	if (fptr == NULL)
	{
		fptr = fopen("testbtree.txt", "wb+");
		int i;
		//printf("enter student details\n");
		int ind = 0;
		int count = 0;
		char c;
		for (c = getc(input); c != EOF; c = getc(input))
			if (c == '\n') // Increment count if this character is newline 
				count = count + 1;
		count++;
		rewind(input);
		printf("Input length is %d\n", count);
		int no_leafs = count / 3;
		if (count % 3 != 0)
			no_leafs++;
		int no_heads = no_leafs / 4;
		if (no_leafs % 4 != 0)
			no_heads++;
		LeafPage *leafs = (LeafPage*)calloc(no_leafs, sizeof(LeafPage));
		NonLeafpage *nonLeaf = (NonLeafpage*)calloc(no_heads, sizeof(NonLeafpage));
		for (i = 0; i < no_leafs; i++)
		{

			leafs[i].pagetype = 'l';
			for (int j = 0; j < 3; j++)
			{
				fscanf(input, "%d,", &leafs[i].student_id[j]);
				fscanf(input, "%s", leafs[i].student_name[j]);
			}
		}
		int k;
		printf("student details\n");
		for (k = 0; k < no_heads; k++)
		{
			nonLeaf[k].pagetype = 'n';
			for (i = 0; i < 4; i++)
			{
				nonLeaf[k].childpages[i] = i;
				printf("%c\n", leafs[i].pagetype);
				for (int j = 0; j < 3; j++)
				{
					printf("%d ", leafs[i].student_id[j]);
					printf("%s\n", leafs[i].student_name[j]);

				}
				if (i > 0)
				{
					nonLeaf[k].data[i - 1] = leafs[i].student_id[0];
				}
			}
		}

		for (i = 0; i < no_heads; i++)
		{
			for (int j = 0; j < no_leafs; j++)
				printf("c[%d] is %d\n", j + 1, nonLeaf[i].childpages[j]);
			for (int j = 0; j < no_leafs - 1; j++)
			{
				printf("v[%d] is %d\n", j + 1, nonLeaf[i].data[j]);
			}
		}

		char *num = (char *)calloc(10, sizeof(char));
		_itoa(no_leafs, num, 10);
		fwrite(num, PAGESIZE, 1, fptr);

		for (i = 0; i < no_leafs; i++)
		{
			char *leaf_char = (char *)calloc(PAGESIZE, sizeof(char));
			memcpy(leaf_char, &leafs[i], PAGESIZE);
			fwrite(leaf_char, PAGESIZE, 1, fptr);
		}


		num = (char *)calloc(10, sizeof(char));
		_itoa(no_heads, num, 10);
		fwrite(num, PAGESIZE, 1, fptr);

		for (i = 0; i < no_leafs; i++)
		{
			char *head_char = (char *)calloc(PAGESIZE, sizeof(char));
			memcpy(head_char, &nonLeaf[i], PAGESIZE);
			fwrite(head_char, PAGESIZE, 1, fptr);
		}

		rewind(fptr);
	}
	else{
		int no_leafs;
		char *num = (char *)calloc(10, sizeof(char));
		fread(num, PAGESIZE, 1, fptr);
		no_leafs = atoi(num);
		printf("%d\n", no_leafs);
		fseek(fptr, PAGESIZE*no_leafs, SEEK_CUR);
		/*LeafPage *leafs = (LeafPage*)calloc(no_leafs, sizeof(LeafPage));
		LeafPage leaf;
		int i = 0;
		int ind=0;
		for (i = 0; i < no_leafs; i++)
		{
			char *leaf_char = (char *)calloc(PAGESIZE, sizeof(char));
			memcpy(leaf_char, &leafs[i], PAGESIZE);
			fread(&leaf, PAGESIZE, 1, fptr);
			leafs[ind++] = leaf;
		}
		int no_heads = no_leafs / 4;
		if (no_leafs % 4 != 0)
			no_heads++;
		//LeafPage *leafs = (LeafPage*)calloc(no_leafs, sizeof(LeafPage));
		NonLeafpage *nonLeaf = (NonLeafpage*)calloc(no_heads, sizeof(NonLeafpage));
		printf("student details\n");
		int k;
		for (k = 0; k < no_heads; k++)
		{
			nonLeaf[k].pagetype = 'n';
			for (i = 0; i < 4; i++)
			{
				nonLeaf[k].childpages[i] = i;
				printf("%c\n", leafs[i].pagetype);
				for (int j = 0; j < 3; j++)
				{
					printf("%d ", leafs[i].student_id[j]);
					printf("%s\n", leafs[i].student_name[j]);

				}
				if (i > 0)
				{
					nonLeaf[k].data[i - 1] = leafs[i].student_id[0];
				}
			}
		}

		for (i = 0; i < no_heads; i++)
		{
			for (int j = 0; j < no_leafs; j++)
				printf("c[%d] is %d\n", j + 1, nonLeaf[i].childpages[j]);
			for (int j = 0; j < no_leafs - 1; j++)
			{
				printf("v[%d] is %d\n", j + 1, nonLeaf[i].data[j]);
			}
		}
		*/
		num = (char *)calloc(10, sizeof(char));
		fread(num, PAGESIZE, 1, fptr);
		int no_heads = atoi(num);
		printf("%d\n", no_heads);
		PageInfo pages[3];
		int pool_count = 0;
		int query;
		while (1)
		{
			printf("enter query\n");
			scanf("%d", &query);
		}
		
	}
	
	fclose(fptr);
	fclose(input);
	getchar();
	return 0;
}

