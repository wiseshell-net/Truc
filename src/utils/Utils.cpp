/*
 * Utils.cpp
 *
 *  Created on: 26 de jul. 2021
 *      Author: antonialoy
 */

#include "Utils.h"
#include <iostream>
#include <cctype>
#include <string>
#include <vector>
using namespace std;

char GetCharacter(const char *prompt, const char *error) {
	const int IGNORE_CHARS = 256;
	char input;
	bool inputFailure;

	do {

		inputFailure = false;
		cout << prompt;

		cin >> input;

		if (cin.fail()) {
			cin.ignore(256, '\n');
			cin.clear();
			cout << error << endl;
			inputFailure = true;
		} else {
			cin.ignore(256, '\n');
			if (isalpha(input)) {
				input = tolower(input);
			} else {
				cout << error << endl;
				inputFailure = true;
			}
		}

	} while (inputFailure);

	return input;
}

char GetCharacter(const char *prompt, const char *error,
		const char validInput[], int validInputLength) {
	const int IGNORE_CHARS = 256;
	char input;
	bool inputFailure = false;

	do {

		cout << prompt;
		cin >> input;

		if (cin.fail()) {
			cin.ignore(256, '\n');
			cin.clear();
			cout << error << endl;
			inputFailure = true;
		} else {
			cin.ignore(256, '\n');

			input = tolower(input);

			for (int i = 0; i < validInputLength; ++i) {
				if (input == validInput[i]) {
					return input;
				}
			}

			cout << error << endl;
			inputFailure = true;
		}

	} while (inputFailure);

	return ' ';
}

// TODO implement this
/*char GetCharacter(const char *prompt, const char *error, std::vector<std::string> validInput) {
	const int IGNORE_CHARS = 256;
	char input;
	bool inputFailure = false;

	do {

		cout << prompt;
		cin >> input;

		if (cin.fail()) {
			cin.ignore(256, '\n');
			cin.clear();
			cout << error << endl;
			inputFailure = true;
		} else {
			cin.ignore(256, '\n');

			input = tolower(input);


			for (int i = 0; i < validInput.size(); ++i) {
				if (input.compare(validInput.at(i))) == 0) {
					return input;
				}
			}

			cout << error << endl;
			inputFailure = true;
		}

	} while (inputFailure);

	return ' ';
}*/

void ClearScreen() {
	cout << "Clearing Screen..." << endl;
	system("clear");
}

void WaitForKeyPress()
{
#ifdef __WINDOWS__
	system("pause");
#endif

#ifdef __MACOSX__
	system("read -n 1 -s -p \"Press any key to continue...\"; echo");
#endif
}
