/*
 * sprite_layer_array.hpp
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

#ifndef _SPRITE_LAYER_ARRAY_HPP
#define _SPRITE_LAYER_ARRAY_HPP

/**
 * \file
 * \brief Multiple sprite layers array management API.
 *
 * This header file declares a minimal API for managing an array of
 sprite layers.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <SDL.h>

#include "array.hpp"
#include "color.hpp"
#include "drawable.hpp"
#include "movable.hpp"
#include "sprite_layer.hpp"


/**
 * \brief Multiple sprite layers array management structure.
 *
 * This structure manages an array of pointer references to external
 * sprite layer object instances, with garbage collection support.
 */
struct SpriteLayerArray :
    public PArray<SpriteLayer *>,
    public Drawable,
    public Movable
{
public:

    /**
     * \brief Structure constructor.
     */
    SpriteLayerArray ();


    /**
     * \brief Structure constructor variant.
     *
     * Initializes object instance with a given number of array items.
     *
     * \param size - number of items in array.
     */
    explicit SpriteLayerArray (const ArraySize& size);


    /**
     * \brief Structure destructor.
     */
    virtual ~SpriteLayerArray ();


    /**
     * \brief Draws all sprite layers at once in rendering context.
     *
     * \param renderer - SDL renderer.
     *
     * \return negative value on failure, zero (0) on success.
     */
    virtual int draw (
        SDL_Renderer * const renderer
    );


    /**
     * \brief Draws all sprite layers at once in rendering context with
     * alpha channel (opacity).
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
     * \brief Draws all sprite layers at once in rendering context with
     * color mask.
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
     * \brief Moves all sprite layers at once along with array's
     * internal data.
     */
    virtual void move ();


    /**
     * \brief Moves all sprite layers at once to relative offset
     * coordinates.
     *
     * \param dx - relative offset to add to internal data.
     * \param dy - relative offset to add to internal data.
     */
    virtual void move (
        const int dx,
        const int dy
    );


    /**
     * \brief Moves all sprite layers at once to relative offset
     * coordinates, with a given direction factor to observe.
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
     * \brief Moves all sprite layers at once to relative offset
     * coordinates, with a given direction factor to observe.
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
     * \brief Moves all sprite layers at once along internal data, with
     * a given direction factor to observe.
     *
     * \param direction - direction XY factors to observe.
     */
    virtual void moveDirection (
        const SDL_Point& direction
    );


    /**
     * \brief Moves all sprite layers at once along internal data, with
     * a given direction factor to observe.
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
     * \brief Allows each sprite layer to move on its own internal
     * data.
     */
    virtual void moveSelf ();


    /**
     * \brief Moves array to absolute position along given coordinates
     * and internal data indications.
     *
     * Sprite layers are moved relatively to array's position.
     *
     * \param anchor - absolute XY coordinates.
     */
    virtual void setPosition (
        const SDL_Point& anchor
    );


    /**
     * \brief Moves array to absolute position along given coordinates
     * and internal data indications.
     *
     * Sprite layers are moved relatively to array's position.
     *
     * \param anchor_x - absolute X coordinate.
     * \param anchor_y - absolute Y coordinate.
     */
    virtual void setPosition (
        const int anchor_x,
        const int anchor_y
    );


    /**
     * \brief Moves array to absolute position along given coordinates
     * and internal data indications.
     *
     * Sprite layers are moved relatively to array's position.
     *
     * \param anchor - absolute XY coordinates.
     * \param anchorage - anchorage enumeration indications.
     */
    virtual void setPosition (
        const SDL_Point& anchor,
        const AnchorageEnum& anchorage
    );


    /**
     * \brief Moves array to absolute position along given coordinates
     * and internal data indications.
     *
     * Sprite layers are moved relatively to array's position.
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
     * Actually does nothing in current implementation.
     */
    virtual void updatePosition ();

};


#endif /* _SPRITE_LAYER_ARRAY_HPP */
