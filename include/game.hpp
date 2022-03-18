/*
 * game.hpp
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

#ifndef _GAME_HPP
#define _GAME_HPP

/**
 * \file
 * \brief Game central management tools.
 *
 * This header file declares all necessary management tools for the
 * game project.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "asset.hpp"
#include "color.hpp"
#include "defs.hpp"
#include "geometry.hpp"


struct Screens;
struct UserInfo;


/**
 * \brief Central class for game project.
 *
 * This class might be either edited / completed in-place or extended
 * in another header file to better fit project's actual needs.
 */
class Game
{

public:

    SDL_Window *    window;
    SDL_Renderer *  renderer;

    Screens *       screens;
    UserInfo *      user_info;

    ISize           window_size;
    SDL_Point       window_center;

    Color           background_color;

    Asset           asset;

    Level           level;

protected:

    bool    m_enabled;
    bool    m_allow_music;
    bool    m_allow_sound;

public:

    /**
     * \brief Class constructor.
     */
    Game ();


    /**
     * \brief Class destructor.
     */
    virtual ~Game ();


    /**
     * \brief Emits sound along enumeration index number.
     *
     * \param index - enumeration index number.
     */
    virtual void emitSound (const SoundEnum& index);


    /**
     * \brief Gets font along enumeration index number.
     *
     * \param index - enumeration index number.
     *
     * \return pointer to existing font object.
     */
    virtual TTF_Font * getFont (const FontEnum& index);


    /**
     * \brief Gets image along enumeration index number.
     *
     * \param index - enumeration index number.
     *
     * \return pointer to existing image object.
     */
    virtual SDL_Surface * getImage (const ImageEnum& index);


    /**
     * \brief Tells if game is still running (enabled) or not.
     *
     * \return true if game is enabled, false otherwise.
     */
    virtual bool isEnabled () const;


    /**
     * \brief Tells if game window is in fullscreen mode or not.
     *
     * \return true if in fullscreen mode, false otherwise.
     */
    virtual bool isFullscreen () const;


    /**
     * \brief Plays music along enumeration index number.
     *
     * \param index - enumeration index number.
     */
    virtual void playMusic (const MusicEnum& index);


    /**
     * \brief Actually runs game.
     *
     * \return either EXIT_SUCCESS or EXIT_FAILURE.
     */
    virtual int run ();


    /**
     * \brief Sets up game running mode (enabled).
     *
     * \param state - true, game is running, false, game is no more
     * running.
     */
    virtual void setEnabled (bool state);


    /**
     * \brief Stops current music playoff, if any.
     */
    virtual void stopMusic ();


    /**
     * \brief Toggles between game window's fullscreen mode and normal
     * mode.
     */
    virtual void toggleFullscreen ();


    /**
     * \brief Enables / disables music playoff.
     */
    virtual void toggleMusic ();


    /**
     * \brief Enables / disables sound playoff.
     */
    virtual void toggleSound ();

protected:

    /**
     * \brief Sets up all external resource initializations i.e. mainly
     * assets (fonts, images, musics and sounds).
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool externalResourcesInitialize ();


    /**
     * \brief Loads all external resources into memory i.e. mainly
     * assets (fonts, images, musics and sounds).
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool externalResourcesLoad ();


    /**
     * \brief Sets up game initializations.
     *
     * Sets up game internal resource initializations e.g. game window,
     * renderer, screens and so on.
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool initialize ();


    /**
     * \brief Game's main loop.
     *
     * This loop is mainly a game screen switcher.
     *
     * \return always returns EXIT_SUCCESS.
     */
    virtual int mainLoop ();

};


#endif /* _GAME_HPP */
