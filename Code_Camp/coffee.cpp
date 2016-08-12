#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
	#define CLEAR_SCR system("clear")
#elif defined __WIN32
	#define CLEAR_SCR system("cls")
#endif

typedef struct{
	const char* name;
	const int size;
	const float cost;
	int tCups;
} cupSize_t;

void Display_Help(void);
void Store_Menu_Display(void);
void Store_Run(char input, cupSize_t menu[], size_t menuLen);

int main(int argc, char* argv[]){
	if(argc > 1 && strcmp(argv[1], "-help") == 0)
		Display_Help();

	char input;
	cupSize_t coffeeMenu[] = {
		{"Small", 9, 1.75f, 0},
		{"Medium", 12, 1.90f, 0},
		{"Large", 15, 2.00f, 0}
	};

	while(1){
		Store_Menu_Display();
		scanf(" %c", &input);
		Store_Run(input, coffeeMenu, sizeof(coffeeMenu)/sizeof(coffeeMenu[0]));
		printf("Press any key to continue\n");
		getchar();
		getchar();
		CLEAR_SCR;
	}

	return 0;
}

/* Display_Help:  writes help message to stdout */
void Display_Help(void){
	printf("This is the coffee shop program.  ");
	printf("You may purchase coffee or view sales statistics.  ");
	printf("Use the menu to guide you through the options.\n");
}

/* Store_Menu_Display:  writes the menu of user options */
void Store_Menu_Display(void){
	printf("Welcome to the Coffee Shop\n");
	printf("Please make a selection\n");
	printf("a. Buy Coffee\n");
	printf("b. Show the total number of cups of each size sold\n");
	printf("c. Show the total amount of coffee sold\n");
	printf("d. Show the total money made\n");
	printf("q. Quit\n");
}

void Buy(cupSize_t menu[], int* tCoffee, float* tMoney, size_t sMenu);
inline void ShowCups(cupSize_t menu[], size_t sMenu);
inline void ShowCoffee(int tCoffee);
inline void ShowMoney(float tMoney);

/* Store_Run:  performs the action listed in the store menu chosen by user */
void Store_Run(char input, cupSize_t menu[], size_t menuLen){
	static int tCoffee;
	static float tMoney;

	switch(input){
	case 'a':
		Buy(menu, &tCoffee, &tMoney, menuLen);
		break;
	case 'b':
		ShowCups(menu, menuLen);
		break;
	case 'c':
		ShowCoffee(tCoffee);
		break;
	case 'd':
		ShowMoney(tMoney);
		break;
	case 'q':
		printf("Goodbye!\n");
		exit(EXIT_SUCCESS);
	default:
		printf("%c is not a valid selection\n", input);
	}
}

/* Buy:  presents menu of available coffee choices and performs purchase transaction */
void Buy(cupSize_t menu[], int* tCoffee, float* tMoney, size_t menuLen){
	printf("Select from the following coffee options to purchase:\n");
	printf("Selection    Size(oz)   Cost\n");
	int sel = 0;

	int i;
	for(i = 0; i < menuLen; i++)
		printf("%d. %s\t%d\t$%.2f\n", sel + i, menu[i].name, menu[i].size, menu[i].cost);

	int input;
	scanf("%d", &input);

	int delta = input - sel;
	if(delta >= 0 && delta < menuLen){
		printf("You have purchased a %s coffee for $%.2f\n", menu[delta].name, menu[delta].cost);
		menu[delta].tCups++;
		*tCoffee += menu[delta].size;
		*tMoney += menu[delta].cost;
	}
	else
		printf("Invalid selection\n");
}

/* ShowCups:  writes the number sold of each coffee size to stdout */
inline void ShowCups(cupSize_t menu[], size_t menuLen){
	printf("Cups sold:\n");
	int i;
	for(i = 0; i < menuLen; i++)
		printf("%d %s\n", menu[i].tCups, menu[i].name);
}

/* ShowCoffee:  writes the total amount of coffee sold to stdout */
inline void ShowCoffee(int tCoffee){
	printf("%d ounces of coffee have been sold\n", tCoffee);
}

/* ShowMoney:  writes the total amount of money made to stdout */
inline void ShowMoney(float tMoney){
	printf("$%.2f has been made\n", tMoney);
}
