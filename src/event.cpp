/*
 * event.cpp
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

#include "event.hpp"

#include "debug.hpp"


namespace Event
{

EventEnum
getCommonEvent (const SDL_Event& event)
{
    DEBUG_FUNCTION_CALL;

    switch (event.type)
    {
        case SDL_QUIT:
            return EVENT_QUIT;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
                case SDLK_RETURN:
                case SDLK_SPACE:
                    return EVENT_PLAY;

                case SDLK_F1:
                case SDLK_h:
                    return EVENT_HELP;

                case SDLK_F2:
                case SDLK_i:
                    return EVENT_INTRO;

                case SDLK_F3:
                case SDLK_c:
                    return EVENT_CREDITS;

                case SDLK_q:
                case SDLK_x:
                case SDLK_ESCAPE:
                    return EVENT_QUIT;

                case SDLK_F9:
                case SDLK_s:
                    return EVENT_TOGGLE_SOUND;

                case SDLK_F10:
                case SDLK_m:
                    return EVENT_TOGGLE_MUSIC;

                case SDLK_F11:
                case SDLK_f:
                    return EVENT_TOGGLE_FULLSCREEN;

                default:
                    break;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            return EVENT_PLAY;

        default:
            break;
    }

    return EVENT_NONE;
}

} /* namespace */

