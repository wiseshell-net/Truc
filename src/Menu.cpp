/*
 * Menu.cpp
 *
 *  Created on: 4 de nov. 2021
 *      Author: antonialoy
 */

#include "Menu.h"
#include <iostream>

void Menu::StartMenu() {
	// TODO: Handle menu correctly
	Menu::Init();
}

void Menu::Init() {
	// TODO: Start with an array and add options
	std::cout <<  "Benvingut a truc!"  << std::endl;
}

void Menu::Options() {
	// TODO: Start with an array and add options
	std::cout << "Opcions" << std::endl;
}

void Menu::Credits() {
	// TODO: Start with an array and add options
	std::cout << "Crèdits" << std::endl;
}

void Menu::Quit() {
	std::cout << "Sortint del joc" << std::endl;
}
