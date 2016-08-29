#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "list.h"
#include "item.h"

#define MAX_LINE 1000

FILE* fin, * fout;

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Usage: %s filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fin = fopen(argv[1], "r");
	char* outFileName = (char*)calloc(strlen(argv[1] + 5), sizeof(char));
	strcat(outFileName, argv[1]);
	strcat(outFileName, ".out");
	fout = fopen(outFileName, "w");
	free(outFileName);
	if((fin && fout) == 0)
		exit(EXIT_FAILURE);

	char line[MAX_LINE] = {0};
	char* word = NULL;

	while(fgets(line, MAX_LINE, fin)){
		while((word = Parser_GetWords(line, strlen(line))))
			if(List_AddEntry(word) == 0)
				printf("Error: could not add %s.  Memory could not be allocated\n", word);
		Parser_Reset();
	}
	List_Traverse(Item_Display);
	Item_ItemTotals();

	List_Delete();
	
	fclose(fin);
	fclose(fout);

	printf("Word count complete.\nCheck current directory for output file\n<input_file_name.out>\n");
	return 0;
}
