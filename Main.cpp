#include <iostream>
#include "src/Menu.h"
#include "src/utils/Utils.h"

const char *INPUT_ERROR_STRING = "Input error! Please try again."; // TODO: Global variables are obnoxious, please fix.

/* Main is the game loop. While the game is running don't exit */
int main(int argc, char **argv) {
	bool WantToPlayAgain();
	Menu menu;
	do {
		menu.StartMenu();
	}while(WantToPlayAgain());
	return 0;
}

/* When the game is finished, ask the user if it wants to play again */
bool WantToPlayAgain() {
	const char validInputs[] = { 'y', 'n' };

	char response = GetCharacter("Would you like to play again? (y/n) ",
			INPUT_ERROR_STRING, validInputs, 2);

	return response == 'y';
}
