/*
 * geometry.cpp
 *
 * Copyright 2018 Raphaël SEBAN <raphael.seban@laposte.net>
 *
 * This program is delete software; you can redistribute it and/or modify
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

#include "geometry.hpp"


namespace Geometry
{

void
anchorRectangle (
        Integer& rectangle_left_x,
        Integer& rectangle_top_y,
        const Integer& rectangle_width,
        const Integer& rectangle_height,
        const Integer& anchor_x,
        const Integer& anchor_y,
        const AnchorageEnum& anchorage
    )
{
    rectangle_left_x = anchor_x + (
            + ((anchorage & ANCHOR_WEST) != 0)
            - ((anchorage & ANCHOR_EAST) != 0)
            - 1
        ) * std::abs (rectangle_width / 2);

    rectangle_top_y = anchor_y + (
            + ((anchorage & ANCHOR_NORTH) != 0)
            - ((anchorage & ANCHOR_SOUTH) != 0)
            - 1
        ) * std::abs (rectangle_height / 2);
}


void
anchorRectangle (
        IRectangle& rectangle,
        const IAnchoragePoint& anchor
    )
{
    anchorRectangle (
        rectangle.x,
        rectangle.y,
        rectangle.w,
        rectangle.h,
        anchor.x,
        anchor.y,
        anchor.anchorage
    );
}


void
anchorRectangle (
        Number& rectangle_left_x,
        Number& rectangle_top_y,
        const Number& rectangle_width,
        const Number& rectangle_height,
        const Number& anchor_x,
        const Number& anchor_y,
        const AnchorageEnum& anchorage
    )
{
    rectangle_left_x = anchor_x + (
            + ((anchorage & ANCHOR_WEST) != 0)
            - ((anchorage & ANCHOR_EAST) != 0)
            - 1
        ) * std::fabs (rectangle_width / 2.f);

    rectangle_top_y = anchor_y + (
            + ((anchorage & ANCHOR_NORTH) != 0)
            - ((anchorage & ANCHOR_SOUTH) != 0)
            - 1
        ) * std::fabs (rectangle_height / 2.f);
}


void
anchorRectangle (
        Rectangle& rectangle,
        const AnchoragePoint& anchor
    )
{
    anchorRectangle (
        rectangle.x,
        rectangle.y,
        rectangle.w,
        rectangle.h,
        anchor.x,
        anchor.y,
        anchor.anchorage
    );
}


bool
fillPointArrayAsCircle (
        IPointArray& array,
        const ArraySize& nb_points,
        const Integer& center_x,
        const Integer& center_y,
        const Integer& radius
    )
{
    if (!nb_points)
    {
        return false;
    }

    array.resize (nb_points);

    const Number& ratio = 2.f * PI / (Number) nb_points;

    for (ArrayIndex i = 0; i < nb_points; i++)
    {
        array[i].x = center_x + radius * cos ((Number) i * ratio);
        array[i].y = center_y + radius * sin ((Number) i * ratio);
    }

    return true;
}


bool
fillPointArrayAsCircle (
        PointArray& array,
        const ArraySize& nb_points,
        const Number& center_x,
        const Number& center_y,
        const Number& radius
    )
{
    if (!nb_points)
    {
        return false;
    }

    array.resize (nb_points);

    const Number& ratio = 2.f * PI / (Number) nb_points;

    for (ArrayIndex i = 0; i < nb_points; i++)
    {
        array[i].x = center_x + radius * cos ((Number) i * ratio);
        array[i].y = center_y + radius * sin ((Number) i * ratio);
    }

    return true;
}


IRectangle
getAnchoredRectangle (
        const Integer& rectangle_width,
        const Integer& rectangle_height,
        const Integer& anchor_x,
        const Integer& anchor_y,
        const AnchorageEnum& anchorage
    )
{
    Integer rectangle_left_x;
    Integer rectangle_top_y;

    anchorRectangle (
        rectangle_left_x,
        rectangle_top_y,
        rectangle_width,
        rectangle_height,
        anchor_x,
        anchor_y,
        anchorage
    );

    return
    {
        rectangle_left_x,
        rectangle_top_y,
        rectangle_width,
        rectangle_height
    };
}


IRectangle
getAnchoredRectangle (
        const IRectangle& rectangle,
        const IAnchoragePoint& anchor
    )
{
    IRectangle rect = rectangle;

    anchorRectangle (rect, anchor);

    return rect;
}


Rectangle
getAnchoredRectangle (
        const Number& rectangle_width,
        const Number& rectangle_height,
        const Number& anchor_x,
        const Number& anchor_y,
        const AnchorageEnum& anchorage
    )
{
    Number rectangle_left_x;
    Number rectangle_top_y;

    anchorRectangle (
        rectangle_left_x,
        rectangle_top_y,
        rectangle_width,
        rectangle_height,
        anchor_x,
        anchor_y,
        anchorage
    );

    return
    {
        rectangle_left_x,
        rectangle_top_y,
        rectangle_width,
        rectangle_height
    };
}


Rectangle
getAnchoredRectangle (
        const Rectangle& rectangle,
        const AnchoragePoint& anchor
    )
{
    Rectangle rect = rectangle;

    anchorRectangle (rect, anchor);

    return rect;
}


} /* namespace */

