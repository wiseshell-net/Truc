/*
 * screen_base.hpp
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

#ifndef _SCREEN_BASE_HPP
#define _SCREEN_BASE_HPP

/**
 * \file
 * \brief Abstract base structure for all game screens.
 *
 * This header file declares an interface for all game screens.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include "game_part.hpp"
#include "screen_defs.hpp"


/* Screen base interface */


/**
 * \brief Abstract base structure for all game screens.
 *
 * This abstract base structure MUST be implemented in any descendant
 * class / structure.
 */
struct ScreenBase : public GamePart
{
public:

    /**
     * \brief Structure constructor.
     *
     * Initializes object instance along game management class.
     *
     * \param game - game central management object instance.
     */
    ScreenBase (Game& game);


    /**
     * \brief Structure destructor.
     */
    virtual ~ScreenBase ();


    /**
     * \brief Initializes screen on game start.
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool initialize () = 0;


    /**
     * \brief Runs game screen.
     *
     * \return next screen enumeration index number to go.
     */
    virtual ScreenEnum run ();

protected:

    /**
     * \brief Manages all screen drawable objects.
     *
     * \return next screen enumeration index number to go.
     */
    virtual ScreenEnum doDrawings () = 0;


    /**
     * \brief Manages all screen events.
     *
     * \return next screen enumeration index number to go.
     */
    virtual ScreenEnum doEvents () = 0;


    /**
     * \brief Manages all screen logic and interactions.
     *
     * \return next screen enumeration index number to go.
     */
    virtual ScreenEnum doLogic () = 0;


    /**
     * \brief Screen management main loop.
     *
     * \return next screen enumeration index number to go.
     */
    virtual ScreenEnum mainLoop ();


    /**
     * \brief Manages very last things before actually leaving screen.
     *
     * \return next screen enumeration index number to go.
     */
    virtual ScreenEnum onExit (ScreenEnum screen) = 0;


    /**
     * \brief Resets screen items before entering main loop.
     *
     * \return next screen enumeration index number to go.
     */
    virtual ScreenEnum reset () = 0;

};


#endif /* _SCREEN_BASE_HPP */
