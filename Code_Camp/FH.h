#ifndef FH_H
#define FH_H

#define FILE_FAILURE 0
#define NUM_FILES 2
#define INPUT 0
#define OUTPUT 1

int FH_OpenFiles(FILE* [], char*);
void FH_CloseFiles(FILE* []);

#endif
