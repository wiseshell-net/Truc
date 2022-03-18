/*
 * render.hpp
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

#ifndef _RENDER_HPP
#define _RENDER_HPP

/**
 * \file
 * \brief SDL rendering utility tools.
 *
 * This header file declares SDL rendering utility tools.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <SDL.h>

#include "color.hpp"


/**
 * \brief SDL rendering utility tools namespace.
 */
namespace Render
{

    /**
     * \brief Clears out buffer contents and fills out with a given
     * background color.
     *
     * \param renderer  - SDL renderer.
     * \param color     - background color.
     *
     * \return negative value on error, zero (0) on success.
     */
    int clear (SDL_Renderer * const renderer, const Color& color);


    /**
     * \brief Sends buffered pixels to display monitor (graphics card).
     *
     * \param renderer - SDL renderer.
     */
    void display (SDL_Renderer * const renderer);


    /**
     * \brief Sets current drawing color to given color values.
     *
     * \param renderer  - SDL renderer.
     * \param color     - drawing color.
     *
     * \return negative value on error, zero (0) on success.
     */
    int setDrawColor (
        SDL_Renderer * const renderer,
        const Color& color
    );

} /* namespace */


#endif /* _RENDER_HPP */
