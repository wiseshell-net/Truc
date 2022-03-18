/*
 * sprite_layer_area.cpp
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

#include "sprite_layer_area.hpp"


SpriteLayerArea::SpriteLayerArea () :
SpriteLayer (),
frame_rect { 0, 0, 0, 0 },
viewport_rect { 0, 0, 0, 0 },
box (frame_rect)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


SpriteLayerArea::SpriteLayerArea (const ArraySize& size) :
SpriteLayer (size),
frame_rect { 0, 0, 0, 0 },
viewport_rect { 0, 0, 0, 0 },
box (frame_rect)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


SpriteLayerArea::~SpriteLayerArea ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


const ISize
SpriteLayerArea::area () const
{
    DEBUG_FUNCTION_CALL;

    return { frame_rect.w, frame_rect.h };
}


void
SpriteLayerArea::moveAround ()
{
    DEBUG_FUNCTION_ENTER;

    moveAround (dx, dy, direction.x, direction.y);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerArea::moveAround (const int dx, const int dy)
{
    DEBUG_FUNCTION_ENTER;

    moveAround (dx, dy, direction.x, direction.y);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerArea::moveAround (
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
SpriteLayerArea::moveAround (
        const int dx,
        const int dy,
        const int direction_x,
        const int direction_y
    )
{
    DEBUG_FUNCTION_ENTER;

    if (frame_rect.w <= viewport_rect.w
        || frame_rect.h <= viewport_rect.h)
    {
        return;
    }

    move (dx, dy, direction_x, direction_y);

    if (frame_rect.x > viewport_rect.x)
    {
        move (viewport_rect.x - frame_rect.x, 0, 1, 1);
        direction.x = 0;
    }
    else
    {
        const int fx = frame_rect.x + frame_rect.w;
        const int vx = viewport_rect.x + viewport_rect.w;

        if (fx < vx)
        {
            move (vx - fx, 0, 1, 1);
            direction.x = 0;
        }
    }

    if (frame_rect.y > viewport_rect.y)
    {
        move (0, viewport_rect.y - frame_rect.y, 1, 1);
        direction.y = 0;
    }
    else
    {
        const int fy = frame_rect.y + frame_rect.h;
        const int vy = viewport_rect.y + viewport_rect.h;

        if (fy < vy)
        {
            move (0, vy - fy, 1, 1);
            direction.y = 0;
        }
    }

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerArea::moveDirectionAround (const SDL_Point& direction)
{
    DEBUG_FUNCTION_ENTER;

    moveAround (dx, dy, direction.x, direction.y);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerArea::moveDirectionAround (
        const int direction_x,
        const int direction_y
    )
{
    DEBUG_FUNCTION_ENTER;

    moveAround (dx, dy, direction_x, direction_y);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerArea::setArea (const ISize& layer_size)
{
    DEBUG_FUNCTION_ENTER;

    setArea (layer_size.w, layer_size.h);

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerArea::setArea (
        const int layer_width,
        const int layer_height
    )
{
    DEBUG_FUNCTION_ENTER;

    frame_rect.w = layer_width;
    frame_rect.h = layer_height;

    updatePosition ();

    DEBUG_FUNCTION_EXIT;
}


void
SpriteLayerArea::updatePosition ()
{
    DEBUG_FUNCTION_ENTER;

    Geometry::anchorRectangle (
        frame_rect.x,
        frame_rect.y,
        frame_rect.w,
        frame_rect.h,
        anchor.x,
        anchor.y,
        anchorage
    );

    DEBUG_FUNCTION_EXIT;
}

