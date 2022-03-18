/*
 * sound.cpp
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

#include "sound.hpp"

#include "debug.hpp"
#include "error.hpp"


SoundArray::SoundArray () :
Array ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


SoundArray::~SoundArray ()
{
    DEBUG_FUNCTION_ENTER;

    clear ();

    DEBUG_FUNCTION_EXIT;
}


void
SoundArray::clear ()
{
    DEBUG_FUNCTION_ENTER;

    for (auto * const instance: *this)
    {
        Mix_FreeChunk (instance);
    }

    Debug::info ("cleared %zu items.", size ());

    Array::clear ();

    DEBUG_FUNCTION_EXIT;
}


void
SoundArray::emitSound (const SoundEnum& index)
{
    DEBUG_FUNCTION_ENTER;

    Mix_PlayChannel (-1, getSound (index), 0);

    DEBUG_FUNCTION_EXIT;
}


Mix_Chunk *
SoundArray::getSound (const SoundEnum& index)
{
    DEBUG_FUNCTION_CALL;

    return empty () ? nullptr : at (index);
}


bool
SoundArray::loadAll (const std::string& directory_path)
{
    DEBUG_FUNCTION_ENTER;

    if (directory_path.empty ())
    {
        return Error::runtimeError (
            "Unable to load sounds.",
            __func__,
            "Invalid directory path."
        );
    }

    const SoundFile files [] = {

        #include "data/sound_files.dat"

    };

    const ArraySize n_files = ARRAY_SIZE (files);

    clear ();

    resize (n_files);

    std::string file_path;

    for (ArrayIndex i = 0; i < n_files; i++)
    {
        file_path = directory_path + files[i].file_name;

        Debug::info ("File path: '%s'", file_path.c_str ());

        Mix_Chunk * const sound = Mix_LoadWAV (file_path.c_str ());

        if (sound == nullptr)
        {
            clear ();

            return Error::sdlError ("Unable to load sound file.");
        }

        Mix_VolumeChunk (
            sound,
            (MIX_MAX_VOLUME * files[i].volume) / 100
        );

        at (i) = sound;
    }

    DEBUG_FUNCTION_EXIT;

    return true;
}

