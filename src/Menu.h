/*
 * Menu.h
 *
 *  Created on: 4 de nov. 2021
 *      Author: antonialoy
 */

#ifndef SRC_MENU_H_
#define SRC_MENU_H_

class Menu
{
public:
	// Constructor
	//Menu();

	// Start Menu
	void StartMenu();

private:
	// Menu Screen
	void Init();

	// Options Screen
	void Options();

	// Game Selection Screen
	void GameSelection();

	// Credits Screen
	void Credits();

	// Quit Screen
	void Quit();
};

#endif /* SRC_MENU_H_ */
