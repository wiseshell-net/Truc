/*
 * render.cpp
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

#include "render.hpp"

#include "debug.hpp"
#include "error.hpp"


namespace Render
{

int
clear (SDL_Renderer * const renderer, const Color& color)
{
    DEBUG_FUNCTION_CALL;

    if (renderer == nullptr
        || setDrawColor (renderer, color) != ERROR_EXIT_SUCCESS)
    {
        return ERROR_EXIT_FAILURE;
    }

    return SDL_RenderClear (renderer);
}


void
display (SDL_Renderer * const renderer)
{
    DEBUG_FUNCTION_ENTER;

    SDL_RenderPresent (renderer);

    DEBUG_FUNCTION_EXIT;
}


int
setDrawColor (SDL_Renderer * const renderer, const Color& color)
{
    DEBUG_FUNCTION_CALL;

    return SDL_SetRenderDrawColor
        (renderer, color.r, color.g, color.b, color.a);
}

} /* namespace */

