/* Compile with FH.c */
#include <stdio.h>
#include <stdlib.h>
#include "FH.h"

#define MONTH_INDEX 13
#define HIGH 0
#define LOW 1

static const char* month[] = {	 NULL,
				 "January",
				 "February",
				 "March",
				 "April",
				 "May",
				 "June",
				 "July",
				 "August",
				 "September",
				 "October",
				 "November",
				 "December",
};

typedef struct{
	int year;
	int temps[MONTH_INDEX][2];
	int avgHigh, avgLow;
	int indexH, indexL;
} yearData_ts;

int yearData_getData(yearData_ts*, FILE*);
void yearData_Calculate(yearData_ts*);
void yearData_Write(const yearData_ts, FILE*);

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Usage: %s input_filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE* file[NUM_FILES];
	if(FH_OpenFiles(file, argv[1]) == FILE_FAILURE){
		printf("Error opening files.  Check that filename %s is correct "
			"and that input file exists\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	yearData_ts data = {0};

	int error_code;
	if(error_code = yearData_getData(&data, file[INPUT])){
		printf("Error:  malformed input on line %d.  Expected: hi lo\n", error_code);
		exit(EXIT_FAILURE);
	}

	yearData_Calculate(&data);
	yearData_Write(data, file[OUTPUT]);

	FH_CloseFiles(file);

	return 0;
}

int yearData_getData(yearData_ts* a, FILE* input){
	fscanf(input, " %d ", &a->year);

	int i;
	for(i = 1; i < MONTH_INDEX; i++){
		fscanf(input, " %d %d ", &a->temps[i][HIGH], &a->temps[i][LOW]);
		if(a->temps[i][LOW] > a->temps[i][HIGH])
			return i + 1;
	}
	
	return 0;
}

static int Average(int [][2], int);
static int IndexTemp(int [][2], int);

void yearData_Calculate(yearData_ts* a){
	a->avgHigh = Average(a->temps, HIGH);
	a->avgLow = Average(a->temps, LOW);
	a->indexH = IndexTemp(a->temps, HIGH);
	a->indexL = IndexTemp(a->temps, LOW);
}

void yearData_Write(const yearData_ts a, FILE* output){
	fprintf(output, "Year: %d\n"
			"Avg High: %d\n"
			"Avg Low: %d\n"
			"Highest: %d in %s\n"
			"Lowest: %d in %s\n",
			a.year, a.avgHigh, a.avgLow, a.temps[a.indexH][HIGH], month[a.indexH],
			a.temps[a.indexL][LOW], month[a.indexL]);
}

static int Average(int temp[][2], int sel){
	float sum = 0.0f;
	int i;
	for(i = 1; i < MONTH_INDEX; i++)
		sum += (float)temp[i][sel];
	return (int)(sum / 12.0f + 0.5f);
}

static int IndexTemp(int temp[][2], int sel){
	int ret_val[2] = {temp[1][sel], 1};
	int i;
	for(i = 1; i < MONTH_INDEX; i++)
		switch(sel){
		case LOW:
			if(temp[i][sel] < ret_val[0]){
				ret_val[1] = i;
				ret_val[0] = temp[i][sel];
			}
			break;
		case HIGH:
			if(temp[i][sel] > ret_val[0]){
				ret_val[1] = i;
				ret_val[0] = temp[i][sel];
			}
			break;
		}
	return ret_val[1];
}
