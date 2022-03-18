/*
 * sprite_layer_area.hpp
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

#ifndef _SPRITE_LAYER_AREA_HPP
#define _SPRITE_LAYER_AREA_HPP

/**
 * \file
 * \brief Multiple sprites layer array management API with framed area
 * constraints.
 *
 * This header file declares a minimal API for managing a layer array
 * of sprites within a constrained area (frame).
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <SDL.h>

#include "box.hpp"
#include "geometry.hpp"
#include "sprite_layer.hpp"


/**
 * \brief Multiple sprites layer array management with framed area
 * constraints structure.
 *
 * This structure manages an array of pointer references to external
 * sprite object instances, with garbage collection support and
 * constrained movements into given area boundaries (frame).
 */
struct SpriteLayerArea: public SpriteLayer
{
public:

    SDL_Rect    frame_rect;
    SDL_Rect    viewport_rect;

    Box         box;

public:

    /**
     * \brief Structure constructor.
     */
    SpriteLayerArea ();


    /**
     * \brief Structure constructor variant.
     *
     * Initializes object instance with a given number of array items.
     *
     * \param size - number of items in array.
     */
    explicit SpriteLayerArea (const ArraySize& size);


    /**
     * \brief Structure destructor.
     */
    virtual ~SpriteLayerArea ();


    /**
     * \brief Gets current area size.
     *
     * \return area size (width, height) - integer dimensions.
     */
    virtual const ISize area () const;


    /**
     * \brief Moves all sprites at once along with layer array's
     * internal data.
     *
     * This method takes in account area frame constraints while moving
     * around viewport's frame boundaries.
     */
    virtual void moveAround ();


    /**
     * \brief Moves all sprites at once to relative offset coordinates.
     *
     * This method takes in account area frame constraints while moving
     * around viewport's frame boundaries.
     *
     * \param dx - relative offset to add to internal data.
     * \param dy - relative offset to add to internal data.
     */
    virtual void moveAround (
        const int dx,
        const int dy
    );


    /**
     * \brief Moves all sprites at once to relative offset coordinates,
     * with a given direction factor to observe.
     *
     * This method takes in account area frame constraints while moving
     * around viewport's frame boundaries.
     *
     * \param dx - relative offset to add to internal data.
     * \param dy - relative offset to add to internal data.
     * \param direction - direction XY factors to observe.
     */
    virtual void moveAround (
        const int dx,
        const int dy,
        const SDL_Point& direction
    );


    /**
     * \brief Moves all sprites at once to relative offset coordinates,
     * with a given direction factor to observe.
     *
     * This method takes in account area frame constraints while moving
     * around viewport's frame boundaries.
     *
     * \param dx - relative offset to add to internal data.
     * \param dy - relative offset to add to internal data.
     * \param direction_x - direction X factor to observe e.g. (-1, 0,
     * +1).
     * \param direction_y - direction Y factor to observe e.g. (-1, 0,
     * +1).
     */
    virtual void moveAround (
        const int dx,
        const int dy,
        const int direction_x,
        const int direction_y
    );


    /**
     * \brief Moves all sprites at once along internal data, with a
     * given direction factor to observe.
     *
     * This method takes in account area frame constraints while moving
     * around viewport's frame boundaries.
     *
     * \param direction - direction XY factors to observe.
     */
    virtual void moveDirectionAround (
        const SDL_Point& direction
    );


    /**
     * \brief Moves all sprites at once along internal data, with a
     * given direction factor to observe.
     *
     * This method takes in account area frame constraints while moving
     * around viewport's frame boundaries.
     *
     * \param direction_x - direction X factor to observe e.g. (-1, 0,
     * +1).
     * \param direction_y - direction Y factor to observe e.g. (-1, 0,
     * +1).
     */
    virtual void moveDirectionAround (
        const int direction_x,
        const int direction_y
    );


    /**
     * \brief Sets current area to new size.
     *
     * \param layer_size - frame size (width, height) - integer
     * dimensions.
     */
    virtual void setArea (const ISize& layer_size);


    /**
     * \brief Sets current area to new size.
     *
     * \param layer_width - frame width.
     * \param layer_height - frame height.
     */
    virtual void setArea (
        const int layer_width,
        const int layer_height
    );


    /**
     * \brief Updates current position along with specific constraints.
     */
    virtual void updatePosition ();
};


#endif /* _SPRITE_LAYER_AREA_HPP */
