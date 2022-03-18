/*
 * sprite_sheet.hpp
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

#ifndef _SPRITE_SHEET_HPP
#define _SPRITE_SHEET_HPP

/**
 * \file
 * \brief Generic spritesheet management API.
 *
 * This header file declares a minimal API for generic spritesheet
 * management.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <cstdint>
#include <string>

#include "array_defs.hpp"


/**
 * \brief Generic spritesheet management structure.
 *
 * A spritesheet is a graphical image file that might be seen as a rows
 * by columns matrix of fixed size tiles.
 *
 * It is also considered as graphical tile database for tile mappings.
 */
struct SpriteSheet
{
public:

    std::string file_path;

    ArraySize   rows;
    ArraySize   columns;

    /**
     * \brief Internal tile holder structure.
     */
    struct Tile
    {
        uint32_t    width;
        uint32_t    height;
        uint32_t    spacing_x;
        uint32_t    spacing_y;

    }           tile;

public:

    /**
     * \brief Structure constructor.
     */
    SpriteSheet ();


    /**
     * \brief Structure constructor variant.
     *
     * Initializes object instance with given values.
     *
     * \param file_path - path to spritesheet image file.
     * \param rows      - number of rows in spritesheet.
     * \param columns   - number of columns in spritesheet.
     * \param tile_width     - fixed width of each tile in spritesheet.
     * \param tile_height    - fixed height of each tile.
     * \param tile_spacing_x - spacing between each tile (X dimension).
     * \param tile_spacing_y - spacing between each tile (Y dimension).
     */
    SpriteSheet (
        const std::string& file_path,
        const ArraySize& rows,
        const ArraySize& columns,
        const uint32_t& tile_width,
        const uint32_t& tile_height,
        const uint32_t& tile_spacing_x,
        const uint32_t& tile_spacing_y
    );


    /**
     * \brief Structure destructor.
     */
    virtual ~SpriteSheet ();


    /**
     * \brief Gets X coordinate for tile at given array index.
     *
     * \param index - array index of requested tile.
     *
     * \return X coordinate.
     */
    virtual int getTileX (const ArrayIndex& index) const;


    /**
     * \brief Gets Y coordinate for tile at given array index.
     *
     * \param index - array index of requested tile.
     *
     * \return Y coordinate.
     */
    virtual int getTileY (const ArrayIndex& index) const;


    /**
     * \brief Tells if current object instance is well initialized or
     * not.
     *
     * \return true if valid, false otherwise.
     */
    virtual bool isOk () const;


    /**
     * \brief Sets up object instance matrix.
     *
     * \param rows      - number of rows in matrix grid.
     * \param columns   - number of columns in matrix grid.
     */
    virtual void setMatrix (
        const ArrayIndex& rows,
        const ArraySize& columns
    );


    /**
     * \brief Sets up object instance tile dimensions.
     *
     * \param width     - fixed width of each tile in spritesheet.
     * \param height    - fixed height of each tile.
     * \param spacing_x - spacing between each tile (X dimension).
     * \param spacing_y - spacing between each tile (Y dimension).
     */
    virtual void setTile (
        const uint32_t& width,
        const uint32_t& height,
        const uint32_t& spacing_x,
        const uint32_t& spacing_y
    );

};


#endif /* _SPRITE_SHEET_HPP */
