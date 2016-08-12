#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FH.h"

int FH_OpenFiles(FILE* file[], char* fileName){
	char* oFileName = (char*) calloc(strlen(fileName) + 5, sizeof(char));
	if(oFileName == NULL){
		printf("Error:  could not allocate memory for output filename\n");
		return 0;
	}
	strcat(oFileName, fileName);
	strcat(oFileName, ".out");

	file[INPUT] = fopen(fileName, "r");
	file[OUTPUT] = fopen(oFileName, "w");

	free(oFileName);
	return file[INPUT] && file[OUTPUT];
}

void FH_CloseFiles(FILE* file[]){
	fclose(file[INPUT]);
	fclose(file[OUTPUT]);
}
