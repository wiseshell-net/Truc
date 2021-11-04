/*
 * Game.h
 *
 *  Created on: 4 de nov. 2021
 *      Author: antonialoy
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include <string>
#include <stdint.h>

class Game
{
public:
	virtual ~Game(){}
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual const std::string& GetName() const = 0;
};

#endif /* SRC_GAME_H_ */
