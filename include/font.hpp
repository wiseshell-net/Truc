/*
 * font.hpp
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

#ifndef _FONT_HPP
#define _FONT_HPP

/**
 * \file
 * \brief Font store management.
 *
 * This header file declares font store management tools.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <cstdint>
#include <string>

#include <SDL_ttf.h>

#include "array.hpp"


/**
 * \brief Array indices as enumeration.
 */
enum FontEnum
{
    #include "data/font_enum.dat"
};


/**
 * \brief External data file structure.
 */
struct FontFile
{
    const char * const  file_name;
    const uint16_t      font_size_pt;
};


/**
 * \brief Font store management structure.
 *
 * This structure declares a minimal API for font store management.
 *
 * \note This structure does not extend PArray because TTF_Font objects
 * must be manually freed by TTF_CloseFont() (C API bindings).
 *
 */
struct FontArray : public Array<TTF_Font *>
{

    /**
     * \brief Structure constructor.
     */
    FontArray ();


    /**
     * \brief Structure destructor.
     */
    virtual ~FontArray ();


    /**
     * \brief Clears array contents and frees object memory (garbage
     * collection support).
     */
    virtual void clear ();


    /**
     * \brief Gets font along enumeration index number.
     *
     * \param index - enumeration index number.
     *
     * \return pointer to existing font object.
     */
    virtual TTF_Font * getFont (const FontEnum& index);


    /**
     * \brief Loads all external data files contained in a given
     * directory.
     *
     * \param directory_path - string of chars, may be a relative or an
     * absolute path to required directory.
     *
     * \return true if all has been loaded OK, false otherwise.
     */
    virtual bool loadAll (const std::string& directory_path);
};


#endif /* _FONT_HPP */
