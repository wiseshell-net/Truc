/*
 * tile_map.hpp
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

#ifndef _TILE_MAP_HPP
#define _TILE_MAP_HPP

/**
 * \file
 * \brief On-screen tile map sprite management API.
 *
 * This header file declares a minimal API for managing a graphical
 * tile map sprite.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <cstdint>

#include <SDL.h>
#include <SDL_image.h>

#include "array_defs.hpp"
#include "color.hpp"
#include "sprite.hpp"
#include "sprite_sheet.hpp"
#include "tile_map_layer.hpp"
#include "tile_set.hpp"


/**
 * \brief Tile map sprite management structure.
 */
struct TileMap : public Sprite
{
public:

    /**
     * \brief Structure constructor.
     */
    TileMap ();


    /**
     * \brief Structure destructor.
     */
    virtual ~TileMap ();


    /**
     * \brief Renders tile map onto internal sprite's texture.
     *
     * \param renderer - SDL renderer.
     * \param tile_set - tile mapping data source.
     * \param width - tile map width.
     * \param height - tile map height.
     * \param background_color - tile map background color, if any.
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool render (
        SDL_Renderer * const renderer,
        const TileSet& tile_set,
        const uint32_t& width,
        const uint32_t& height,
        const Color& background_color = Transparent
    );


    /**
     * \brief Renders tile map onto internal sprite's texture.
     *
     * \param renderer - SDL renderer.
     * \param tile_set_layer - tile mapping data source.
     * \param width - tile map width.
     * \param height - tile map height.
     * \param background_color - tile map background color, if any.
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool render (
        SDL_Renderer * const renderer,
        const TileSetLayer& tile_set_layer,
        const uint32_t& width,
        const uint32_t& height,
        const Color& background_color = Transparent
    );


    /**
     * \brief Renders tile map onto internal sprite's texture.
     *
     * \param renderer - SDL renderer.
     * \param sprite_sheet - tile graphics database.
     * \param tile_set_index_array - spritesheet source index array.
     * \param tile_map_layer_array - tile map destination index array.
     * \param width - tile map width.
     * \param height - tile map height.
     * \param background_color - tile map background color, if any.
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool render (
        SDL_Renderer * const renderer,
        const SpriteSheet& sprite_sheet,
        const TileSetIndexArray& tile_set_index_array,
        const TileMapLayerArray& tile_map_layer_array,
        const uint32_t& width,
        const uint32_t& height,
        const Color& background_color = Transparent
    );


    /**
     * \brief Renders tile map onto internal sprite's texture.
     *
     * \param renderer - SDL renderer.
     * \param sprite_sheet - tile graphics database.
     * \param tile_set_index_array - spritesheet source index array.
     * \param tile_set_index_array_size - number of items in source
     * index array.
     * \param tile_map_layer_array - tile map destination index array.
     * \param tile_map_layer_array_size - number of items in
     * destination index array.
     * \param width - tile map width.
     * \param height - tile map height.
     * \param background_color - tile map background color, if any.
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool render (
        SDL_Renderer * const renderer,
        const SpriteSheet& sprite_sheet,
        const TileSetIndex * const tile_set_index_array,
        const ArraySize& tile_set_index_array_size,
        const TileMapLayer * const tile_map_layer_array,
        const ArraySize& tile_map_layer_array_size,
        const uint32_t& width,
        const uint32_t& height,
        const Color& background_color = Transparent
    );

protected:

    /**
     * \brief Gets a pre-formatted SDL surface.
     *
     * \param width - surface width.
     * \param height - surface height.
     * \param background_color - surface background color, if any.
     *
     * \return pre-formatted SDL surface on success or nullptr on
     * error.
     */
    virtual SDL_Surface * newSurface (
        const uint32_t& width,
        const uint32_t& height,
        const Color& background_color
    );


    /**
     * \brief Renders one tile map layer onto others.
     *
     * \param tile_map_surface - SDL surface to work on.
     * \param sprite_sheet - tile graphics database.
     * \param tile_set_index_array - spritesheet source index array.
     * \param tile_set_index_array_size - number of items in source
     * index array.
     * \param tile_map_layer_array - tile map destination index array.
     * \param tile_map_layer_array_size - number of items in
     * destination index array.
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool renderLayer (
        SDL_Surface * const tile_map_surface,
        const SpriteSheet& sprite_sheet,
        const TileSetIndex * const tile_set_index_array,
        const ArraySize& tile_set_index_array_size,
        const TileMapLayer * const tile_map_layer_array,
        const ArraySize& tile_map_layer_array_size
    );

};


#endif /* _TILE_MAP_HPP */
