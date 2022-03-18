/*
 * screen_base.cpp
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

#include "screen_base.hpp"

#include "debug.hpp"


ScreenBase::ScreenBase (Game& game) :
GamePart (game)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


ScreenBase::~ScreenBase ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


ScreenEnum
ScreenBase::mainLoop ()
{
    DEBUG_FUNCTION_ENTER;

    ScreenEnum screen = reset ();

    while (screen == SCREEN_DEFAULT && game.isEnabled ())
    {
        screen = doEvents ();

        if (screen != SCREEN_DEFAULT) break;

        screen = doLogic ();

        if (screen != SCREEN_DEFAULT) break;

        screen = doDrawings ();
    }

    DEBUG_FUNCTION_EXIT;

    return onExit (screen);
}


ScreenEnum
ScreenBase::onExit (ScreenEnum screen)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;

    return screen;
}


ScreenEnum
ScreenBase::run ()
{
    DEBUG_FUNCTION_CALL;

    return mainLoop ();
}

