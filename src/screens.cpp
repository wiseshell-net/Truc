/*
 * screens.cpp
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

#include "screens.hpp"

#include "sprite.hpp"
#include "string_tools.hpp"


Screens::Screens (Game& game) :
GamePart (game),
screen_credits (nullptr),
screen_game_play (nullptr),
screen_intro (nullptr),
screen_rules (nullptr)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


Screens::~Screens ()
{
    DEBUG_FUNCTION_ENTER;

    delete screen_credits;
    delete screen_game_play;
    delete screen_intro;
    delete screen_rules;

    DEBUG_FUNCTION_EXIT;
}


bool
Screens::initializeAll ()
{
    DEBUG_FUNCTION_ENTER;

    Random::initialize ();

    screen_credits = new ScreenCredits (game);

    if (screen_credits == nullptr
        || !screen_credits->initialize ())
    {
        return false;
    }

    screen_game_play = new ScreenGamePlay (game);

    if (screen_game_play == nullptr
        || !screen_game_play->initialize ())
    {
        return false;
    }

    screen_intro = new ScreenIntro (game);

    if (screen_intro == nullptr
        || !screen_intro->initialize ())
    {
        return false;
    }

    screen_rules = new ScreenRules (game);

    if (screen_rules == nullptr
        || !screen_rules->initialize ())
    {
        return false;
    }

    DEBUG_FUNCTION_EXIT;

    return true;
}


ScreenEnum
Screens::dummyScreen (
        const std::string& title,
        const std::string& tip
    )
{
    DEBUG_FUNCTION_ENTER;

    ScreenEnum screen;

    Sprite title_sprite (
        game.renderer,
        title.empty () ? GAME_TITLE_TEXT : title,
        game.getFont (GAME_TITLE_FONT),
        GAME_TITLE_COLOR
    );

    title_sprite.setPosition (
        game.window_center.x,
        game.window_center.y - 10,
        ANCHOR_SOUTH
    );

    Sprite tip_sprite (
        game.renderer,
        tip.empty () ? GAME_TIP_TEXT : tip,
        game.getFont (GAME_TIP_FONT),
        GAME_TIP_COLOR
    );

    tip_sprite.setPosition (
        game.window_center.x,
        game.window_center.y + 10,
        ANCHOR_NORTH
    );

    game.user_info->reset ();

    game.user_info->setAnchoragePoint (
        game.window_center.x,
        game.window_center.y / 2,
        ANCHOR_CENTER
    );

    while (game.isEnabled ())
    {
        screen = fromEvents (SCREEN_PLAY);

        if (screen != SCREEN_DEFAULT) break;

        Render::clear (game.renderer, game.background_color);

        title_sprite.draw (game.renderer);

        tip_sprite.draw (game.renderer);

        game.user_info->draw (game.renderer);

        Render::display (game.renderer);

        SDL_Delay (GAME_DRAWINGS_DELAY_MS);
    }

    DEBUG_FUNCTION_EXIT;

    return screen;
}


ScreenEnum
Screens::fromCommonEvent (
        const SDL_Event& event,
        const ScreenEnum& next_screen
    )
{
    DEBUG_FUNCTION_CALL;

    switch (Event::getCommonEvent (event))
    {
        case EVENT_CREDITS:
            return SCREEN_CREDITS;

        case EVENT_HELP:
            return SCREEN_RULES;

        case EVENT_INTRO:
            return SCREEN_INTRO;

        case EVENT_PLAY:
            return next_screen;

        case EVENT_QUIT:
            return SCREEN_QUIT;

        case EVENT_TOGGLE_FULLSCREEN:
            game.toggleFullscreen ();
            break;

        case EVENT_TOGGLE_MUSIC:
            game.toggleMusic ();
            break;

        case EVENT_TOGGLE_SOUND:
            game.toggleSound ();
            break;

        default:
            break;
    }

    return SCREEN_DEFAULT;
}


ScreenEnum
Screens::fromEvents (const ScreenEnum& next_screen)
{
    DEBUG_FUNCTION_ENTER;

    ScreenEnum screen = SCREEN_DEFAULT;

    SDL_Event event;

    while (screen == SCREEN_DEFAULT && SDL_PollEvent (&event))
    {
        screen = fromCommonEvent (event, next_screen);
    }

    DEBUG_FUNCTION_EXIT;

    return screen;
}


ScreenEnum
Screens::screenGameOver ()
{
    DEBUG_FUNCTION_ENTER;

    game.emitSound (SOUND_GAME_OVER);

    DEBUG_FUNCTION_EXIT;

    return dummyScreen ("GAME OVER");
}


ScreenEnum
Screens::screenLevelComplete ()
{
    DEBUG_FUNCTION_ENTER;

    game.emitSound (SOUND_LEVEL_COMPLETE);

    DEBUG_FUNCTION_EXIT;

    return dummyScreen ("Level complete");
}


ScreenEnum
Screens::screenQuit ()
{
    DEBUG_FUNCTION_ENTER;

    game.setEnabled (false);

    DEBUG_FUNCTION_EXIT;

    return SCREEN_QUIT;
}


ScreenEnum
Screens::switchTo (const ScreenEnum& screen)
{
    DEBUG_FUNCTION_ENTER;

    switch (screen)
    {
        case SCREEN_CREDITS:
            return screen_credits->run ();

        case SCREEN_GAME_OVER:
            return screenGameOver ();

        case SCREEN_INTRO:
            return screen_intro->run ();

        case SCREEN_LEVEL_COMPLETE:
            return screenLevelComplete ();

        case SCREEN_PLAY:
            return screen_game_play->run ();

        case SCREEN_RULES:
            return screen_rules->run ();

        case SCREEN_QUIT:
        default:
            return screenQuit ();
    }

    DEBUG_FUNCTION_EXIT;

    return screen;
}

