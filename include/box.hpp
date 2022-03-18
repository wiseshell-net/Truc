/*
 * box.hpp
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

#ifndef _BOX_HPP
#define _BOX_HPP

/**
 * \file
 * \brief Arbitrary rectangle and collision management.
 *
 * This header file declares class and methods for managing arbitrary
 * rectangles with collision support.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <SDL.h>

#include "geometry.hpp"


/**
 * \brief Arbitrary rectangle and collision support structure.
 *
 * A general purpose API for managing arbitrary rectangles with
 * collision support.
 *
 */
struct Box
{
public:

    SDL_Rect *  rect;

public:

    /**
     * \brief Structure constructor.
     */
    Box ();


    /**
     * \brief Structure constructor variant.
     *
     * Initializes object instance by pointer reference to an existing
     * rectangle object.
     *
     * \param rect - pointer reference to an existing rectangle object.
     */
    Box (SDL_Rect * const rect);


    /**
     * \brief Structure constructor variant.
     *
     * Initializes object instance by object reference to an existing
     * rectangle object.
     *
     * \param rect - object reference to an existing rectangle object.
     */
    Box (SDL_Rect& rect);


    /**
     * \brief Structure destructor.
     */
    virtual ~Box ();


    /**
     * \brief Gets box bottom left corner XY coordinates.
     *
     * \return bottom left corner XY coordinates (read-only).
     */
    virtual const SDL_Point bottomLeft () const;


    /**
     * \brief Gets box bottom right corner XY coordinates.
     *
     * \return bottom right corner XY coordinates (read-only).
     */
    virtual const SDL_Point bottomRight () const;


    /**
     * \brief Gets box bottom side Y coordinate.
     *
     * \return bottom side Y coordinate (read-only).
     */
    virtual int bottomSide () const;


    /**
     * \brief Gets a copy of referenced rectangle object.
     *
     * \return constant rectangle object copy (read-only).
     */
    virtual const SDL_Rect boundingBox () const;


    /**
     * \brief Gets box center XY coordinates.
     *
     * \return center XY coordinates (read-only).
     */
    virtual const SDL_Point center () const;


    /**
     * \brief Gets box half-size dimensions (w, h).
     *
     * Gets box half-size dimensions (w, h).
     * May also be interpreted as center point relative XY coordinates.
     *
     * \return box half-size dimensions (read-only).
     */
    virtual const ISize centroid () const;


    /**
     * \brief Gets box diagonal length.
     *
     * \return rectangle diagonal length (read-only).
     */
    virtual int diagonal () const;


    /**
     * \brief Gets box height dimension.
     *
     * \return rectangle height dimension (read-only).
     */
    virtual int height () const;


    /**
     * \brief Tells if box' rectangle intersects with another
     * rectangle.
     *
     * Indicates if box' rectangle intersects (collides) with another
     * external rectangle.
     *
     * Collision support.
     *
     * \param rect - pointer to an existing rectangle object.
     *
     * \return true if both rectangles intersect, false otherwise.
     */
    virtual bool intersects (const SDL_Rect * const rect) const;


    /**
     * \brief Tells if box' rectangle intersects with another
     * rectangle.
     *
     * Indicates if box' rectangle intersects (collides) with another
     * external rectangle.
     *
     * Collision support.
     *
     * \param rect - object reference to an existing rectangle object.
     *
     * \return true if both rectangles intersect, false otherwise.
     */
    virtual bool intersects (const SDL_Rect& rect) const;


    /**
     * \brief Tells if box' rectangle intersects with another box
     * rectangle.
     *
     * Indicates if box' rectangle intersects (collides) with another
     * box rectangle.
     *
     * Collision support.
     *
     * \param box - pointer to an existing box object.
     *
     * \return true if both rectangles intersect, false otherwise.
     */
    virtual bool intersects (const Box * const box) const;


    /**
     * \brief Tells if box' rectangle intersects with another box
     * rectangle.
     *
     * Indicates if box' rectangle intersects (collides) with another
     * box rectangle.
     *
     * Collision support.
     *
     * \param box - object reference to an existing box object.
     *
     * \return true if both rectangles intersect, false otherwise.
     */
    virtual bool intersects (const Box& box) const;


    /**
     * \brief Gets box left side X coordinate.
     *
     * \return left side X coordinate (read-only).
     */
    virtual int leftSide () const;


    /**
     * \brief Gets box right side X coordinate.
     *
     * \return right side X coordinate (read-only).
     */
    virtual int rightSide () const;


    /**
     * \brief Gets box top left corner XY coordinates.
     *
     * \return top left corner XY coordinates (read-only).
     */
    virtual const SDL_Point topLeft () const;


    /**
     * \brief Gets box top right corner XY coordinates.
     *
     * \return top right corner XY coordinates (read-only).
     */
    virtual const SDL_Point topRight () const;


    /**
     * \brief Gets box top side Y coordinate.
     *
     * \return top side Y coordinate (read-only).
     */
    virtual int topSide () const;


    /**
     * \brief Gets box width dimension.
     *
     * \return rectangle width dimension (read-only).
     */
    virtual int width () const;
};


#endif /* _BOX_HPP */
