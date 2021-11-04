/*
 * Menu.cpp
 *
 *  Created on: 4 de nov. 2021
 *      Author: antonialoy
 */

#include "Menu.h"
#include <iostream>
#include <string>
#include <vector>
#include "utils/Utils.h"

/* Aquí afegirem tots els menús amb totes les opcions */
void Menu::Setup(std::vector<std::string> &init,
		std::vector<std::string> &options,
		std::vector<std::string> &gameSelection,
		std::vector<std::string> &credits) {
	// Init (Inici)
	init.push_back("COMENÇAR");
	init.push_back("MULTIJUGADOR");
	init.push_back("CRÈDITS");
	init.push_back("SORTIR");
	// Options
	options.push_back("OPCIONS");
	// Game Selection
	gameSelection.push_back("TRUC");
	// Credits
	credits.push_back("CREDITS");
}

/* When the game is finished, ask the user if it wants to play again */
/*bool SelectInit(std::vector<std::string> &init) {
	char response = GetCharacter("Selecciona un dels ítems del menú: ", "ERROR",
			init, 2);

	return response == 'y';
}*/

void Menu::Init(std::vector<std::string> &init) {
	// TODO: Implement this
	//do {
		std::cout << "Benvingut a truc!" << std::endl;
		for (int i = 0; i < init.size(); i++) {
			std::cout << init.at(i) << std::endl;
		}
	//} while (SelectInit(std::vector < std::string > init));
}

void Menu::Options(std::vector<std::string> &options) {
	// TODO: Start with an array and add options
	std::cout << "Opcions" << std::endl;
}

void Menu::GameSelection(std::vector<std::string> &gameSelection) {
	// TODO: Start with an array and add options
	std::cout << "Opcions" << std::endl;
}

void Menu::Credits(std::vector<std::string> &credits) {
	// TODO: Start with an array and add options
	std::cout << "Crèdits" << std::endl;
}

void Menu::Quit() {
	std::cout << "Sortint del joc" << std::endl;
}

void Menu::StartMenu() {

	// Declare variables
	std::vector<std::string> init;
	std::vector<std::string> options;
	std::vector<std::string> gameSelection;
	std::vector<std::string> credits;

	// Setup
	Menu::Setup(init, options, gameSelection, credits);

	// TODO: Handle menu correctly
	Menu::Init(init);
}
