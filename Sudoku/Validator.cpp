#include <new>
#include <string.h>
#include "Validator.h"

/* SUM_CHAR is the sum of all the integer values of the specified characters */
const unsigned SUM_CHAR = '9' + '8' + '7'
			+ '6' + '5' + '4'
			+ '3' + '2' + '1';

/* NUMBER is the number of rows and columns on a game board */
const unsigned NUMBER = 9;

/* MAX_MSG is the maximum length of the message to be written to output */
const unsigned MAX_MSG = 59;

/* Constructor:  Receives the puzzle number (np) and puzzle (p) and initializes
	the members of the Validator class.
	Allocates memory for the output message (msg) */
Validator::Validator(const char* np, const char* p)	:
	puzzleNumber(np), puzzle(p), MAGIC_NUM(SUM_CHAR), status(VALID), eArea(0), present(NULL){
	msg = new char[MAX_MSG]();
}

/* Destructor:  Deallocates memory used for msg and present members */
Validator::~Validator(){
	delete[] msg;
	delete[] present;
}

/* Validate:  Public method that validates the entire puzzle.  It calls
	ValidateRows, ValidateCols, and ValidateBlks in that order.  If a failure
	is detected by one of these three methods validation terminates.
	CreateValMsg is called at the termination of this method and a pointer to
	the message is returned */
char* Validator::Validate(){
	if(!ValidateRows())
		goto RETURN_MESSAGE;
	if(!ValidateCols())
		goto RETURN_MESSAGE;
	if(!ValidateBlks())
		goto RETURN_MESSAGE;
	RETURN_MESSAGE:
	return CreateValMsg();
}

/* ValidateRows: Private method that validates each row of the puzzle.  This method loops
	through each row calling the CheckArea method.  If an error is detected by CheckArea,
	eArea is set to the current row, status is set to EROW and GetError is called.
	Returns true if no errors; false otherwise */
bool Validator::ValidateRows(){
	for(unsigned row = 0; row < NUMBER; row++){
		const char* segment = puzzle + row * NUMBER;
		if(!CheckArea(segment, segment + NUMBER / 3, segment + 2 * NUMBER / 3, 1)){
			eArea = row + 1;
			status = EROW;
			GetError(segment, segment + NUMBER / 3, segment + 2 * NUMBER / 3, 1);
			return false;
		}
	}
	return true;
}

/* ValidateCols: Private method that validates each column of the puzzle.  This method loops
	through each column calling the CheckArea method.  If an error is detected by CheckArea,
	eArea is set to the current column, status is set to ECOL and GetError is called.
	Returns true if no errors; false otherwise */
bool Validator::ValidateCols(){
	for(unsigned col = 0; col < NUMBER; col++){
		const char* segment = puzzle + col;
		if(!CheckArea(segment, segment + 3 * NUMBER, segment + 6 * NUMBER, NUMBER)){
			eArea = col + 1;
			status = ECOL;
			GetError(segment, segment + 3 * NUMBER, segment + 6 * NUMBER, NUMBER);
			return false;
		}
	}
	return true;
}

/* ValidateBlks: Private method that validates each block of the puzzle.  This method loops
	through each block calling the CheckArea method.  If an error is detected by CheckArea,
	eArea is set to the current block, status is set to EBLK and GetError is called.
	Returns true if no errors; false otherwise
	Block numbering:
			123
			456
			789								*/
bool Validator::ValidateBlks(){
	for(unsigned rBlk = 0; rBlk < NUMBER / 3; rBlk++)
		for(unsigned cBlk = 0; cBlk < NUMBER / 3; cBlk++){
			const char* segment = puzzle + NUMBER / 3 * (NUMBER * rBlk + cBlk);
			if(!CheckArea(segment, segment + NUMBER, segment + 2 * NUMBER, 1)){
				eArea = 3 * rBlk + cBlk + 1;
				status = EBLK;
				GetError(segment, segment + NUMBER, segment + 2 * NUMBER, 1);
				return false;
			}
		}
	return true;
}

/* CheckArea:  Private method that tests the input area's equality to the MAGIC_NUM.  It
	receives three pointers to characters and an offset (NUMBER for column checking,
	1 otherwise).  It loops through NUMBER / 3 times adding each character pointed to
	to a cummulative sum.  After loop terminates it checks the sum against the MAGIC_NUM.
	If sum != the MAGIC_NUM then ther is an error and returns false.
	Returns true if sum == MAGIC_NUM */
bool Validator::CheckArea(const char* a, const char* b, const char* c, unsigned offset){
	unsigned sum = 0;
	for(unsigned i = 0; i < NUMBER / 3; i++)
		sum += *(a + i * offset) + *(b + i * offset) + *(c + i * offset);
	if(sum != MAGIC_NUM)
		return false;
	return true;
}

/* GetError:  Private method that finds the duplicate and omitted characters in the input area.
	It receives the same parameters as CheckArea and is meant to be used in tandem with.
	If CheckArea finds an error in a given area then this function should be called on the
	same area to find the specific errors.
	Allocates memory for present array which counts how many times each character is present
	in the input area */
void Validator::GetError(const char* a, const char* b, const char* c, unsigned offset){
	present = new unsigned[NUMBER + 1]();
	for(unsigned i = 0; i < NUMBER / 3; i++){
		(*(present + (*(a + i * offset) - '0')))++;
		(*(present + (*(b + i * offset) - '0')))++;
		(*(present + (*(c + i * offset) - '0')))++;
	}
}

/* CreateValMsg:  Private method that returns pointer to the output message.  This method creates
	and formats the output message based on hard coded formatting rules and the status of the
	puzzle */
char* Validator::CreateValMsg(){
	strcat(msg, puzzleNumber);
	for(char* c = msg + strlen(msg); c < msg + 10; c++)
		*c = ' ';
	if(!status){
		strcat(msg, "VALID");
		for(char* c = msg + strlen(msg); c < msg + 21; c++)
			*c = ' ';
	}
	else{
		strcat(msg, "INVALID");
		for(char* c = msg + strlen(msg); c < msg + 21; c++)
			*c = ' ';
		switch(status){
		case EROW:
			strcat(msg, "ROW");
			break;
		case ECOL:
			strcat(msg, "COL");
			break;
		case EBLK:
			strcat(msg, "BLK");
		}
		*(msg + strlen(msg)) = eArea + '0';
		strcat(msg, " ");
		strcat(msg, "DUPLICATES:");
		char* c = msg + strlen(msg);
		for(unsigned i = 1; i <= NUMBER; i++)
			if(*(present + i) > 1)
				*c++ = '0' + i;
		for(; c < msg + 42; c++)
			*c = ' ';
		strcat(msg, "OMITTED:");
		c = msg + strlen(msg);
		for(unsigned i = 1; i <= NUMBER; i++)
			if(*(present + i) < 1)
				*c++ = '0' + i;
	}
	return msg;
}
