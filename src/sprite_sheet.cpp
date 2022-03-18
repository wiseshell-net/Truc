/*
 * sprite_sheet.cpp
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

#include "sprite_sheet.hpp"

#include "debug.hpp"


SpriteSheet::SpriteSheet () :
file_path ()
{
    DEBUG_FUNCTION_ENTER;

    setMatrix (0, 0);

    setTile (0, 0, 0, 0);

    DEBUG_FUNCTION_EXIT;
}


SpriteSheet::SpriteSheet (
        const std::string& file_path,
        const ArraySize& rows,
        const ArraySize& columns,
        const uint32_t& tile_width,
        const uint32_t& tile_height,
        const uint32_t& tile_spacing_x,
        const uint32_t& tile_spacing_y
    ) :
file_path (file_path)
{
    DEBUG_FUNCTION_ENTER;

    setMatrix (rows, columns);

    setTile (tile_width, tile_height, tile_spacing_x, tile_spacing_y);

    DEBUG_FUNCTION_EXIT;
}


SpriteSheet::~SpriteSheet ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


int
SpriteSheet::getTileX (const ArrayIndex& index) const
{
    DEBUG_FUNCTION_CALL;

    return (tile.width + tile.spacing_x) * (index % columns);
}


int
SpriteSheet::getTileY (const ArrayIndex& index) const
{
    DEBUG_FUNCTION_CALL;

    return (tile.height + tile.spacing_y) * (index / columns);
}


bool
SpriteSheet::isOk () const
{
    DEBUG_FUNCTION_CALL;

    return (!file_path.empty()
            && rows
            && columns
            && tile.width
            && tile.height);
}


void
SpriteSheet::setMatrix (
        const ArrayIndex& rows_,
        const ArraySize& columns_
    )
{
    DEBUG_FUNCTION_ENTER;

    rows = rows_;
    columns = columns_;

    DEBUG_FUNCTION_EXIT;
}


void
SpriteSheet::setTile (
        const uint32_t& width,
        const uint32_t& height,
        const uint32_t& spacing_x,
        const uint32_t& spacing_y
    )
{
    DEBUG_FUNCTION_ENTER;

    tile = { width, height, spacing_x, spacing_y };

    DEBUG_FUNCTION_EXIT;
}

