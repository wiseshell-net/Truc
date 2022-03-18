/*
 * game_defs.hpp
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

#ifndef _GAME_DEFS_HPP
#define _GAME_DEFS_HPP


/* overall common values */

#define GAME_NAME                   "Scuba Max"

#define GAME_CANVAS_WIDTH           2000
#define GAME_CANVAS_HEIGHT          1000

#define GAME_VIEWPORT_WIDTH         640
#define GAME_VIEWPORT_HEIGHT        480

#define GAME_DRAWINGS_DELAY_MS      30

#define GAME_BACKGROUND_COLOR       Color (0x000088ff)

#define GAME_MUSIC_VOLUME           MIX_MAX_VOLUME / 2
#define GAME_MUSIC_LOOPS            -1
#define GAME_MUSIC_FADE_IN_DELAY    500
#define GAME_MUSIC_FADE_OUT_DELAY   500

#define GAME_TITLE_TEXT             GAME_NAME
#define GAME_TITLE_FONT             FONT_FOR_TITLE                      /* see data/font_enum.dat */
#define GAME_TITLE_COLOR            Color (0x88ddffff)

#define GAME_TIP_TEXT               "Press spacebar to continue"
#define GAME_TIP_FONT               FONT_FOR_TIP
#define GAME_TIP_COLOR              Color (0xd2d2d2d2)

#define GAME_TEXT_COLOR_HI          Color (0xccddffff)
#define GAME_TEXT_COLOR_LO          Color (0xffee00ff)


/* screen_game_play.cpp */

#define GAME_PAUSE_TEXT     "GAME PAUSED"
#define GAME_PAUSE_FONT     FONT_FOR_PAUSE
#define GAME_PAUSE_COLOR    Color (0xffff66ff)


/* user_info.hpp */

#define GAME_USER_INFO_FONT         FONT_FOR_USER_INFO
#define GAME_USER_INFO_COLOR        White
#define GAME_USER_INFO_DELAY        1000
#define GAME_USER_INFO_ANCHOR_X     game.window_center.x
#define GAME_USER_INFO_ANCHOR_Y     game.window_center.y
#define GAME_USER_INFO_ANCHORAGE    ANCHOR_CENTER


#endif /* _GAME_DEFS_HPP */
