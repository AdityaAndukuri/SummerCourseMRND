// FileSystem2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileoperations.h"
#include "DiskIO.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <unordered_map>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	unordered_map<string, int> umap;
	umap["store"] = 1;
	umap["copy"] = 2;
	umap["delete"] = 3;
	umap["format"] = 4;
	umap["list"] = 5;
	umap["debug"] = 6;
	umap["exit"] = 7;
	umap["mount"] = 8;
	char *command = (char *)calloc(20, sizeof(char));
	char *source = (char *)calloc(20, sizeof(char));
	char *dest = (char *)calloc(20, sizeof(char));
	char *output_buffer = (char *)calloc(30, sizeof(char));
	char *disk = (char *)calloc(20, sizeof(char));
	//char *disk2 = (char *)calloc(20, sizeof(char));
	//disk = "hell";
	int disksize;
	//list();
	while (1)
	{
		printf(">");
		scanf("%s", command);
			switch (umap[command])
			{
			case 1:
				scanf("%s", source);
				if (strlen(disk) == 0)
					printf("Mount the hard disk to continue");
				else
				setFile(source, block_size);
				printf("\n");
				break;
			case 2:
				scanf("%s", source);
				scanf("%s", dest);
				if (strlen(disk) == 0)
					printf("Mount the hard disk to continue");
				else
				getFile(source, block_size, dest);
				printf("\n");
				//if (strcmp(output_buffer, "No Such file found") == 0)
				//	printf("%s\n", output_buffer);
				/*else
				createOutPutFile(output_buffer, dest);*/
				break;
			case 3:
				scanf("%s", source);
				if (strlen(disk) == 0)
					printf("Mount the hard disk to continue");
				else
				delete_file(source);
				printf("\n");
				break;
			case 4:
				if (strlen(disk) == 0)
					printf("Mount the hard disk to continue");
				else
				format(block_size);
				printf("\n");
				break;
			case 5:
				if (strlen(disk) == 0)
					printf("Mount the hard disk to continue");
				else
				list_files();
				break;
			case 6:
				if (strlen(disk) == 0)
					printf("Mount the hard disk to continue");
				else
				debug();
				break;
			case 7:
				exit(0);
			case 8:
				scanf("%s", disk);
				//scanf("%d", &disksize);
				mount(disk);
				printf("\n");
				break;
			}
			
		
	}
	getchar();
	return 0;

}

