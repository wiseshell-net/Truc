/*
 * game.cpp
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

#include "game.hpp"

#include "debug.hpp"
#include "error.hpp"
#include "screens.hpp"
#include "user_info.hpp"


Game::Game () :
window (nullptr),
renderer (nullptr),
screens (nullptr),
user_info (nullptr)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


Game::~Game ()
{
    DEBUG_FUNCTION_ENTER;

    delete user_info;

    delete screens;

    SDL_DestroyRenderer (renderer);

    SDL_DestroyWindow (window);

    DEBUG_FUNCTION_EXIT;
}


void
Game::emitSound (const SoundEnum& index)
{
    DEBUG_FUNCTION_ENTER;

    if (!asset.soundSupported ()) return;

    if (m_allow_sound)
    {
        asset.sounds->emitSound (index);
    }
    else
    {
        Mix_HaltChannel (-1);
    }

    DEBUG_FUNCTION_EXIT;
}


TTF_Font *
Game::getFont (const FontEnum& index)
{
    DEBUG_FUNCTION_CALL;

    return asset.fontSupported () ?
        asset.fonts->getFont (index) : nullptr;
}


SDL_Surface *
Game::getImage (const ImageEnum& index)
{
    DEBUG_FUNCTION_CALL;

    return asset.imageSupported () ?
        asset.images->getImage (index) : nullptr;
}


bool
Game::initialize ()
{
    DEBUG_FUNCTION_ENTER;

    window_size = { GAME_VIEWPORT_WIDTH, GAME_VIEWPORT_HEIGHT };

    window_center = { window_size.w / 2, window_size.h / 2 };

    window = SDL_CreateWindow (
        GAME_NAME,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_size.w,
        window_size.h,
        SDL_WINDOW_OPENGL
    );

    if (window == nullptr)
    {
        return Error::sdlError ("Unable to create game window.");
    }

    renderer = SDL_CreateRenderer (
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == nullptr)
    {
        return Error::sdlError ("Unable to set up window's renderer.");
    }

    background_color = GAME_BACKGROUND_COLOR;

    m_enabled = true;
    m_allow_music = true;
    m_allow_sound = true;

    level = 0;

    user_info = new UserInfo (*this);

    if (user_info == nullptr || !user_info->initialize ())
    {
        return Error::runtimeError (
            "Unable to initialize user info.",
            __func__,
            "User info init failed."
        );
    }

    screens = new Screens (*this);

    if (screens == nullptr || !screens->initializeAll ())
    {
        return Error::runtimeError (
            "Unable to initialize screens.",
            __func__,
            "Screen inits failed."
        );
    }

    DEBUG_FUNCTION_EXIT;

    return true;
}


bool
Game::isEnabled () const
{
    DEBUG_FUNCTION_CALL;

    return m_enabled;
}


bool
Game::isFullscreen () const
{
    DEBUG_FUNCTION_CALL;

    return (
        (SDL_GetWindowFlags (window) &
        (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP))
        != 0
    );
}


int
Game::mainLoop ()
{
    DEBUG_FUNCTION_ENTER;

    ScreenEnum screen = SCREEN_INTRO;

    while (isEnabled ())
    {
        screen = screens->switchTo (screen);
    }

    DEBUG_FUNCTION_EXIT;

    return EXIT_SUCCESS;
}


void
Game::playMusic (const MusicEnum& index)
{
    DEBUG_FUNCTION_ENTER;

    if (!asset.musicSupported ()) return;

    stopMusic ();

    Mix_VolumeMusic (GAME_MUSIC_VOLUME);

    Mix_FadeInMusic (
        asset.musics->getMusic (index),
        GAME_MUSIC_LOOPS,
        GAME_MUSIC_FADE_IN_DELAY
    );

    if (!m_allow_music)
    {
        Mix_PauseMusic ();
    }

    DEBUG_FUNCTION_EXIT;
}


bool
Game::externalResourcesInitialize ()
{
    DEBUG_FUNCTION_CALL;

    return asset.initialize ();
}


bool
Game::externalResourcesLoad ()
{
    DEBUG_FUNCTION_CALL;

    return asset.loadAll ();
}


int
Game::run ()
{
    DEBUG_FUNCTION_ENTER;

    if (!externalResourcesInitialize ())
    {
        Error::fatalError ("Unable to initialize game resources.");
    }

    if (!externalResourcesLoad ())
    {
        Error::fatalError ("Unable to load game resources.");
    }

    if (!initialize ())
    {
        Error::fatalError ("Unable to initialize game.");
    }

    DEBUG_FUNCTION_EXIT;

    return mainLoop ();
}


void
Game::setEnabled (bool state)
{
    DEBUG_FUNCTION_ENTER;

    m_enabled = state;

    DEBUG_FUNCTION_EXIT;
}


void
Game::stopMusic ()
{
    DEBUG_FUNCTION_ENTER;

    if (!asset.musicSupported ()) return;

    if (m_allow_music)
    {
        Mix_FadeOutMusic (GAME_MUSIC_FADE_OUT_DELAY);
    }
    else
    {
        Mix_HaltMusic ();
    }

    DEBUG_FUNCTION_EXIT;
}


void
Game::toggleFullscreen ()
{
    DEBUG_FUNCTION_ENTER;

    SDL_SetWindowFullscreen (
        window,
        isFullscreen () ? 0 : SDL_WINDOW_FULLSCREEN
    );

    DEBUG_FUNCTION_EXIT;
}


void
Game::toggleMusic ()
{
    DEBUG_FUNCTION_ENTER;

    if (!asset.musicSupported ()) return;

    m_allow_music = !m_allow_music;

    if (m_allow_music)
    {
        Mix_ResumeMusic ();

        user_info->show (renderer, "music enabled");
    }
    else
    {
        Mix_PauseMusic ();

        user_info->show (renderer, "music disabled");
    }

    DEBUG_FUNCTION_EXIT;
}


void
Game::toggleSound ()
{
    DEBUG_FUNCTION_ENTER;

    if (!asset.soundSupported ()) return;

    m_allow_sound = !m_allow_sound;

    if (m_allow_sound)
    {
        user_info->show (renderer, "sound enabled");
    }
    else
    {
        Mix_HaltChannel (-1);

        user_info->show (renderer, "sound disabled");
    }

    DEBUG_FUNCTION_EXIT;
}

