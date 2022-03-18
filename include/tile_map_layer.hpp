/*
 * tile_map_layer.hpp
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

#ifndef _TILE_MAP_LAYER_HPP
#define _TILE_MAP_LAYER_HPP

/**
 * \file
 * \brief Tile map layer management API.
 *
 * This header file declares a minimal API for managing single tile map
 * layer.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <cstdint>

#include "array.hpp"


/**
 * \brief Tile map layer management structure.
 */
struct TileMapLayer
{
public:

    ArrayIndex  row;
    ArrayIndex  column;

    ArraySize   rows;
    ArraySize   columns;

    int         offset_x;   /* pixels */
    int         offset_y;   /* pixels */

public:

    /**
     * \brief Structure constructor.
     */
    TileMapLayer ();


    /**
     * \brief Structure constructor variant.
     *
     * Initializes object instance with given values.
     *
     * \param row       - current tile row to consider.
     * \param column    - current tile column to consider.
     * \param rows      - total number of rows in layer.
     * \param columns   - total number of columns in layer.
     * \param offset_x  - X offset coordinate for graphical mapping.
     * \param offset_y  - Y offset coordinate for graphical mapping.
     */
    TileMapLayer (
        const ArrayIndex& row,
        const ArrayIndex& column,
        const ArraySize& rows,
        const ArraySize& columns,
        const int offset_x,
        const int offset_y
    );


    /**
     * \brief Structure destructor.
     */
    virtual ~TileMapLayer ();


    /**
     * \brief Gets X coordinate for tile at given array index.
     *
     * \param tile_width    - tile width.
     * \param index         - array index of requested tile.
     *
     * \return X coordinate.
     */
    virtual int getTileX (
        const uint32_t& tile_width,
        const ArrayIndex& index
    ) const;


    /**
     * \brief Gets Y coordinate for tile at given array index.
     *
     * \param tile_height   - tile height.
     * \param index         - array index of requested tile.
     *
     * \return Y coordinate.
     */
    virtual int getTileY (
        const uint32_t& tile_height,
        const ArrayIndex& index
    ) const;


    /**
     * \brief Tells if current object instance is well initialized or
     * not.
     *
     * \return true if valid, false otherwise.
     */
    virtual bool isOk () const;

};


/**
 * \brief Multiple tile map layers array management structure.
 */
struct TileMapLayerArray : Array<TileMapLayer> {};


#endif /* _TILE_MAP_LAYER_HPP */
