/*
 * screen_defs.hpp
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

#ifndef _SCREEN_DEFS_HPP
#define _SCREEN_DEFS_HPP


enum ScreenEnum
{
    SCREEN_DEFAULT = 0,                 /* aka current running screen */
    SCREEN_INTRO,
    SCREEN_RULES,
    SCREEN_LEVEL_SELECT,
    SCREEN_PLAY,
    SCREEN_LEVEL_COMPLETE,
    SCREEN_ALL_DONE,
    SCREEN_GAME_OVER,
    SCREEN_CREDITS,
    SCREEN_QUIT,
};


#endif /* _SCREEN_DEFS_HPP */
