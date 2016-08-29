#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 256
#define LINES 10
#define BUF_SIZE 1000

int main(void){
	char fileName[MAX_NAME];

	printf("Enter file name of file to be tailed\n");
	scanf("%s", fileName);

	FILE* fp = fopen(fileName, "rb");
	if(!fp){
		printf("Error opening file %s\n", fileName);
		exit(EXIT_FAILURE);
	}
	fseek(fp, 0L, SEEK_END);

	unsigned int nNewLine = 0;
	unsigned long i, last = ftell(fp);
	for(i = 1L; i <= last && nNewLine <= LINES; i++){
		fseek(fp, -1 * i, SEEK_END);
		if(getc(fp) == '\n')
			nNewLine++;
	}

	if(nNewLine <= LINES){
		printf("Displaying entire file contents\n\n");
		fseek(fp, 0L, SEEK_SET);
	}
	char output[BUF_SIZE] = {0};
	while(fgets(output, BUF_SIZE, fp) != NULL)
		fputs(output, stdout);

	fclose(fp);
	return 0;
}
