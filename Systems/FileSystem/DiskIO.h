#include "stdafx.h"
#include <string.h>
#define block_size 16384
#ifndef _DISKIO_H
#define _DISKIO_H
static char disk_name[30];
int init(char *diskname, int blocksize);
void readBlock(void *buffer, int blocknumber);
void writeBlock(void *buffer, int blocknumber);
#endif