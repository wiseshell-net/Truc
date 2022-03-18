/*
 * tile_map.cpp
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

#include "tile_map.hpp"

#include "debug.hpp"
#include "error.hpp"


TileMap::TileMap () :
Sprite ()
{
    DEBUG_FUNCTION_ENTER;

    setPosition (0, 0, ANCHOR_NORTH_WEST);

    DEBUG_FUNCTION_EXIT;
}


TileMap::~TileMap ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


SDL_Surface *
TileMap::newSurface (
        const uint32_t& width,
        const uint32_t& height,
        const Color& background_color
    )
{
    DEBUG_FUNCTION_ENTER;

    SDL_Surface * surface = nullptr;

    if (width && height)
    {
        surface = SDL_CreateRGBSurfaceWithFormat
            (0, width, height, 32, SDL_PIXELFORMAT_RGBA32);

        if (surface != nullptr)
        {
            SDL_SetSurfaceBlendMode (surface, SDL_BLENDMODE_BLEND);

            SDL_FillRect (
                surface,
                nullptr,
                SDL_MapRGBA (
                    surface->format,
                    background_color.r,
                    background_color.g,
                    background_color.b,
                    background_color.a
                )
            );
        }
    }

    DEBUG_FUNCTION_EXIT;

    return surface;
}


bool
TileMap::render (
        SDL_Renderer * const renderer,
        const TileSet& tile_set,
        const uint32_t& width,
        const uint32_t& height,
        const Color& background_color
    )
{
    DEBUG_FUNCTION_ENTER;

    if (renderer != nullptr && !tile_set.empty ())
    {
        SDL_Surface * surface =
            newSurface (width, height, background_color);

        if (surface != nullptr)
        {
            for (const TileSetLayer& tile_set_layer: tile_set)
            {
                renderLayer (
                    surface,
                    tile_set_layer.sprite_sheet,
                    tile_set_layer.tile_set_index_array.data (),
                    tile_set_layer.tile_set_index_array.size (),
                    tile_set_layer.tile_map_layer_array.data (),
                    tile_set_layer.tile_map_layer_array.size ()
                );
            }

            setTexture (renderer, surface);

            SDL_FreeSurface (surface);

            return true;
        }
    }

    DEBUG_FUNCTION_EXIT;

    return false;
}


bool
TileMap::render (
        SDL_Renderer * const renderer,
        const TileSetLayer& tile_set_layer,
        const uint32_t& width,
        const uint32_t& height,
        const Color& background_color
    )
{
    DEBUG_FUNCTION_ENTER;

    if (renderer != nullptr)
    {
        SDL_Surface * surface =
            newSurface (width, height, background_color);

        renderLayer (
            surface,
            tile_set_layer.sprite_sheet,
            tile_set_layer.tile_set_index_array.data (),
            tile_set_layer.tile_set_index_array.size (),
            tile_set_layer.tile_map_layer_array.data (),
            tile_set_layer.tile_map_layer_array.size ()
        );

        setTexture (renderer, surface);

        SDL_FreeSurface (surface);

        return true;
    }

    DEBUG_FUNCTION_EXIT;

    return false;
}


bool
TileMap::render (
        SDL_Renderer * const renderer,
        const SpriteSheet& sprite_sheet,
        const TileSetIndexArray& tile_set_index_array,
        const TileMapLayerArray& tile_map_layer_array,
        const uint32_t& width,
        const uint32_t& height,
        const Color& background_color
    )
{
    DEBUG_FUNCTION_ENTER;

    if (renderer != nullptr)
    {
        SDL_Surface * surface =
            newSurface (width, height, background_color);

        renderLayer (
            surface,
            sprite_sheet,
            tile_set_index_array.data (),
            tile_set_index_array.size (),
            tile_map_layer_array.data (),
            tile_map_layer_array.size ()
        );

        setTexture (renderer, surface);

        SDL_FreeSurface (surface);

        return true;
    }

    DEBUG_FUNCTION_EXIT;

    return false;
}


bool
TileMap::render (
        SDL_Renderer * const renderer,
        const SpriteSheet& sprite_sheet,
        const TileSetIndex * const tile_set_index_array,
        const ArraySize& tile_set_index_array_size,
        const TileMapLayer * const tile_map_layer_array,
        const ArraySize& tile_map_layer_array_size,
        const uint32_t& width,
        const uint32_t& height,
        const Color& background_color
    )
{
    DEBUG_FUNCTION_ENTER;

    if (renderer != nullptr)
    {
        SDL_Surface * surface =
            newSurface (width, height, background_color);

        renderLayer (
            surface,
            sprite_sheet,
            tile_set_index_array,
            tile_set_index_array_size,
            tile_map_layer_array,
            tile_map_layer_array_size
        );

        setTexture (renderer, surface);

        SDL_FreeSurface (surface);

        return true;
    }

    DEBUG_FUNCTION_EXIT;

    return false;
}


bool
TileMap::renderLayer (
        SDL_Surface * const tile_map_surface,
        const SpriteSheet& sprite_sheet,
        const TileSetIndex * const tile_set_index_array,
        const ArraySize& tile_set_index_array_size,
        const TileMapLayer * const tile_map_layer_array,
        const ArraySize& tile_map_layer_array_size
    )
{
    DEBUG_FUNCTION_ENTER;

    if (tile_map_surface == nullptr
        || !sprite_sheet.isOk ()
        || tile_set_index_array == nullptr
        || !tile_set_index_array_size
        || tile_map_layer_array == nullptr
        || !tile_map_layer_array_size)
    {
        return false;
    }

    SDL_Surface * tile_set_surface =
        IMG_Load (sprite_sheet.file_path.c_str ());

    if (tile_set_surface == nullptr)
    {
        return false;
    }

    SDL_SetSurfaceBlendMode (tile_set_surface, SDL_BLENDMODE_BLEND);

    SDL_Rect tile_set_rectangle =
    {
        0,
        0,
        (int) sprite_sheet.tile.width,
        (int) sprite_sheet.tile.height
    };

    SDL_Rect tile_map_rectangle = tile_set_rectangle;

    ArrayIndex tile_set_index_array_index = 0;

    int ret = ERROR_EXIT_SUCCESS;

    for (ArrayIndex i = 0;
        ret == ERROR_EXIT_SUCCESS &&
        tile_set_index_array_index < tile_set_index_array_size
        && i < tile_map_layer_array_size;
        i++)
    {
        const TileMapLayer& tile_map_layer = tile_map_layer_array [i];

        if (!tile_map_layer.isOk ()) continue;

        const ArraySize size = std::fmin (
            tile_set_index_array_size,
            tile_set_index_array_index +
                tile_map_layer.rows * tile_map_layer.columns
        );

        for (ArrayIndex j = tile_set_index_array_index;
            ret == ERROR_EXIT_SUCCESS && j < size;
            j++)
        {
            const ArrayIndex k = j - tile_set_index_array_index;

            const TileSetIndex& tile_set_index =
                tile_set_index_array [j];

            tile_set_rectangle.x =
                sprite_sheet.getTileX (tile_set_index);

            tile_set_rectangle.y =
                sprite_sheet.getTileY (tile_set_index);

            tile_map_rectangle.x =
                tile_map_layer.getTileX (sprite_sheet.tile.width, k);

            tile_map_rectangle.y =
                tile_map_layer.getTileY (sprite_sheet.tile.height, k);

            ret = SDL_BlitSurface (
                tile_set_surface,
                &tile_set_rectangle,
                tile_map_surface,
                &tile_map_rectangle
            );
        }

        tile_set_index_array_index += size;
    }

    SDL_FreeSurface (tile_set_surface);

    DEBUG_FUNCTION_EXIT;

    return (ret == ERROR_EXIT_SUCCESS);
}

