#include "stdafx.h"
#include "fileoperations.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <unordered_map>
#define disksize 104875600
#ifndef _FILEUTILS_H
#define _FILEUTILS_H

static int blocksize;
static char diskname[]="ADI";
typedef struct {
	char file_name[20];
	int start_block;
	int no_blocks;
	int file_length;
}file;

typedef struct{
	int magic;
	int no_files;
	file files[32];
	bool available_blocks[6400]; //100MB/8MB = 6400*2
}metadata;
#endif