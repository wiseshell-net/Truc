/*
 * tile_set.cpp
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

#include "tile_set.hpp"


TileSetLayer::TileSetLayer () :
sprite_sheet (),
tile_set_index_array (),
tile_map_layer_array ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


TileSetLayer::TileSetLayer (
        const SpriteSheet& sprite_sheet,
        const TileSetIndexArray& tile_set_index_array,
        const TileMapLayerArray& tile_map_layer_array
    ) :
sprite_sheet (sprite_sheet),
tile_set_index_array (tile_set_index_array),
tile_map_layer_array (tile_map_layer_array)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


TileSetLayer::~TileSetLayer ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}

