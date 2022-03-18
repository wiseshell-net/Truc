/*
 * image.cpp
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

#include "image.hpp"

#include "debug.hpp"
#include "error.hpp"


ImageArray::ImageArray () :
Array ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


ImageArray::~ImageArray ()
{
    DEBUG_FUNCTION_ENTER;

    clear ();

    DEBUG_FUNCTION_EXIT;
}


void
ImageArray::clear ()
{
    DEBUG_FUNCTION_ENTER;

    for (auto * const instance: *this)
    {
        SDL_FreeSurface (instance);
    }

    Debug::info ("cleared %zu items.", size ());

    Array::clear ();

    DEBUG_FUNCTION_EXIT;
}


SDL_Surface *
ImageArray::getImage (const ImageEnum& index)
{
    DEBUG_FUNCTION_CALL;

    return empty () ? nullptr : at (index);
}


bool
ImageArray::loadAll (const std::string& directory_path)
{
    DEBUG_FUNCTION_ENTER;

    if (directory_path.empty ())
    {
        return Error::runtimeError (
            "Unable to load images.",
            __func__,
            "Invalid directory path."
        );
    }

    const ImageFile files [] = {

        #include "data/image_files.dat"

    };

    const ArraySize n_files = ARRAY_SIZE (files);

    clear ();

    resize (n_files);

    std::string file_path;

    for (ArrayIndex i = 0; i < n_files; i++)
    {
        file_path = directory_path + files[i].file_name;

        Debug::info ("File path: '%s'", file_path.c_str ());

        SDL_Surface * const image = IMG_Load (file_path.c_str ());

        if (image == nullptr)
        {
            clear ();

            return Error::sdlError ("Unable to load image file.");
        }

        if (files[i].clip_rect.w != 0 && files[i].clip_rect.h != 0)
        {
            SDL_SetClipRect (image, &files[i].clip_rect);
        }

        at (i) = image;
    }

    DEBUG_FUNCTION_EXIT;

    return true;
}

