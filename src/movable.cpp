/*
 * movable.cpp
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

#include "movable.hpp"

#include "debug.hpp"


Movable::Movable () :
anchorage (ANCHOR_CENTER),
anchor { 0, 0 },
direction { 1, 1 },
dx (0),
dy (0)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


Movable::~Movable ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


void
Movable::move ()
{
    DEBUG_FUNCTION_ENTER;

    move (dx, dy, direction.x, direction.y);

    DEBUG_FUNCTION_EXIT;
}


void
Movable::move (const int dx, const int dy)
{
    DEBUG_FUNCTION_ENTER;

    move (dx, dy, direction.x, direction.y);

    DEBUG_FUNCTION_EXIT;
}


void
Movable::move (
        const int dx,
        const int dy,
        const SDL_Point& direction
    )
{
    DEBUG_FUNCTION_ENTER;

    move (dx, dy, direction.x, direction.y);

    DEBUG_FUNCTION_EXIT;
}


void
Movable::move (
        const int dx,
        const int dy,
        const int direction_x,
        const int direction_y
    )
{
    DEBUG_FUNCTION_ENTER;

    anchor.x += dx * direction_x;
    anchor.y += dy * direction_y;

    updatePosition ();

    DEBUG_FUNCTION_EXIT;
}


void
Movable::moveDirection (const SDL_Point& direction)
{
    DEBUG_FUNCTION_ENTER;

    move (dx, dy, direction.x, direction.y);

    DEBUG_FUNCTION_EXIT;
}


void
Movable::moveDirection (
        const int direction_x,
        const int direction_y
    )
{
    DEBUG_FUNCTION_ENTER;

    move (dx, dy, direction_x, direction_y);

    DEBUG_FUNCTION_EXIT;
}


void
Movable::setPosition (const SDL_Point& anchor)
{
    DEBUG_FUNCTION_ENTER;

    setPosition (anchor.x, anchor.y);

    DEBUG_FUNCTION_EXIT;
}


void
Movable::setPosition (const int anchor_x, const int anchor_y)
{
    DEBUG_FUNCTION_ENTER;

    anchor = { anchor_x, anchor_y };

    updatePosition ();

    DEBUG_FUNCTION_EXIT;
}


void
Movable::setPosition (
        const int anchor_x,
        const int anchor_y,
        const AnchorageEnum& anchorage_
    )
{
    DEBUG_FUNCTION_ENTER;

    anchorage = anchorage_;

    setPosition (anchor_x, anchor_y);

    DEBUG_FUNCTION_EXIT;
}


void
Movable::setPosition (
        const SDL_Point& anchor,
        const AnchorageEnum& anchorage
    )
{
    DEBUG_FUNCTION_ENTER;

    setPosition (anchor.x, anchor.y, anchorage);

    DEBUG_FUNCTION_EXIT;
}

