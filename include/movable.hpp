/*
 * movable.hpp
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

#ifndef _MOVABLE_HPP
#define _MOVABLE_HPP

/**
 * \file
 * \brief Interface for movable objects.
 *
 * This header file declares an interface structure to re-implement in
 * movable descendant structures / classes, if necessary.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <SDL.h>

#include "geometry.hpp"


/* movable interface */


/**
 * \brief Interface for movable object classes.
 *
 * This abstract structure MUST implement at least pure virtual methods
 * in descendant structures / classes.
 *
 */
struct Movable
{
public:

    AnchorageEnum   anchorage;

    SDL_Point   anchor;
    SDL_Point   direction;

    int dx;
    int dy;

public:

    /**
     * \brief Structure constructor.
     */
    Movable ();


    /**
     * \brief Structure destructor.
     */
    virtual ~Movable ();


    /**
     * \brief Moves object instance along with internal data.
     */
    virtual void move ();


    /**
     * \brief Moves object instance to relative offset coordinates.
     *
     * \param dx - relative offset to add to internal data.
     * \param dy - relative offset to add to internal data.
     */
    virtual void move (
        const int dx,
        const int dy
    );


    /**
     * \brief Moves object instance to relative offset coordinates,
     * with a given direction factor to observe.
     *
     * \param dx - relative offset to add to internal data.
     * \param dy - relative offset to add to internal data.
     * \param direction - direction XY factors to observe.
     */
    virtual void move (
        const int dx,
        const int dy,
        const SDL_Point& direction
    );


    /**
     * \brief Moves object instance to relative offset coordinates,
     * with a given direction factor to observe.
     *
     * \param dx - relative offset to add to internal data.
     * \param dy - relative offset to add to internal data.
     * \param direction_x - direction X factor to observe e.g. (-1, 0,
     * +1).
     * \param direction_y - direction Y factor to observe e.g. (-1, 0,
     * +1).
     */
    virtual void move (
        const int dx,
        const int dy,
        const int direction_x,
        const int direction_y
    );


    /**
     * \brief Moves object instance along internal data, with a given
     * direction factor to observe.
     *
     * \param direction - direction XY factors to observe.
     */
    virtual void moveDirection (
        const SDL_Point& direction
    );


    /**
     * \brief Moves object instance along internal data, with a given
     * direction factor to observe.
     *
     * \param direction_x - direction X factor to observe e.g. (-1, 0,
     * +1).
     * \param direction_y - direction Y factor to observe e.g. (-1, 0,
     * +1).
     */
    virtual void moveDirection (
        const int direction_x,
        const int direction_y
    );


    /**
     * \brief Sets object instance absolute position along given
     * coordinates and internal data indications.
     *
     * \param anchor - absolute XY coordinates.
     */
    virtual void setPosition (
        const SDL_Point& anchor
    );


    /**
     * \brief Sets object instance absolute position along given
     * coordinates and internal data indications.
     *
     * \param anchor_x - absolute X coordinate.
     * \param anchor_y - absolute Y coordinate.
     */
    virtual void setPosition (
        const int anchor_x,
        const int anchor_y
    );


    /**
     * \brief Sets object instance absolute position along given
     * coordinates and anchorage indications.
     *
     * \param anchor - absolute XY coordinates.
     * \param anchorage - anchorage enumeration indications.
     */
    virtual void setPosition (
        const SDL_Point& anchor,
        const AnchorageEnum& anchorage
    );


    /**
     * \brief Sets object instance absolute position along given
     * coordinates and anchorage indications.
     *
     * \param anchor_x - absolute X coordinate.
     * \param anchor_y - absolute Y coordinate.
     * \param anchorage - anchorage enumeration indications.
     */
    virtual void setPosition (
        const int anchor_x,
        const int anchor_y,
        const AnchorageEnum& anchorage
    );


    /**
     * \brief Updates current position along with specific constraints.
     *
     * This pure virtual method MUST always be implemented in
     * descendant structures / classes.
     */
    virtual void updatePosition () = 0;

};


#endif /* _MOVABLE_HPP */
