/*
 * box.cpp
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

#include "box.hpp"

#include "debug.hpp"


Box::Box () :
rect (nullptr)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


Box::Box (SDL_Rect * const rect) :
rect (rect)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


Box::Box (SDL_Rect& rect) :
rect (&rect)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


Box::~Box ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


const SDL_Point
Box::bottomLeft () const
{
    DEBUG_FUNCTION_CALL;

    return (rect != nullptr) ?
        SDL_Point { rect->x, rect->y + rect->h } :
        SDL_Point ();
}


const SDL_Point
Box::bottomRight () const
{
    DEBUG_FUNCTION_CALL;

    return (rect != nullptr) ?
        SDL_Point { rect->x + rect->w, rect->y + rect->h } :
        SDL_Point ();
}


int
Box::bottomSide () const
{
    DEBUG_FUNCTION_CALL;

    return (rect != nullptr) ? (rect->y + rect->h) : 0;
}


const SDL_Rect
Box::boundingBox () const
{
    DEBUG_FUNCTION_CALL;

    return (rect != nullptr) ? *rect : SDL_Rect ();
}


const SDL_Point
Box::center () const
{
    DEBUG_FUNCTION_CALL;

    return (rect != nullptr) ?
        SDL_Point { rect->x + rect->w / 2, rect->y + rect->h / 2 } :
        SDL_Point ();
}


const ISize
Box::centroid () const
{
    DEBUG_FUNCTION_CALL;

    return (rect != nullptr) ?
        ISize { rect->w / 2, rect->h / 2 } :
        ISize ();
}


int
Box::diagonal () const
{
    DEBUG_FUNCTION_CALL;

    return (rect != nullptr) ? std::hypot (rect->w, rect->h) : 0;
}


int
Box::height () const
{
    DEBUG_FUNCTION_CALL;

    return (rect != nullptr) ? rect->h : 0;
}


bool
Box::intersects (const SDL_Rect * const other) const
{
    DEBUG_FUNCTION_CALL;

    return SDL_HasIntersection (rect, other);
}


bool
Box::intersects (const SDL_Rect& other) const
{
    DEBUG_FUNCTION_CALL;

    return SDL_HasIntersection (rect, &other);
}


bool
Box::intersects (const Box * const box) const
{
    DEBUG_FUNCTION_CALL;

    return (box != nullptr) ?
        (bool) SDL_HasIntersection (rect, box->rect) :
        false;
}


bool
Box::intersects (const Box& box) const
{
    DEBUG_FUNCTION_CALL;

    return SDL_HasIntersection (rect, box.rect);
}


int
Box::leftSide () const
{
    DEBUG_FUNCTION_CALL;

    return (rect != nullptr) ? rect->x : 0;
}


int
Box::rightSide () const
{
    DEBUG_FUNCTION_CALL;

    return (rect != nullptr) ? (rect->x + rect->w) : 0;
}


const SDL_Point
Box::topLeft () const
{
    DEBUG_FUNCTION_CALL;

    return (rect != nullptr) ?
        SDL_Point { rect->x, rect->y } :
        SDL_Point ();
}


const SDL_Point
Box::topRight () const
{
    DEBUG_FUNCTION_CALL;

    return (rect != nullptr) ?
        SDL_Point { rect->x + rect->w, rect->y } :
        SDL_Point ();
}


int
Box::topSide () const
{
    DEBUG_FUNCTION_CALL;

    return (rect != nullptr) ? rect->y : 0;
}


int
Box::width () const
{
    DEBUG_FUNCTION_CALL;

    return (rect != nullptr) ? rect->w : 0;
}

