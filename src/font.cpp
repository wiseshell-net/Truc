/*
 * font.cpp
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

#include "font.hpp"

#include "debug.hpp"
#include "error.hpp"


FontArray::FontArray () :
Array ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


FontArray::~FontArray ()
{
    DEBUG_FUNCTION_ENTER;

    clear ();

    DEBUG_FUNCTION_EXIT;
}


void
FontArray::clear ()
{
    DEBUG_FUNCTION_ENTER;

    for (auto * const instance: *this)
    {
        TTF_CloseFont (instance);
    }

    Debug::info ("cleared %zu items.", size ());

    Array::clear ();

    DEBUG_FUNCTION_EXIT;
}


TTF_Font *
FontArray::getFont (const FontEnum& index)
{
    DEBUG_FUNCTION_CALL;

    return empty () ? nullptr : at (index);
}


bool
FontArray::loadAll (const std::string& directory_path)
{
    DEBUG_FUNCTION_ENTER;

    if (directory_path.empty ())
    {
        return Error::runtimeError (
            "Unable to load fonts.",
            __func__,
            "Invalid directory path."
        );
    }

    const FontFile files [] = {

        #include "data/font_files.dat"

    };

    const ArraySize n_files = ARRAY_SIZE (files);

    clear ();

    resize (n_files);

    std::string file_path;

    for (ArrayIndex i = 0; i < n_files; i++)
    {
        file_path = directory_path + files[i].file_name;

        Debug::info ("File path: '%s'", file_path.c_str ());

        TTF_Font * const font = TTF_OpenFont (
            file_path.c_str (),
            files[i].font_size_pt
        );

        if (font == nullptr)
        {
            clear ();

            return Error::sdlError ("Unable to load font file.");
        }

        at (i) = font;
    }

    DEBUG_FUNCTION_EXIT;

    return true;
}

