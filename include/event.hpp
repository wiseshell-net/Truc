/*
 * event.hpp
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

#ifndef _EVENT_HPP
#define _EVENT_HPP

#include <SDL.h>


enum EventEnum
{
    EVENT_NONE = 0,
    EVENT_CREDITS,
    EVENT_HELP,
    EVENT_INTRO,
    EVENT_PLAY,
    EVENT_QUIT,
    EVENT_TOGGLE_FULLSCREEN,
    EVENT_TOGGLE_MUSIC,
    EVENT_TOGGLE_SOUND,
};


namespace Event
{

EventEnum getCommonEvent (const SDL_Event& event);

} /* namespace */


#endif /* _EVENT_HPP */
