/* Compile with FH.cpp */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "FH.h"

#define MAXLINE 100

#define QUESTIONS 20
#define POINTS_PER_QUESTION 2
#define MAX_SCORE (QUESTIONS * POINTS_PER_QUESTION)

char corrAns[QUESTIONS + 1];
inline void GetAnswers(FILE*);

typedef struct{
	char answer[QUESTIONS + 1];
	char* studID;
	float score;
} studRec_ts;
void StudRec_Parse(char*, studRec_ts*, FILE*);
void StudRec_Grade(studRec_ts*);
inline void StudRec_Free(studRec_ts*, int);
inline void StudRec_Write(const studRec_ts, FILE*);

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Usage: %s input_filename number_of_students\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE* file[NUM_FILES];
	if(FH_OpenFiles(file, argv[1]) == FILE_FAILURE){
		printf("Error opening files.  Check that filename %s is correct "
			"and that input file exists\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	int nStudents = atoi(argv[2]);
	char buffer[MAXLINE];
	studRec_ts record[nStudents];

	GetAnswers(file[INPUT]);

	for(int i = 0; i < nStudents; i++){
		fgets(buffer, MAXLINE, file[INPUT]);
		StudRec_Parse(buffer, &record[i], file[INPUT]);
		StudRec_Grade(&record[i]);
		StudRec_Write(record[i], file[OUTPUT]);
	}

	StudRec_Free(record, nStudents);
	FH_CloseFiles(file);

	return 0;
}

inline void GetAnswers(FILE* input){
	fscanf(input, " %s ", corrAns);
}

#define SKIP_WHITE_SPACE(s) while(isspace(*s)) s++
#define MARK_ID_END(s) while(isalnum(*s)) *s++; *s++ = '\0'
void StudRec_Parse(char* buffer, studRec_ts* record, FILE* input){
	char* s = buffer;

	SKIP_WHITE_SPACE(s);
	MARK_ID_END(s);

	record->studID = (char*) calloc(strlen(buffer + 1), sizeof(char));
	strcpy(record->studID, buffer);
	*(s + 20) = '\0';
	strcpy(record->answer, s);
}

void StudRec_Grade(studRec_ts* record){
	record->score = 0.0f;
	for(int i = 0; i < QUESTIONS; i++)
		if(record->answer[i] != ' ')
			record->score = record->answer[i] == corrAns[i] ? record->score + 2.0f : record->score + 1.0f;
	record->score = record->score / (float)MAX_SCORE * 100.0f;
}

inline void StudRec_Free(studRec_ts* record, int nStudents){
	for(int i = 0; i < nStudents; i++)
		free(record[i].studID);
}

char AssignGrade(float score){
	if(score < 60.0f)
		return 'F';
	else if(score < 70.0f)
		return 'D';
	else if(score < 80.0f)
		return 'C';
	else if(score < 90.0f)
		return 'B';
	else
		return 'A';
}

inline void StudRec_Write(studRec_ts record, FILE* output){
	fprintf(output, "Student: %s Answers: %s Score: %.2f Grade: %c\n",
			record.studID, record.answer, record.score, AssignGrade(record.score));
}
