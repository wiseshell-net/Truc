/*
 * asset.hpp
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

#ifndef _ASSET_HPP
#define _ASSET_HPP

/**
 * \file
 * \brief Asset management - external resource store.
 *
 * This header file declares a minimal API for external resources
 * (assets) management.
 *
 * These resources are mainly fonts, images, sounds and music files.
 *
 * ASSET_ENABLE_xxx macro defines should be commented / uncommented
 * directly into this header file, along project needs.
 *
 * All other macro defines are defaulted to listed values unless
 * overridden into game_defs.hpp header file.
 *
 * To override an ASSET_xxx value, merely #define GAME_xxx value in
 * game_defs.hpp header file (replace ASSET_ prefix by GAME_ prefix).
 *
 * For example, to override ASSET_FONTS_DIR value, merely #define
 * GAME_FONTS_DIR value in game_defs.hpp header file.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include "font.hpp"
#include "game_defs.hpp"
#include "image.hpp"
#include "music.hpp"
#include "sound.hpp"


/* comment/uncomment along needs */

#define ASSET_ENABLE_FONTS
#define ASSET_ENABLE_IMAGES
#define ASSET_ENABLE_MUSICS
#define ASSET_ENABLE_SOUNDS


#ifdef GAME_SDL_INIT_FLAGS
    #define ASSET_SDL_INIT_FLAGS    GAME_SDL_INIT_FLAGS
#else
    #define ASSET_SDL_INIT_FLAGS    SDL_INIT_EVERYTHING
#endif

#ifdef GAME_IMAGE_FLAGS
    #define ASSET_IMAGE_FLAGS   GAME_IMAGE_FLAGS
#else
    #define ASSET_IMAGE_FLAGS   IMG_INIT_JPG | IMG_INIT_PNG
#endif

#ifdef GAME_MIXER_FLAGS
    #define ASSET_MIXER_FLAGS   GAME_MIXER_FLAGS
#else
    #define ASSET_MIXER_FLAGS   \
            MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MP3
#endif

#ifdef GAME_MIXER_DEFAULTS
    #define ASSET_MIXER_DEFAULTS    GAME_MIXER_DEFAULTS
#else
    #define ASSET_MIXER_DEFAULTS    \
            MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048
#endif

#ifdef GAME_FONTS_DIR
    #define ASSET_FONTS_DIR     GAME_FONTS_DIR
#else
    #define ASSET_FONTS_DIR     "res/fonts/"
#endif

#ifdef GAME_IMAGES_DIR
    #define ASSET_IMAGES_DIR    GAME_IMAGES_DIR
#else
    #define ASSET_IMAGES_DIR    "res/images/"
#endif

#ifdef GAME_MUSICS_DIR
    #define ASSET_MUSICS_DIR    GAME_MUSICS_DIR
#else
    #define ASSET_MUSICS_DIR    "res/musics/"
#endif

#ifdef GAME_SOUNDS_DIR
    #define ASSET_SOUNDS_DIR    GAME_SOUNDS_DIR
#else
    #define ASSET_SOUNDS_DIR    "res/sounds/"
#endif

#ifdef GAME_MAX_SOUND_CHANNELS
    #define ASSET_MAX_SOUND_CHANNELS    GAME_MAX_SOUND_CHANNELS
#else
    #define ASSET_MAX_SOUND_CHANNELS    30
#endif


/**
 * \brief External resources (assets) management class.
 *
 * This class acts as an asset store, gathering all external resources
 * in one central point, making code easier.
 *
 */
class Asset
{
public:

    FontArray *     fonts;
    ImageArray *    images;
    MusicArray *    musics;
    SoundArray *    sounds;

public:

    /**
     * \brief Class constructor.
     */
    Asset ();


    /**
     * \brief Class destructor.
     */
    virtual ~Asset ();


    /**
     * \brief Tells if font store is available for the project.
     *
     * \return true if fonts are supported, false otherwise.
     */
    virtual bool fontSupported () const;


    /**
     * \brief Tells if image store is available for the project.
     *
     * \return true if images are supported, false otherwise.
     */
    virtual bool imageSupported () const;


    /**
     * \brief Initializes asset store management.
     *
     * \return true if all inits went OK, false otherwise.
     */
    virtual bool initialize ();


    /**
     * \brief Loads all external resources into asset store.
     *
     * \return true if all is OK, false otherwise.
     */
    virtual bool loadAll ();


    /**
     * \brief Tells if music store is available for the project.
     *
     * \return true if musics are supported, false otherwise.
     */
    virtual bool musicSupported () const;


    /**
     * \brief Tells if sound store is available for the project.
     *
     * \return true if sounds are supported, false otherwise.
     */
    virtual bool soundSupported () const;

};


#endif /* _ASSET_HPP */
