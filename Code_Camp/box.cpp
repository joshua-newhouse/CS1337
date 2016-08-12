#include <stdio.h>
#include <math.h>

/* Volume:  calculates box volume given cut length s, width w, and cardboard area a */
#define Volume(s, w, a) ((a / w - 2 * s) * (w - 2 * s) * s)

typedef struct{
	unsigned int area;
	unsigned int length;
	unsigned int width;
	unsigned int s;
	unsigned int volume;
} box_t;

inline void Box_Display(const box_t box);
unsigned int Box_MaxVol(box_t* box);

int main(void){
	box_t box = {0};

	printf("Enter cardboard area: ");
	scanf("%u", &box.area);

	if(Box_MaxVol(&box) != box.area){
		printf("Max volume not possible with integral box dimensions for given area.\n");
		printf("Area displayed is largest area less than input which yields integral dimensions.\n");
	}

	Box_Display(box);

	return 0;
}

/* Box_Display:  writes cardboard and box dimensions to stdout */
inline void Box_Display(const box_t box){
	printf("cardboard area: %u\n", box.length * box.width);
	printf("cardboard length: %u\n", box.length);
	printf("cardboard width: %u\n", box.width);
	printf("cut length: %u\n", box.s);
	printf("box length: %u\n", box.length - 2 * box.s);
	printf("box width: %u\n", box.width - 2 * box.s);
	printf("box height: %u\n", box.s);
	printf("max volume: %u\n", box.volume);
}

/* Box_MaxVol:  calculates maximum integral box volume and dimensions given a cardboard area;
		returns length * width of possibly updated cardboard area */
unsigned int Box_MaxVol(box_t* box){
	int w, s;
	for(w = 2; w <= sqrt(box->area); w++){
		for(s = 1; s * 2 < w; s++){
			int v;
			if(box->volume < (v = Volume(s, w, box->area))){
				box->volume = v;
				box->width = w;
				box->s = s;
			}
		}
	}

	int side;
	if((side = box->area / box->width) >= box->width)
		box->length = side;
	else{
		box->length = box->width;
		box->width = side;
	}

	return box->length * box->width;
}
