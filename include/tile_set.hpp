/*
 * tile_set.hpp
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

#ifndef _TILE_SET_HPP
#define _TILE_SET_HPP

/**
 * \file
 * \brief Tile set management API.
 *
 * This header file declares a minimal API for managing graphical tile
 * sets.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include "array.hpp"
#include "sprite_sheet.hpp"
#include "tile_defs.hpp"
#include "tile_map_layer.hpp"


/**
 * \brief Tile set source index array management structure.
 */
struct TileSetIndexArray : Array<TileSetIndex> {};


/**
 * \brief Tile set layer management structure (tile mapping data
 * source).
 */
struct TileSetLayer
{
public:

    SpriteSheet         sprite_sheet;
    TileSetIndexArray   tile_set_index_array;
    TileMapLayerArray   tile_map_layer_array;

public:

    /**
     * \brief Structure constructor.
     */
    TileSetLayer ();


    /**
     * \brief Structure constructor variant.
     *
     * Initializes object instance with given values.
     *
     * \param sprite_sheet - tile graphics database.
     * \param tile_set_index_array - spritesheet source index array.
     * \param tile_map_layer_array - tile map destination index array.
     */
    explicit TileSetLayer (
        const SpriteSheet& sprite_sheet,
        const TileSetIndexArray& tile_set_index_array,
        const TileMapLayerArray& tile_map_layer_array
    );


    /**
     * \brief Structure destructor.
     */
    virtual ~TileSetLayer ();

};


/**
 * \brief Multiple tile set layers array management structure.
 */
struct TileSetLayerArray : Array<TileSetLayer> {};


/**
 * \brief Type definition for multiple tile set layers array management
 * (synonym).
 */
typedef struct TileSetLayerArray TileSet;


#endif /* _TILE_SET_HPP */
