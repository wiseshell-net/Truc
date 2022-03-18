/*
 * screen_rules.cpp
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

#include "screen_rules.hpp"
#include "screens.hpp"

#include "geometry.hpp"


ScreenRules::ScreenRules (Game& game) :
ScreenBase (game)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


ScreenRules::~ScreenRules ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


ScreenEnum
ScreenRules::doDrawings ()
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
ScreenRules::doEvents ()
{
    DEBUG_FUNCTION_CALL;

    return game.screens->fromEvents (SCREEN_PLAY);
}


ScreenEnum
ScreenRules::doLogic ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;

    return SCREEN_DEFAULT;
}


bool
ScreenRules::initialize ()
{
    DEBUG_FUNCTION_ENTER;

    m_title_sprite.setText (
        game.renderer,
        "Game Rules",
        game.getFont (GAME_TITLE_FONT),
        GAME_TITLE_COLOR
    );

    m_title_sprite.setPosition (
        game.window_center.x,
        10,
        ANCHOR_NORTH
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

    const char * const texts [] = {
        "Help Maximilian in his quest for",
        "beauty and wonder.",
        "But beware, oxygen is rapidly",
        "exhausted while diving so far.",
        "Maybe some fish could help?",
        "Enjoy."
    };

    const ArraySize n_texts = ARRAY_SIZE (texts);

    m_sprites.clear ();

    m_sprites.resize (n_texts);

    for (ArrayIndex i = 0; i < n_texts; i++)
    {
        m_sprites[i].setText (
            game.renderer,
            texts [i],
            game.getFont (FONT_FOR_MENU),
            (i % 2) ? GAME_TEXT_COLOR_HI : GAME_TEXT_COLOR_LO
        );

        m_sprites[i].setPosition (
            game.window_center.x / 4,
            game.window_center.y + 20 + 32 * (i - n_texts / 2),
            ANCHOR_WEST
        );
    }

    DEBUG_FUNCTION_EXIT;

    return true;
}


ScreenEnum
ScreenRules::onExit (ScreenEnum screen)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;

    return screen;
}


ScreenEnum
ScreenRules::reset ()
{
    DEBUG_FUNCTION_ENTER;

    game.playMusic (MUSIC_RULES);

    game.user_info->reset ();

    game.user_info->setAnchoragePoint (
        game.window_center.x,
        game.window_center.y / 2 - 10,
        ANCHOR_CENTER
    );

    DEBUG_FUNCTION_EXIT;

    return SCREEN_DEFAULT;
}

