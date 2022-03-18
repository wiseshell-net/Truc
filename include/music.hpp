/*
 * music.hpp
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

#ifndef _MUSIC_HPP
#define _MUSIC_HPP

/**
 * \file
 * \brief Music store management.
 *
 * This header file declares music store management tools.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <string>

#include <SDL_mixer.h>

#include "array.hpp"


/**
 * \brief Array indices as enumeration.
 */
enum MusicEnum
{
    #include "data/music_enum.dat"
};


/**
 * \brief External data file structure.
 */
struct MusicFile
{
    const char * const  file_name;
};


/**
 * \brief Music store management structure.
 *
 * This structure declares a minimal API for music store management.
 *
 * \note This structure does not extend PArray because Mix_Music
 * objects must be manually freed by Mix_FreeMusic() (C API bindings).
 */
struct MusicArray : public Array<Mix_Music *>
{

    /**
     * \brief Structure constructor.
     */
    MusicArray ();


    /**
     * \brief Structure destructor.
     */
    virtual ~MusicArray ();


    /**
     * \brief Clears array contents and frees object memory (garbage
     * collection support).
     */
    virtual void clear ();


    /**
     * \brief Gets music along enumeration index number.
     *
     * \param index - enumeration index number.
     *
     * \return pointer to existing music object.
     */
    virtual Mix_Music * getMusic (const MusicEnum& index);


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


#endif /* _MUSIC_HPP */
