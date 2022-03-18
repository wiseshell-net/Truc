/*
 * sprite_array.cpp
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

#include "sprite_array.hpp"

#include "debug.hpp"
#include "error.hpp"


SpriteArray::SpriteArray () :
Array (),
Drawable (),
Movable ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


SpriteArray::SpriteArray (const ArraySize& size) :
Array (size),
Drawable (),
Movable ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


SpriteArray::~SpriteArray ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


int
SpriteArray::draw (SDL_Renderer * const renderer)
{
    DEBUG_FUNCTION_ENTER;

    if (renderer == nullptr)
    {
        return ERROR_EXIT_FAILURE;
    }

    int error = ERROR_EXIT_SUCCESS;

    if (is_visible)
    {
        for (Sprite& instance: *this)
        {
            if (instance.draw (renderer) != ERROR_EXIT_SUCCESS)
            {
                error = ERROR_EXIT_FAILURE;
            }
        }
    }

    DEBUG_FUNCTION_EXIT;

    return error;
}


int
SpriteArray::draw (
        SDL_Renderer * const renderer,
        const ColorChannel& alpha
    )
{
    DEBUG_FUNCTION_ENTER;

    if (renderer == nullptr)
    {
        return ERROR_EXIT_FAILURE;
    }

    int error = ERROR_EXIT_SUCCESS;

    if (is_visible && alpha)
    {
        for (Sprite& instance: *this)
        {
            if (instance.draw (renderer, alpha) != ERROR_EXIT_SUCCESS)
            {
                error = ERROR_EXIT_FAILURE;
            }
        }
    }

    DEBUG_FUNCTION_EXIT;

    return error;
}


int
SpriteArray::draw (SDL_Renderer * const renderer, const Color& color)
{
    DEBUG_FUNCTION_ENTER;

    if (renderer == nullptr)
    {
        return ERROR_EXIT_FAILURE;
    }

    int error = ERROR_EXIT_SUCCESS;

    if (is_visible && color.a)
    {
        for (Sprite& instance: *this)
        {
            if (instance.draw (renderer, color) != ERROR_EXIT_SUCCESS)
            {
                error = ERROR_EXIT_FAILURE;
            }
        }
    }

    DEBUG_FUNCTION_EXIT;

    return error;
}


void
SpriteArray::move ()
{
    DEBUG_FUNCTION_ENTER;

    Movable::move ();

    DEBUG_FUNCTION_EXIT;
}


void
SpriteArray::move (const int dx, const int dy)
{
    DEBUG_FUNCTION_ENTER;

    Movable::move (dx, dy);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteArray::move (
        const int dx,
        const int dy,
        const SDL_Point& direction
    )
{
    DEBUG_FUNCTION_ENTER;

    Movable::move (dx, dy, direction);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteArray::move (
        const int dx,
        const int dy,
        const int direction_x,
        const int direction_y
    )
{
    DEBUG_FUNCTION_ENTER;

    for (Sprite& instance: *this)
    {
        instance.move (dx, dy, direction_x, direction_y);
    }

    Movable::move (dx, dy, direction_x, direction_y);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteArray::moveDirection (const SDL_Point& direction)
{
    DEBUG_FUNCTION_ENTER;

    Movable::moveDirection (direction);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteArray::moveDirection (
        const int direction_x,
        const int direction_y
    )
{
    DEBUG_FUNCTION_ENTER;

    Movable::moveDirection (direction_x, direction_y);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteArray::moveSelf ()
{
    DEBUG_FUNCTION_ENTER;

    for (Sprite& instance: *this)
    {
        instance.move ();
    }

    DEBUG_FUNCTION_EXIT;
}


void
SpriteArray::setPosition (const SDL_Point& anchor)
{
    DEBUG_FUNCTION_ENTER;

    Movable::setPosition (anchor);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteArray::setPosition (const int anchor_x, const int anchor_y)
{
    DEBUG_FUNCTION_ENTER;

    const int dx = anchor_x - anchor.x;
    const int dy = anchor_y - anchor.y;

    move (dx, dy, 1, 1);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteArray::setPosition (
        const SDL_Point& anchor,
        const AnchorageEnum& anchorage
    )
{
    DEBUG_FUNCTION_ENTER;

    Movable::setPosition (anchor, anchorage);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteArray::setPosition (
        const int anchor_x,
        const int anchor_y,
        const AnchorageEnum& anchorage
    )
{
    DEBUG_FUNCTION_ENTER;

    Movable::setPosition (anchor_x, anchor_y, anchorage);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteArray::updatePosition ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}

