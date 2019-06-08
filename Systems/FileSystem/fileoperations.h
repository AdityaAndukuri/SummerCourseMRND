#ifndef _FILEOPERATIONS_H
#define _FILEOPERATIONS_H

int setFile(char *fname, int sizeofblock);
void debug();
void delete_file(char *fname);
void getFile(char *fname, int sizeofblock, char *dest);
void createOutPutFile(char *buffer, char *dest);
void list_files();
void format(int blocksize);
void mount(char *diskname);

#endif