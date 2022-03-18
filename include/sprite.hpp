/*
 * sprite.hpp
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

#ifndef _SPRITE_HPP
#define _SPRITE_HPP

/**
 * \file
 * \brief General purpose graphic sprite management API.
 *
 * This header file declares a minimal API for general purpose sprite.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "box.hpp"
#include "color.hpp"
#include "drawable.hpp"
#include "movable.hpp"


/**
 * \brief General purpose graphic sprite management structure.
 */
struct Sprite : public Drawable, public Movable
{
public:

    SDL_Texture *   texture;

    SDL_Rect        texture_rect;
    SDL_Rect        renderer_rect;

    Box             box;

    Color           color;

    bool            texture_is_internal;

public:

    /**
     * \brief Structure constructor.
     */
    Sprite ();


    /**
     * \brief Structure constructor variant.
     *
     * Initializes object instance with external texture reference.
     *
     * \param texture - pointer reference to external texture.
     */
    explicit Sprite (SDL_Texture * const texture);


    /**
     * \brief Structure constructor variant.
     *
     * Initializes object instance from image.
     *
     * \param renderer - SDL renderer.
     * \param surface  - SDL surface.
     */
    explicit Sprite (
        SDL_Renderer * const renderer,
        SDL_Surface * const surface
    );


    /**
     * \brief Structure constructor variant.
     *
     * Initializes object instance from text.
     *
     * \param renderer  - SDL renderer.
     * \param text      - text to display.
     * \param font      - pointer reference to text font.
     * \param color     - color object.
     */
    explicit Sprite (
        SDL_Renderer * const renderer,
        const std::string& text,
        TTF_Font * const font,
        const Color& color
    );


    /**
     * \brief Structure destructor.
     */
    virtual ~Sprite ();


    /**
     * \brief Clears texture reference.
     *
     * Deletes internal texture object, if any.
     */
    virtual void clearTexture ();


    /**
     * \brief Tells if current sprite object instance collides with
     * another sprite object instance.
     *
     * \param sprite - pointer reference to another sprite object
     * instance.
     *
     * \return true if both sprite boxes collide each other, false
     * otherwise.
     */
    virtual bool collides (const Sprite * const sprite);


    /**
     * \brief Tells if current sprite object instance collides with
     * another sprite object instance.
     *
     * \param sprite - object reference to another sprite object
     * instance.
     *
     * \return true if both sprite boxes collide each other, false
     * otherwise.
     */
    virtual bool collides (const Sprite& sprite);


    /**
     * \brief Draws sprite in rendering context.
     *
     * \param renderer - SDL renderer.
     *
     * \return negative value on failure, zero (0) on success.
     */
    virtual int draw (
        SDL_Renderer * const renderer
    );


    /**
     * \brief Draws sprite in rendering context with alpha channel
     * (opacity).
     *
     * \param renderer  - SDL renderer.
     * \param alpha     - alpha 8-bit color channel (opacity).
     *
     * \return negative value on failure, zero (0) on success.
     */
    virtual int draw (
        SDL_Renderer * const renderer,
        const ColorChannel& alpha
    );


    /**
     * \brief Draws sprite in rendering context with a color mask.
     *
     * \param renderer  - SDL renderer.
     * \param color     - color object to serve as pixel mask.
     *
     * \return negative value on failure, zero (0) on success.
     */
    virtual int draw (
        SDL_Renderer * const renderer,
        const Color& color
    );


    /**
     * \brief Sets sprite as text.
     *
     * \param renderer  - SDL renderer.
     * \param text      - text to display.
     * \param font      - pointer reference to text font.
     * \param color     - color object.
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool setText (
        SDL_Renderer * const renderer,
        const std::string& text,
        TTF_Font * const font,
        const Color& color
    );


    /**
     * \brief Sets sprite's texture to new reference.
     *
     * \param texture  - pointer reference to external texture.
     * \param internal - true, texture should be considered as internal
     * one, false, external texture reference.
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool setTexture (
        SDL_Texture * const texture,
        bool internal = false
    );


    /**
     * \brief Sets sprite's texture from image.
     *
     * \param renderer - SDL renderer.
     * \param surface  - SDL surface.
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool setTexture (
        SDL_Renderer * const renderer,
        SDL_Surface * const surface
    );


    /**
     * \brief Updates sprite's position along all internal constraints.
     */
    virtual void updatePosition ();

};


#endif /* _SPRITE_HPP */
