/*
 * user_info.hpp
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

#ifndef _USER_INFO_HPP
#define _USER_INFO_HPP

/**
 * \file
 * \brief Thread-animated user information text management API.
 *
 * This header file declares a minimal API for animated info text.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <string>

#include <SDL.h>

#include "color.hpp"
#include "defs.hpp"
#include "font.hpp"
#include "game_defs.hpp"
#include "game_part.hpp"
#include "sprite.hpp"
#include "threadable.hpp"


/**
 * \def USER_INFO_ANCHORAGE
 *
 * Default value: ANCHOR_CENTER
 *
 * Might be overridden by GAME_USER_INFO_ANCHORAGE
 * if defined in game_defs.hpp header file.
 */
#ifdef GAME_USER_INFO_ANCHORAGE
    #define USER_INFO_ANCHORAGE     GAME_USER_INFO_ANCHORAGE
#else
    #define USER_INFO_ANCHORAGE     ANCHOR_CENTER
#endif


/**
 * \def USER_INFO_ANCHOR_X
 *
 * Default value: game.window_center.x
 *
 * Might be overridden by GAME_USER_INFO_ANCHOR_X
 * if defined in game_defs.hpp header file.
 */
#ifdef GAME_USER_INFO_ANCHOR_X
    #define USER_INFO_ANCHOR_X      GAME_USER_INFO_ANCHOR_X
#else
    #define USER_INFO_ANCHOR_X      game.window_center.x
#endif


/**
 * \def USER_INFO_ANCHOR_Y
 *
 * Default value: game.window_center.y
 *
 * Might be overridden by GAME_USER_INFO_ANCHOR_Y
 * if defined in game_defs.hpp header file.
 */
#ifdef GAME_USER_INFO_ANCHOR_Y
    #define USER_INFO_ANCHOR_Y      GAME_USER_INFO_ANCHOR_Y
#else
    #define USER_INFO_ANCHOR_Y      game.window_center.y
#endif


/**
 * \def USER_INFO_COLOR
 *
 * Default value: White
 *
 * Might be overridden by GAME_USER_INFO_COLOR
 * if defined in game_defs.hpp header file.
 */
#ifdef GAME_USER_INFO_COLOR
    #define USER_INFO_COLOR         GAME_USER_INFO_COLOR
#else
    #define USER_INFO_COLOR         White
#endif


/**
 * \def USER_INFO_DELAY
 *
 * Default value: 1000
 *
 * Might be overridden by GAME_USER_INFO_DELAY
 * if defined in game_defs.hpp header file.
 */
#ifdef GAME_USER_INFO_DELAY
    #define USER_INFO_DELAY         GAME_USER_INFO_DELAY
#else
    #define USER_INFO_DELAY         1000
#endif


/**
 * \def USER_INFO_FONT
 *
 * Default value: FONT_FOR_TEXT
 *
 * Might be overridden by GAME_USER_INFO_FONT
 * if defined in game_defs.hpp header file.
 */
#ifdef GAME_USER_INFO_FONT
    #define USER_INFO_FONT          GAME_USER_INFO_FONT
#else
    #define USER_INFO_FONT          FONT_FOR_TEXT
#endif


/**
 * \brief Thread-animated user information text management structure.
 *
 * Each default USER_INFO_xxx macro value might be overridden by
 * GAME_USER_INFO_xxx macro value, if defined in game_defs.hpp header
 * file.
 *
 * For example, USER_INFO_FONT value might be overridden by
 * GAME_USER_INFO_FONT value, if actually defined in game_defs.hpp
 * header file.
 */
struct UserInfo : public GamePart, public Threadable
{
protected:

    /**
     * \brief Specific function called by animation thread.
     *
     * The \c friend keyword allows this function to access protected
     * members.
     *
     * \param data - opaque pointer to thread data.
     *
     * \return negative value on failure, zero (0) on success.
     */
    friend int userInfoAnimationThread (void * const data);

    Delay       m_animation_duration_ms;
    FontEnum    m_font_index;
    Sprite      m_text_sprite;

public:

    /**
     * \brief Structure constructor.
     *
     * Initializes object instance along game management class.
     *
     * \param game - game central management object instance.
     */
    UserInfo (Game& game);


    /**
     * \brief Structure destructor.
     */
    virtual ~UserInfo ();


    /**
     * \brief Draws information text into given rendering context.
     *
     * \param renderer - SDL renderer.
     *
     * \return negative value on failure, zero (0) on success.
     */
    virtual int draw (SDL_Renderer * const renderer);


    /**
     * \brief Initializes internal data.
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool initialize ();


    /**
     * \brief Resets all internal data to default values.
     */
    virtual void reset ();


    /**
     * \brief Resets text anchorage point to default value.
     */
    virtual void resetAnchoragePoint ();


    /**
     * \brief Resets text color to default value.
     */
    virtual void resetColor ();


    /**
     * \brief Resets text font index to default value.
     */
    virtual void resetFontIndex ();


    /**
     * \brief Sets text anchorage point to given values.
     *
     * \param anchor_x - anchor point X coordinate.
     * \param anchor_y - anchor point Y coordinate.
     * \param anchorage - anchorage enumeration indications.
     */
    virtual void setAnchoragePoint (
        const int anchor_x,
        const int anchor_y,
        const AnchorageEnum& anchorage
    );


    /**
     * \brief Sets text color to given value.
     *
     * \param color - color object.
     */
    virtual void setColor (const Color& color);


    /**
     * \brief Sets text font index to given value.
     *
     * \param font_index - font enumeration index number.
     */
    virtual void setFontIndex (const FontEnum& font_index);


    /**
     * \brief Shows up user information text.
     *
     * \param renderer  - SDL renderer.
     * \param message   - text to show up.
     * \param delay_ms  - animation duration, in milliseconds.
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool show (
        SDL_Renderer * const renderer,
        const std::string& message,
        const Delay& delay_ms = USER_INFO_DELAY
    );

};


#endif /* _USER_INFO_HPP */
