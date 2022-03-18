/*
 * music.cpp
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

#include "music.hpp"

#include "debug.hpp"
#include "error.hpp"


MusicArray::MusicArray () :
Array ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


MusicArray::~MusicArray ()
{
    DEBUG_FUNCTION_ENTER;

    clear ();

    DEBUG_FUNCTION_EXIT;
}


void
MusicArray::clear ()
{
    DEBUG_FUNCTION_ENTER;

    for (auto * const instance: *this)
    {
        Mix_FreeMusic (instance);
    }

    Debug::info ("cleared %zu items.", size ());

    Array::clear ();

    DEBUG_FUNCTION_EXIT;
}


Mix_Music *
MusicArray::getMusic (const MusicEnum& index)
{
    DEBUG_FUNCTION_CALL;

    return empty () ? nullptr : at (index);
}


bool
MusicArray::loadAll (const std::string& directory_path)
{
    DEBUG_FUNCTION_ENTER;

    if (directory_path.empty ())
    {
        return Error::runtimeError (
            "Unable to load musics.",
            __func__,
            "Invalid directory path."
        );
    }

    const MusicFile files [] = {

        #include "data/music_files.dat"

    };

    const ArraySize n_files = ARRAY_SIZE (files);

    clear ();

    resize (n_files);

    std::string file_path;

    for (ArrayIndex i = 0; i < n_files; i++)
    {
        file_path = directory_path + files[i].file_name;

        Debug::info ("File path: '%s'", file_path.c_str ());

        Mix_Music * const music = Mix_LoadMUS (file_path.c_str ());

        if (music == nullptr)
        {
            clear ();

            return Error::sdlError ("Unable to load music file.");
        }

        at (i) = music;
    }

    DEBUG_FUNCTION_EXIT;

    return true;
}

