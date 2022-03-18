/*
 * drawable.hpp
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

#ifndef _DRAWABLE_HPP
#define _DRAWABLE_HPP

/**
 * \file
 * \brief Interface for SDL drawable objects.
 *
 * This header file declares an interface structure to implement in SDL
 * drawable object classes.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <SDL.h>

#include "color.hpp"


/* drawable interface */

/**
 * \brief Interface for SDL drawable object classes.
 *
 * This abstract structure MUST be implemented in descendant structures
 * / classes.
 *
 */
struct Drawable
{
public:

    bool    is_visible;

public:

    /**
     * \brief Structure constructor.
     */
    Drawable ();


    /**
     * \brief Structure destructor.
     */
    virtual ~Drawable ();


    /**
     * \brief Draws object instance pixels into a given SDL renderer.
     *
     * \param renderer - a well-initialized SDL renderer.
     *
     * \return negative value on failure, zero value (0) on success.
     */
    virtual int draw (
        SDL_Renderer * const renderer
    ) = 0;


    /**
     * \brief Draws object instance pixels into a given SDL renderer
     * with alpha channel (opacity).
     *
     * \param renderer - a well-initialized SDL renderer.
     * \param alpha - alpha 8-bit color channel (opacity).
     *
     * \return negative value on failure, zero value (0) on success.
     */
    virtual int draw (
        SDL_Renderer * const renderer,
        const ColorChannel& alpha
    ) = 0;


    /**
     * \brief Draws object instance pixels into a given SDL renderer
     * with color mask.
     *
     * \param renderer - a well-initialized SDL renderer.
     * \param color - a color object to serve as color mask onto
     * object's own color pixels.
     *
     * \return negative value on failure, zero value (0) on success.
     */
    virtual int draw (
        SDL_Renderer * const renderer,
        const Color& color
    ) = 0;
};


#endif /* _DRAWABLE_HPP */
