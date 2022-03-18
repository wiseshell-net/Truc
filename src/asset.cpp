/*
 * asset.cpp
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

#include "asset.hpp"

#include "debug.hpp"
#include "error.hpp"


Asset::Asset () :
fonts (nullptr),
images (nullptr),
musics (nullptr),
sounds (nullptr)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


Asset::~Asset ()
{
    DEBUG_FUNCTION_ENTER;

    delete fonts;
    delete images;
    delete musics;
    delete sounds;

    DEBUG_FUNCTION_EXIT;
}


bool
Asset::fontSupported () const
{
    DEBUG_FUNCTION_CALL;

    return (fonts != nullptr);
}


bool
Asset::imageSupported () const
{
    DEBUG_FUNCTION_CALL;

    return (images != nullptr);
}


bool
Asset::initialize ()
{
    DEBUG_FUNCTION_ENTER;

    if (SDL_Init (ASSET_SDL_INIT_FLAGS) != ERROR_EXIT_SUCCESS)
    {
        return Error::sdlError ("Unable to initialize SDL.");
    }

    atexit (SDL_Quit);

#ifdef ASSET_ENABLE_FONTS

    if (TTF_Init () != ERROR_EXIT_SUCCESS)
    {
        return Error::sdlError ("Unable to initialize font support.");
    }

    atexit (TTF_Quit);

    fonts = new FontArray;

    if (fonts == nullptr)
    {
        return Error::runtimeError (
            "Unable to initialize font store.",
            __func__,
            "Null pointer font array."
        );
    }

#endif

#ifdef ASSET_ENABLE_IMAGES

    if (IMG_Init (ASSET_IMAGE_FLAGS) != (ASSET_IMAGE_FLAGS))
    {
        return Error::sdlError ("Unable to initialize image support.");
    }

    atexit (IMG_Quit);

    images = new ImageArray;

    if (images == nullptr)
    {
        return Error::runtimeError (
            "Unable to initialize image store.",
            __func__,
            "Null pointer image array."
        );
    }

#endif

#if (defined (ASSET_ENABLE_MUSICS) || defined (ASSET_ENABLE_SOUNDS))

    int init = Mix_Init (ASSET_MIXER_FLAGS);

    if ((init != (ASSET_MIXER_FLAGS)) && (init != ERROR_EXIT_SUCCESS))
    {
        return Error::sdlError ("Unable to initialize sound support.");
    }

    atexit (Mix_Quit);

    if (Mix_OpenAudio (ASSET_MIXER_DEFAULTS) != ERROR_EXIT_SUCCESS)
    {
        return Error::sdlError ("Unable to initialize sound mixer.");
    }

    atexit (Mix_CloseAudio);

#endif /* need mixer - musics or sounds enabled */

#ifdef ASSET_ENABLE_MUSICS

    musics = new MusicArray;

    if (musics == nullptr)
    {
        return Error::runtimeError (
            "Unable to initialize music store.",
            __func__,
            "Null pointer music array."
        );
    }

#endif

#ifdef ASSET_ENABLE_SOUNDS

    sounds = new SoundArray;

    if (sounds == nullptr)
    {
        return Error::runtimeError (
            "Unable to initialize sound store.",
            __func__,
            "Null pointer sound array."
        );
    }

#endif

    DEBUG_FUNCTION_EXIT;

    return true;
}


bool
Asset::loadAll (void)
{
    DEBUG_FUNCTION_ENTER;

    bool status = (
#ifdef ASSET_ENABLE_FONTS
        fonts->loadAll (ASSET_FONTS_DIR) &&
#endif

#ifdef ASSET_ENABLE_IMAGES
        images->loadAll (ASSET_IMAGES_DIR) &&
#endif

#ifdef ASSET_ENABLE_MUSICS
        musics->loadAll (ASSET_MUSICS_DIR) &&
#endif

#ifdef ASSET_ENABLE_SOUNDS
        sounds->loadAll (ASSET_SOUNDS_DIR) &&
#endif
        true
    );

#if (defined (ASSET_ENABLE_MUSICS) || defined (ASSET_ENABLE_SOUNDS))

    Mix_AllocateChannels (ASSET_MAX_SOUND_CHANNELS);

    Mix_Volume (-1, MIX_MAX_VOLUME);

#endif /* need mixer - musics or sounds enabled */

    DEBUG_FUNCTION_EXIT;

    return status;
}


bool
Asset::musicSupported () const
{
    DEBUG_FUNCTION_CALL;

    return (musics != nullptr);
}


bool
Asset::soundSupported () const
{
    DEBUG_FUNCTION_CALL;

    return (sounds != nullptr);
}
