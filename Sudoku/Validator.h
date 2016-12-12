#ifndef VAL_H
#define VAL_H

class Validator{
	private:
		//String pointing to the puzzle number
		const char* puzzleNumber;

		//String pointing to the puzzle board
		const char* puzzle;

		//Sum of all digit characters in a valid row/col/block area
		const unsigned MAGIC_NUM;

		//Status of the puzzle, EXXX indicates an error in ROW/COL/BLK
		enum Status{
			VALID, EROW, ECOL, EBLK
		} status;

		//Specific row/col/blk number where the error was found
		unsigned eArea;

		/*Pointer to array of count of digit chars in an error area
			ex: present -> 0111121110
			This would indicate that '5' is present twice while '9' ommitted */
		unsigned* present;

		//Pointer to the output message
		char* msg;

		/* Each Validation method calls the CheckArea method */
		bool ValidateRows();		//Validates all rows of the puzzle
		bool ValidateCols();		//Validates all colums of the puzzle
		bool ValidateBlks();		//Validates all blocks of the puzzle

		/* CheckArea validates the input area passed to it by the ValidateXxxx methods */
		bool CheckArea(const char*, const char*, const char*, unsigned);

		/* GetError builds the present array with the input area.  Should only be called
			if CheckArea returns false and with the same arguments */
		void GetError(const char*, const char*, const char*, unsigned);

		char* CreateValMsg();		//Creates validation message

	public:
		Validator(const char*, const char*);	//Sets up the validator on the input puzzle
		~Validator();			//Deletes memory allocated by the Validator
		char* Validate();		//Performs validation of the puzzle
};

#endif
