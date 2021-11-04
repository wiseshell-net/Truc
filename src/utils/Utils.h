/*
 * Utils.h
 *
 *  Created on: 26 de jul. 2021
 *      Author: antonialoy
 */

#ifndef UTILS_H_
#define UTILS_H_

char GetCharacter(const char *prompt, const char *error);
char GetCharacter(const char *prompt, const char *error,
		const char validInput[], int validInputLength);
void ClearScreen();

#endif /* UTILS_H_ */
