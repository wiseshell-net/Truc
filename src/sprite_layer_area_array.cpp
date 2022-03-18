/*
 * sprite_layer_area_array.cpp
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

#include "sprite_layer_area_array.hpp"

#include "debug.hpp"
#include "error.hpp"


SpriteLayerAreaArray::SpriteLayerAreaArray () :
PArray (),
Drawable (),
Movable ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


SpriteLayerAreaArray::SpriteLayerAreaArray (const ArraySize& size) :
PArray (size),
Drawable (),
Movable ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


SpriteLayerAreaArray::~SpriteLayerAreaArray ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


int
SpriteLayerAreaArray::draw (SDL_Renderer * const renderer)
{
    DEBUG_FUNCTION_ENTER;

    if (renderer == nullptr)
    {
        return ERROR_EXIT_FAILURE;
    }

    int error = ERROR_EXIT_SUCCESS;

    if (is_visible)
    {
        for (SpriteLayerArea * const instance: *this)
        {
            if (instance != nullptr
                && instance->draw (renderer)
                    != ERROR_EXIT_SUCCESS)
            {
                error = ERROR_EXIT_FAILURE;
            }
        }
    }

    DEBUG_FUNCTION_EXIT;

    return error;
}


int
SpriteLayerAreaArray::draw (
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
        for (SpriteLayerArea * const instance: *this)
        {
            if (instance != nullptr
                && instance->draw (renderer, alpha)
                    != ERROR_EXIT_SUCCESS)
            {
                error = ERROR_EXIT_FAILURE;
            }
        }
    }

    DEBUG_FUNCTION_EXIT;

    return error;
}


int
SpriteLayerAreaArray::draw (
        SDL_Renderer * const renderer,
        const Color& color
    )
{
    DEBUG_FUNCTION_ENTER;

    if (renderer == nullptr)
    {
        return ERROR_EXIT_FAILURE;
    }

    int error = ERROR_EXIT_SUCCESS;

    if (is_visible && color.a)
    {
        for (SpriteLayerArea * const instance: *this)
        {
            if (instance != nullptr
                && instance->draw (renderer, color)
                    != ERROR_EXIT_SUCCESS)
            {
                error = ERROR_EXIT_FAILURE;
            }
        }
    }

    DEBUG_FUNCTION_EXIT;

    return error;
}


void
SpriteLayerAreaArray::move ()
{
    DEBUG_FUNCTION_ENTER;

    Movable::move ();

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::move (const int dx, const int dy)
{
    DEBUG_FUNCTION_ENTER;

    Movable::move (dx, dy);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::move (
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
SpriteLayerAreaArray::move (
        const int dx,
        const int dy,
        const int direction_x,
        const int direction_y
    )
{
    DEBUG_FUNCTION_ENTER;

    for (SpriteLayerArea * const instance: *this)
    {
        if (instance != nullptr)
        {
            instance->move (dx, dy, direction_x, direction_y);
        }
    }

    Movable::move (dx, dy, direction_x, direction_y);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::moveAround ()
{
    DEBUG_FUNCTION_ENTER;

    moveAround (dx, dy, direction.x, direction.y);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::moveAround (const int dx, const int dy)
{
    DEBUG_FUNCTION_ENTER;

    moveAround (dx, dy, direction.x, direction.y);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::moveAround (
        const int dx,
        const int dy,
        const SDL_Point& direction
    )
{
    DEBUG_FUNCTION_ENTER;

    moveAround (dx, dy, direction.x, direction.y);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::moveAround (
        const int dx,
        const int dy,
        const int direction_x,
        const int direction_y
    )
{
    DEBUG_FUNCTION_ENTER;

    for (SpriteLayerArea * const instance: *this)
    {
        if (instance != nullptr)
        {
            instance->moveAround (dx, dy, direction_x, direction_y);
        }
    }

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::moveDirection (const SDL_Point& direction)
{
    DEBUG_FUNCTION_ENTER;

    Movable::moveDirection (direction);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::moveDirection (
        const int direction_x,
        const int direction_y
    )
{
    DEBUG_FUNCTION_ENTER;

    Movable::moveDirection (direction_x, direction_y);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::moveDirectionAround (
        const SDL_Point& direction
    )
{
    DEBUG_FUNCTION_ENTER;

    moveAround (dx, dy, direction.x, direction.y);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::moveDirectionAround (
        const int direction_x,
        const int direction_y
    )
{
    DEBUG_FUNCTION_ENTER;

    moveAround (dx, dy, direction_x, direction_y);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::moveSelf ()
{
    DEBUG_FUNCTION_ENTER;

    for (SpriteLayerArea * const instance: *this)
    {
        if (instance != nullptr)
        {
            instance->move ();
        }
    }

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::setPosition (const SDL_Point& anchor)
{
    DEBUG_FUNCTION_ENTER;

    Movable::setPosition (anchor);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::setPosition (
        const int anchor_x,
        const int anchor_y
    )
{
    DEBUG_FUNCTION_ENTER;

    const int dx = anchor_x - anchor.x;
    const int dy = anchor_y - anchor.y;

    move (dx, dy, 1, 1);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::setPosition (
        const SDL_Point& anchor,
        const AnchorageEnum& anchorage
    )
{
    DEBUG_FUNCTION_ENTER;

    Movable::setPosition (anchor, anchorage);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerAreaArray::setPosition (
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
SpriteLayerAreaArray::updatePosition ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}

