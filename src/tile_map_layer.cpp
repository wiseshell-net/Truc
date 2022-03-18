/*
 * tile_map_layer.cpp
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

#include "tile_map_layer.hpp"


TileMapLayer::TileMapLayer ()
{
    DEBUG_FUNCTION_ENTER;

    row = column = rows = columns = offset_x = offset_y = 0;

    DEBUG_FUNCTION_EXIT;
}


TileMapLayer::TileMapLayer (
        const ArrayIndex& row,
        const ArrayIndex& column,
        const ArraySize& rows,
        const ArraySize& columns,
        const int offset_x,
        const int offset_y
    ) :
row (row),
column (column),
rows (rows),
columns (columns),
offset_x (offset_x),
offset_y (offset_y)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


TileMapLayer::~TileMapLayer ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


int
TileMapLayer::getTileX (
        const uint32_t& tile_width,
        const ArrayIndex& index
    ) const
{
    DEBUG_FUNCTION_CALL;

    return offset_x + tile_width * (column + (index % columns));
}


int
TileMapLayer::getTileY (
        const uint32_t& tile_height,
        const ArrayIndex& index
    ) const
{
    DEBUG_FUNCTION_CALL;

    return offset_y + tile_height * (row + (index / columns));
}


bool
TileMapLayer::isOk () const
{
    DEBUG_FUNCTION_CALL;

    return (rows && columns);
}

