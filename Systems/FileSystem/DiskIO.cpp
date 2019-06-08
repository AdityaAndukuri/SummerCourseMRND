#include "DiskIO.h"
int init(char *diskname, int block_ize)
{
	//printf("%s\n", diskname);
	FILE *fptr = fopen("HardDisk.hdd", "rb");
	if (fptr)
	{
		strcpy(disk_name, diskname);
		fseek(fptr, 0, SEEK_END);
		int x = (ftell(fptr) + 1);
		fclose(fptr);
		return x / block_size;
	}
	else{
		//format(block_size);
		printf("Disk does not exists");
		return 0;
	}
}

void readBlock(void *buffer, int blocknumber)
{
	FILE *fptr = fopen("HardDisk.hdd", "rb");
	//FILE *fptr = fopen(disk_name, "rb");
	if (fptr)
	{
		fseek(fptr, block_size*blocknumber, SEEK_SET);
		fread(buffer, block_size, 1, fptr);
		fclose(fptr);

	}
	else{
		printf("disk doesnot exists\n");
	}
	
	return;

}

void writeBlock(void *buffer, int blocknumber)
{
	//printf("%s", (char*)buffer);

	FILE *fptr = fopen("HardDisk.hdd", "rb+");
	//FILE *fptr = fopen(disk_name, "rb");
	if (fptr)
	{
		//rewind(fptr);
		fseek(fptr, block_size*blocknumber, SEEK_SET);
		fwrite(buffer, block_size, 1, fptr);
		fclose(fptr);

	}
	else{
		printf("disk doesnot exists\n");
	}
	
	return;
}