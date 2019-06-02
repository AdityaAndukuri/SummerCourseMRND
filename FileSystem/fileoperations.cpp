#include "DiskIO.h"
#include "stdafx.h"
#include "fileutils.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <unordered_map>

int setFile(char *fname, int sizeofblock)
{
	metadata *meta = (metadata *)calloc(1, sizeof(metadata));
	//FILE* fptr = fopen("HardDisk.hdd", "rb+");
	char *buffer = (char*)calloc(1, block_size);
	FILE *input = fopen(fname, "rb+");
	int fsize = 0;
	fseek(input, 0, SEEK_END);
	fsize = ftell(input);
	int required_blocks;
	if (fsize%sizeofblock)
		required_blocks = (fsize / sizeofblock + 1);
	else
		required_blocks = (fsize / sizeofblock);

	readBlock(buffer, 0);
	
	memcpy(meta, buffer, sizeof(metadata));
	//debug();
	//fread(meta, sizeof(metadata), 1, fptr);
	int i, j;
	int flag = 0;
	int count = 0, stored = 0;
	for (i = 1; i < 6400; i++)
	{
		if (meta->available_blocks[i] == 0)
		{
			count++;
			if (flag==0)
			{
				flag = i;
				printf("%d is i\n", i);
				if (required_blocks == 1)
				{
					stored = 1;
					break;
				}
				
			}
			if (count == required_blocks+1)
			{
				break;
			}
		}
		/*else{
			count = 0;
		}*/
	}
	if (i == 6400)
		return 0;
	file newfile;  
	newfile.file_length = fsize;
	strcpy(newfile.file_name, fname);
	newfile.no_blocks = required_blocks;
	newfile.start_block = flag;
	meta->files[meta->no_files++] = newfile;
	char *start_indices = (char *)calloc(1, block_size);
	int ind = 0;
	rewind(input);
	if (stored==1)
	{
		meta->available_blocks[i] = 1;
		if (fsize >= sizeofblock)
			//memcpy(buffer, input_buff, sizeofblock);
			fread(buffer, 1, block_size, input);
		else
			fread(buffer, 1, fsize, input);
		//	printf("%s is bugg\n", buffer);
		//printf("%d %d %d \n", i, i*sizeofblock,fsize);
		writeBlock(buffer, i);
	}
	else{

		/*i = i - count + 1;

		for (j = i; j < i + required_blocks; j++)
			meta->available_blocks[j] = 1;
			*/
		int temp_size = fsize;
		//printf("%d is flag, %d is i\n", flag, i);
		meta->available_blocks[flag] = 1;
		char *num = (char*)calloc(20, sizeof(char));;

		for (j = flag+1; j <= i; j++)
		{
			if (temp_size > 0 && meta->available_blocks[j] == 0)
			{
				meta->available_blocks[j] = 1;
				_itoa(j,num,10);
				//sprintf(start_indices, "%s ", num);
				strcat(start_indices,num);
				strcat(start_indices, " ");
				//printf("%d is flag, %d is i %d is j\n", flag, i,j);
				if (temp_size >= sizeofblock)
					//memcpy(buffer, input_buff, sizeofblock);
					fread(buffer, 1, block_size, input);
				else
					fread(buffer, 1, temp_size, input);
				//	printf("%s is bugg\n", buffer);

				writeBlock(buffer, j);
				//fsize -= sizeofblock;
				temp_size -= block_size;
			}
			
			//printf("%d is temp_size j is %d\n", temp_size,j);

		}
	}
	//rewind(fptr);
	
	//fwrite(meta, sizeof(metadata), 1, fptr);
	//fsize++;// ???
	char *input_buff = (char*)calloc(1, block_size);
	memcpy(input_buff, meta,sizeof(metadata));
	writeBlock(input_buff, 0);
	writeBlock(start_indices, flag);
	//for (int k = 0; k < ind; k++)
	//	printf("%d if val\n", start_indices[k]);
	//printf("%[^\n]s", start_indices);
	//puts(start_indices);
	//debug();
	//fread(inp, sizeof(char), fsize + 1, input);
	//fseek(fptr, i*sizeofblock, SEEK_SET);
	//fwrite(inp, sizeof(char), fsize + 1, fptr);
	//fclose(fptr);
	//int initial_block = i*sizeofblock;
	//printf("init is %d %d is i\n", initial_block,i);
	
	/*while (fsize > 0)
	{
		if (fsize >= sizeofblock)
			//memcpy(buffer, input_buff, sizeofblock);
			fread(buffer, 1, block_size, input);
		else
			fread(buffer, 1, fsize, input);
	//	printf("%s is bugg\n", buffer);

		writeBlock(buffer, initial_block);
		initial_block++;
		fsize -= sizeofblock;

	}*/
	fclose(input);
	return 1;
}

void debug()
{
	metadata *tmp = (metadata *)calloc(1, sizeof(metadata));
	//FILE *fptr = fopen("HardDisk.hdd", "rb+");
	//fread(tmp, sizeof(metadata), 1, fptr);
	char *buffer = (char *)calloc(1, block_size);
	readBlock(buffer, 0);
	memcpy(tmp, buffer, sizeof(metadata));
	printf("magic number is %d\nNumber of files is %d\n", tmp->magic, tmp->no_files);
	//for (int i = 0; i < 200; i++)
	//printf("%d", tmp->available_blocks[i]);
	
	printf("File details: \nFilename\tstart block\tNo of blocks\tfile size\n");
	for (int i = 0; i < tmp->no_files; i++)
	{
		printf("%s\t%d\t\t%d\t\t%d\n", tmp->files[i].file_name, tmp->files[i].start_block, tmp->files[i].no_blocks, tmp->files[i].file_length);
	}
	
}

void delete_file(char *fname)
{
	
	metadata *tmp = (metadata *)calloc(1, sizeof(metadata));
	//FILE *fptr = fopen("HardDisk.hdd", "rb+");
	//fread(tmp, sizeof(metadata), 1, fptr);
	char *buffer = (char *)calloc(1, block_size);
	readBlock(buffer, 0);
	memcpy(tmp, buffer, sizeof(metadata));
	int i;
	for (i = 0; i < 32; i++)
	{
		if (strcmp(fname, tmp->files[i].file_name) == 0)
		{
			//printf("%d is i%s %d %d %d\n",i, tmp->files[i].file_name, tmp->files[i].start_block, tmp->files[i].no_blocks, tmp->files[i].file_length);
			break;
		}
	}
	if (i == 32)
	{
		printf("No Such file found\n");
		return;
	}
	else{
		if (tmp->files[i].no_blocks == 1)
		{
			tmp->available_blocks[tmp->files[i].start_block] = 0;
		}
		else{
			/*for (int j = tmp->files[i].start_block; j < tmp->files[i].start_block + tmp->files[i].no_blocks+1; j++)
			{
				tmp->available_blocks[j] = 0;
				//printf("%d is j\n", j);
			}*/
			char *out_buffer = (char*)malloc(block_size);
			int initial_block = tmp->files[i].start_block;
			tmp->available_blocks[tmp->files[i].start_block] = 0;
			readBlock(out_buffer, initial_block);
			//puts(out_buffer);

			int *arr = (int*)calloc(tmp->files[i].no_blocks, sizeof(int));
			int str_ind = 0;
			for (int k = 0; k < tmp->files[i].no_blocks; k++)
			{
				sscanf(out_buffer + str_ind, "%d", &arr[k]);
				/*readBlock(out_buffer_res, arr[k]);
				if (fsize >= sizeofblock)
					//memcpy(buffer,input,sizeofblock);
					fwrite(out_buffer_res, 1, sizeofblock, fptr);
				else
					fwrite(out_buffer_res, 1, fsize, fptr);
				fsize -= sizeofblock;*/
				tmp->available_blocks[arr[k]] = 0;
				while (out_buffer[str_ind] != ' ')
				{
					str_ind++;
				};
				str_ind++;
				//printf("%d\n", arr[k]);
			}




		}
		tmp->files[i] = tmp->files[(tmp->no_files) - 1];
		//printf("%d is i%s %d %d %d\n", i, tmp->files[i].file_name, tmp->files[i].start_block, tmp->files[i].no_blocks, tmp->files[i].file_length);
		tmp->no_files--;
		char *input_buff = (char*)malloc(block_size);
		memcpy(input_buff, tmp, sizeof(metadata));
		writeBlock(input_buff, 0);
		return;
	}
}

void getFile(char *fname, int sizeofblock, char *dest)
{
	metadata *tmp = (metadata *)calloc(1, sizeof(metadata));
	//FILE *fptr = fopen("HardDisk.hdd", "rb+");
	//fread(tmp, sizeof(metadata), 1, fptr);
	char *buffer = (char *)calloc(1, block_size);
	readBlock(buffer, 0);
	memcpy(tmp, buffer, sizeof(metadata));
	int i;
	for (i = 0; i < 32; i++)
	{
		if (strcmp(fname, tmp->files[i].file_name) == 0)
		{
			//printf("%d is i%s %d %d %d\n",i, tmp->files[i].file_name, tmp->files[i].start_block, tmp->files[i].no_blocks, tmp->files[i].file_length);
			break;
		}
	}
	if (i == 32)
	{
		printf("no file\n");
		return;
	}
	//printf("%s %d %d %d\n", tmp->files[i].file_name, tmp->files[i].start_block, tmp->files[i].no_blocks, tmp->files[i].file_length);
	//fseek(fptr, tmp->files[i].start_block*sizeofblock, SEEK_SET);
	//printf("%d is ftell %s %d %d %d\n",ftell(fptr), tmp->files[i].file_name, tmp->files[i].start_block, tmp->files[i].no_blocks, tmp->files[i].file_length);
	int fsize = tmp->files[i].file_length;
	//void *out_buffer = (char *)calloc(tmp->files[i].file_length + 1, sizeof(char));
	//int x = fread(out_buffer, tmp->files[i].file_length + 1, 1, fptr);
	//printf("%s is result %d is x\n", out_buffer,x);
	//fclose(fptr);
	char *out_buffer = (char*)malloc(block_size);
	char *out_buffer_res = (char*)malloc(block_size);
	int initial_block = tmp->files[i].start_block;
	FILE *fptr = fopen(dest, "wb");
	readBlock(out_buffer, initial_block);
	if (tmp->files[i].no_blocks == 1)
	{
		//while (fsize > 0)
		//{
			
			if (fsize >= sizeofblock)
				//memcpy(buffer,input,sizeofblock);
				fwrite(out_buffer, 1, sizeofblock, fptr);
			else
				fwrite(out_buffer, 1, fsize, fptr);
			//writeBlock(buffer, initial_block++);

			//fsize -= sizeofblock;

		//}
	}
	else{
		//puts(out_buffer);

		int *arr = (int*)calloc(tmp->files[i].no_blocks, sizeof(int));
		int str_ind = 0;
		for (int k = 0; k < tmp->files[i].no_blocks; k++)
		{
			sscanf(out_buffer+str_ind, "%d", &arr[k]);
			readBlock(out_buffer_res, arr[k]);
			if (fsize >= sizeofblock)
				//memcpy(buffer,input,sizeofblock);
				fwrite(out_buffer_res, 1, sizeofblock, fptr);
			else
				fwrite(out_buffer_res, 1, fsize, fptr);
			fsize -= sizeofblock;
			while (out_buffer[str_ind] != ' ')
			{
				str_ind++;
			};
			str_ind++;
			//printf("%d\n", arr[k]);
		}
	}

	fclose(fptr);
	//return out_buffer;



}
void createOutPutFile(char *buffer, char *dest)
{
	FILE *fptr = fopen(dest, "wb");
	fwrite(buffer, sizeof(char), strlen(buffer), fptr);
	fclose(fptr);
}

void list_files()
{
	metadata *tmp = (metadata *)calloc(1, sizeof(metadata));
	//FILE *fptr = fopen("HardDisk.hdd", "rb+");
	//fread(tmp, sizeof(metadata), 1, fptr);
	char *buffer = (char *)calloc(1, block_size);
	readBlock(buffer, 0);
	memcpy(tmp, buffer, sizeof(metadata));
	printf("Files: %d\n", tmp->no_files);

	/*for (int i = 0; i < tmp->no_files; i++)
	{
		printf("%s\n", tmp->files[i].file_name);
	}*/
}
void format(int blocksize)
{
	metadata *meta = (metadata *)calloc(1, sizeof(metadata));
	meta->magic = 1234;
	meta->no_files = 0;
	for (int i = 0; i < 6400; i++)
		meta->available_blocks[i] = 0;
	for (int i = 0; i < (sizeof(metadata) / block_size + 1); i++)
		meta->available_blocks[i] = 1;

	/*FILE *fptr = fopen("HardDisk.hdd", "rb+");
	if (fptr == NULL)
	{
	printf("Fail to open harddisk\n");
	}

	fwrite(meta, sizeof(metadata), 1, fptr);
	*/
	char *input_buff = (char*)calloc(1, block_size);
	memcpy(input_buff, meta, sizeof(metadata));
	writeBlock(input_buff, 0);
	//fclose(fptr);
}

void mount(char *diskname)
{
	int no_blocks = init(diskname, block_size);
	if (no_blocks)
	{
		metadata *meta = (metadata *)calloc(1, sizeof(metadata));
		char *buffer = (char *)calloc(1, block_size);
		readBlock(buffer, 0);
		memcpy(meta, buffer, sizeof(metadata));
		if (meta->magic != 1234)
		{
			printf("Disk corrupted!!!, formmating the disk.......\n");
			format(block_size);
		}

	}
	
}