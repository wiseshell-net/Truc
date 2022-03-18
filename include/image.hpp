/*
 * image.hpp
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

#ifndef _IMAGE_HPP
#define _IMAGE_HPP

/**
 * \file
 * \brief Image store management.
 *
 * This header file declares image store management tools.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "array.hpp"


/**
 * \brief Array indices as enumeration.
 */
enum ImageEnum
{
    #include "data/image_enum.dat"
};


/**
 * \brief External data file structure.
 */
struct ImageFile
{
    const char * const  file_name;
    const SDL_Rect      clip_rect;
};


/**
 * \brief Image store management structure.
 *
 * This structure declares a minimal API for image store management.
 *
 * \note This structure does not extend PArray because SDL_Surface
 * objects must be manually freed by SDL_FreeSurface() (C API
 * bindings).
 */
struct ImageArray : public Array<SDL_Surface *>
{

    /**
     * \brief Structure constructor.
     */
    ImageArray ();


    /**
     * \brief Structure destructor.
     */
    virtual ~ImageArray ();


    /**
     * \brief Clears array contents and frees object memory (garbage
     * collection support).
     */
    virtual void clear ();


    /**
     * \brief Gets image along enumeration index number.
     *
     * \param index - enumeration index number.
     *
     * \return pointer to existing image object.
     */
    virtual SDL_Surface * getImage (const ImageEnum& index);


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


#endif /* _IMAGE_HPP */
