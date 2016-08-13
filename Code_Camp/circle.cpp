/* Compile with FH.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "FH.h"

#define PI 3.1416f
#define Distance(x1, y1, x2, y2) sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))
#define PT_COMP 4

typedef struct{
	float x, y;
} Point_ts;

typedef struct{
	Point_ts center;
	float radius;
	float diameter;
	float circumference;
	float area;
} Circle_ts;

inline int Circle_fReadLine(FILE*, Point_ts*, Point_ts*);
void Circle_NewCircle(Circle_ts*, Point_ts, Point_ts);
inline void Circle_fWriteLine(FILE*, Circle_ts);

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Usage:  %s input_filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE* file[NUM_FILES];
	if(FH_OpenFiles(file, argv[1]) == FILE_FAILURE){
		printf("Error opening files.  Check that filename %s is correct "
			"and that input file exists\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	Point_ts point1, point2;
	Circle_ts circle;
	while(Circle_fReadLine(file[INPUT], &point1, &point2) == PT_COMP){
		Circle_NewCircle(&circle, point1, point2);
		Circle_fWriteLine(file[OUTPUT], circle);
	}

	FH_CloseFiles(file);

	return 0;
}

inline int Circle_fReadLine(FILE* fp, Point_ts* pt1, Point_ts* pt2){
	return fscanf(fp, " ( %f , %f ) ( %f , %f ) ", &pt1->x, &pt1->y, &pt2->x, &pt2->y);
}

void Circle_NewCircle(Circle_ts* c, Point_ts ctr, Point_ts pt){
	c->center.x = ctr.x;
	c->center.y = ctr.y;
	c->radius = Distance(ctr.x, ctr.y, pt.x, pt.y);
	c->diameter = 2.0f * c->radius;
	c->circumference = 2.0f * PI * c->radius;
	c->area = PI * c->radius * c->radius;
}

inline void Circle_fWriteLine(FILE* fp, Circle_ts c){
	fprintf(fp,	"Center: (%.1f,%.1f)  "
			"Radius: %.1f  "
			"Diameter: %.1f  "
			"Circumference: %.1f  "
			"Area: %.1f\n",
		c.center.x, c.center.y, c.radius, c.diameter, c.circumference, c.area);
}
