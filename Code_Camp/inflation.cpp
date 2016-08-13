#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FH.h"

#define PRICE_LISTINGS 3

typedef struct{
	float price[PRICE_LISTINGS];
	float inf[PRICE_LISTINGS - 1];
} InfCalc_ts;

int InfCalc_Read(InfCalc_ts*, FILE*);
inline void InfCalc_Calculate(InfCalc_ts*);
inline void InfCalc_Write(InfCalc_ts, FILE*);

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Useage:  %s input_filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE* file[NUM_FILES];
	if(FH_OpenFiles(file, argv[1]) == FILE_FAILURE){
		printf("Error opening files.  Check that filename %s is correct "
			"and that input file exists\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	
	InfCalc_ts curItem = {0};
	while(InfCalc_Read(&curItem, file[INPUT]) == PRICE_LISTINGS){
		InfCalc_Calculate(&curItem);
		InfCalc_Write(curItem, file[OUTPUT]);
	}

	FH_CloseFiles(file);

	return 0;
}

int InfCalc_Read(InfCalc_ts* a, FILE* fp){
	int retval = 0;

	int i;
	for(i = 0; i < PRICE_LISTINGS; i++)
		retval += fscanf(fp, "%f", &a->price[i]);
	
	return retval;
}

inline void InfCalc_Calculate(InfCalc_ts* a){
	int i;
	for(i = 0; i < PRICE_LISTINGS - 1; i++)
		if(a->price[i + 1]){
			a->inf[i] = (a->price[i + 1] - a->price[i]) / a->price[i + 1];
			if(a->inf[i] < 0.0f)
				a->inf[i] *= -1.0f;
		}
		else{
			printf("Bad input; 0 price listing results in division by 0\n");
			a->inf[i] = -1.0f;
			return;
		}
}

inline void InfCalc_Write(InfCalc_ts a, FILE* fp){
	if(a.inf[0] < 0.0f || a.inf[1] < 0.0f){
		fprintf(fp, "Bad price input\n");
		return;
	}
	fprintf(fp, "Current price is $%.2f which is %s\n", a.price[0],
		a.inf[0] > a.inf[1] ? "increasing" : a.inf[0] < a.inf[1] ? "decreasing" : "constant");
}
