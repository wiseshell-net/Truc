/*
 * screens.hpp
 *
 * Copyright 2018 Raphaël SEBAN <raphael.seban@laposte.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#ifndef _SCREENS_HPP
#define _SCREENS_HPP

#include <string>

#include <SDL.h>

#include "event.hpp"
#include "game_part.hpp"
#include "random.hpp"
#include "render.hpp"
#include "screen_defs.hpp"
#include "user_info.hpp"

#include "screen_credits.hpp"
#include "screen_game_play.hpp"
#include "screen_intro.hpp"
#include "screen_rules.hpp"


struct Screens : public GamePart
{
public:

    ScreenCredits *     screen_credits;
    ScreenGamePlay *    screen_game_play;
    ScreenIntro *       screen_intro;
    ScreenRules *       screen_rules;

public:

    Screens (Game& game);

    virtual ~Screens ();

    virtual bool initializeAll ();

    virtual ScreenEnum fromCommonEvent (
        const SDL_Event& event,
        const ScreenEnum& next_screen
    );

    virtual ScreenEnum fromEvents (const ScreenEnum& next_screen);

    virtual ScreenEnum switchTo (const ScreenEnum& screen);

protected:

    virtual ScreenEnum dummyScreen (
        const std::string& title,
        const std::string& tip = ""
    );

    virtual ScreenEnum screenGameOver ();

    virtual ScreenEnum screenLevelComplete ();

    virtual ScreenEnum screenQuit ();
};


#endif /* _SCREENS_HPP */
