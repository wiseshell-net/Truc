/*
 * animated_sprite.hpp
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

#ifndef _ANIMATED_SPRITE_HPP
#define _ANIMATED_SPRITE_HPP

/**
 * \file
 * \brief Thread-animated sprite.
 *
 * This header file declares a minimal API for using a thread-animated
 * sprite.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <cstdint>

#include <SDL.h>

#include "array_defs.hpp"
#include "sprite_animation.hpp"
#include "sprite.hpp"


/**
 * \brief Thread-animated sprite API structure.
 *
 * This structure inherits from Sprite and SpriteAnimation structures
 * in order to simplify repetitive thread-animated sprite management.
 *
 */
struct AnimatedSprite : public Sprite, public SpriteAnimation
{
public:

    /**
     * \brief Structure constructor.
     */
    AnimatedSprite ();


    /**
     * \brief Structure destructor.
     */
    virtual ~AnimatedSprite ();


    /**
     * \brief Initializes object mappings.
     *
     * \param renderer - an SDL renderer to operate on.
     * \param tile_set_surface - an SDL surface containing all
     * animation frames (tiles) as a tile set.
     * \param tile_set_columns - max number of horizontal frames
     * (tiles) in all animation frames of the SDL surface.
     * \param tile_width - animation frame (tile) width.
     * \param tile_height - animation frame (tile) height.
     *
     * \return true if initialization went all right, false otherwise.
     */
    virtual bool initialize (
        SDL_Renderer * const renderer,
        SDL_Surface * const tile_set_surface,
        const ArraySize& tile_set_columns,
        const uint32_t& tile_width,
        const uint32_t& tile_height
    );
};


#endif /* _ANIMATED_SPRITE_HPP */
