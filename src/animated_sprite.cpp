/*
 * animated_sprite.cpp
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

#include "animated_sprite.hpp"


AnimatedSprite::AnimatedSprite () :
Sprite (),
SpriteAnimation ()
{
    DEBUG_FUNCTION_ENTER;

    tile_rect = &texture_rect;

    DEBUG_FUNCTION_EXIT;
}


AnimatedSprite::~AnimatedSprite ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


bool
AnimatedSprite::initialize (
        SDL_Renderer * const renderer,
        SDL_Surface * const tile_set_surface,
        const ArraySize& tile_set_columns,
        const uint32_t& tile_width,
        const uint32_t& tile_height
    )
{
    DEBUG_FUNCTION_ENTER;

    if (!setTexture (renderer, tile_set_surface))
    {
        return false;
    }

    this->tile_set_columns = tile_set_columns;

    texture_rect = { 0, 0, (int) tile_width, (int) tile_height };

    renderer_rect = texture_rect;

    tile_rect = &texture_rect;

    DEBUG_FUNCTION_EXIT;

    return true;
}

