/*
 * screen_intro.cpp
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

#include "screen_intro.hpp"
#include "screens.hpp"

#include "geometry.hpp"


ScreenIntro::ScreenIntro (Game& game) :
ScreenBase (game)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


ScreenIntro::~ScreenIntro ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


ScreenEnum
ScreenIntro::doDrawings ()
{
    DEBUG_FUNCTION_ENTER;

    Render::clear (game.renderer, game.background_color);

    m_title_sprite.draw (game.renderer);

    m_sprites.draw (game.renderer);

    m_tip_sprite.draw (game.renderer);

    game.user_info->draw (game.renderer);

    Render::display (game.renderer);

    SDL_Delay (GAME_DRAWINGS_DELAY_MS);

    DEBUG_FUNCTION_EXIT;

    return SCREEN_DEFAULT;
}


ScreenEnum
ScreenIntro::doEvents ()
{
    DEBUG_FUNCTION_CALL;

    return game.screens->fromEvents (SCREEN_RULES);
}


ScreenEnum
ScreenIntro::doLogic ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;

    return SCREEN_DEFAULT;
}


bool
ScreenIntro::initialize ()
{
    DEBUG_FUNCTION_ENTER;

    m_title_sprite.setText (
        game.renderer,
        GAME_TITLE_TEXT,
        game.getFont (FONT_FOR_GAME_NAME),
        GAME_TITLE_COLOR
    );

    m_title_sprite.setPosition (
        game.window_center.x,
        game.window_size.h / 7,
        ANCHOR_CENTER
    );

    m_tip_sprite.setText (
        game.renderer,
        GAME_TIP_TEXT,
        game.getFont (GAME_TIP_FONT),
        GAME_TIP_COLOR

    );

    m_tip_sprite.setPosition (
        game.window_center.x,
        game.window_size.h - 20,
        ANCHOR_SOUTH
    );

    const char * const menus [] = {
        "Arrow keys: player move",
        "Spacebar: player action",
        "'C': Credits - contributors",
        "'H': Help - game rules",
        "'F': Toggle fullscreen mode",
        "'P': Pause/resume game",
        "'M': Pause/resume music",
        "'S': Pause/resume sound",
        "'Q'/'X'/'Esc': Quit game"
    };

    const ArraySize n_menus = ARRAY_SIZE (menus);

    m_sprites.clear ();

    m_sprites.resize (n_menus);

    for (ArrayIndex i = 0; i < n_menus; i++)
    {
        m_sprites[i].setText (
            game.renderer,
            menus [i],
            game.getFont (FONT_FOR_MENU),
            (i % 2) ? GAME_TEXT_COLOR_HI : GAME_TEXT_COLOR_LO
        );

        m_sprites[i].setPosition (
            game.window_center.x / 2.25f,
            game.window_center.y - 5 + 28 * (i + 1 - n_menus / 2),
            ANCHOR_NORTH_WEST
        );
    }

    DEBUG_FUNCTION_EXIT;

    return true;
}


ScreenEnum
ScreenIntro::onExit (ScreenEnum screen)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;

    return screen;
}


ScreenEnum
ScreenIntro::reset ()
{
    DEBUG_FUNCTION_ENTER;

    game.playMusic (MUSIC_INTRO);

    game.user_info->reset ();

    game.user_info->setAnchoragePoint (
        game.window_center.x,
        game.window_center.y / 2 + 5,
        ANCHOR_CENTER
    );

    game.user_info->setColor (Color (0xd2d2d2ff));

    game.user_info->setFontIndex (FONT_FOR_TIP);

    DEBUG_FUNCTION_EXIT;

    return SCREEN_DEFAULT;
}

