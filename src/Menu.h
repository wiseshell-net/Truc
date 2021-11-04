/*
 * Menu.h
 *
 *  Created on: 4 de nov. 2021
 *      Author: antonialoy
 */

#ifndef SRC_MENU_H_
#define SRC_MENU_H_

#include <string>
#include <vector>

class Menu
{
public:
	// Constructor
	//Menu();

	// Start Menu
	void StartMenu();

private:

	// Menu Setup
	void Setup(std::vector<std::string> &init, std::vector<std::string> &options, std::vector<std::string> &gameSelection, std::vector<std::string> &credits);

	// Menu Screen
	void Init(std::vector<std::string> &init);

	// Options Screen
	void Options(std::vector<std::string> &options);

	// Game Selection Screen
	void GameSelection(std::vector<std::string> &gameSelection);

	// Credits Screen
	void Credits(std::vector<std::string> &credits);

	// Quit Screen
	void Quit();
};

#endif /* SRC_MENU_H_ */
