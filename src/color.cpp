/*
 * color.cpp
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

#include <climits>

#include "color.hpp"

#include "debug.hpp"
#include "random.hpp"


static constexpr std::size_t bits = CHAR_BIT * sizeof (ColorChannel);


Color::Color ()
{
    DEBUG_FUNCTION_ENTER;

    r = g = b = a = 0;

    DEBUG_FUNCTION_EXIT;
}


Color::Color (const RGBAChannels& rgba)
{
    DEBUG_FUNCTION_ENTER;

    r = (rgba >> (3 * bits));
    g = (rgba >> (2 * bits));
    b = (rgba >> (1 * bits));
    a = (rgba >> (0 * bits));

    DEBUG_FUNCTION_EXIT;
}


Color::Color (const RGBChannels& rgb, const ColorChannel& alpha)
{
    DEBUG_FUNCTION_ENTER;

    r = (rgb >> (2 * bits));
    g = (rgb >> (1 * bits));
    b = (rgb >> (0 * bits));
    a = alpha;

    DEBUG_FUNCTION_EXIT;
}


Color::Color (
        const ColorChannel& red,
        const ColorChannel& green,
        const ColorChannel& blue,
        const ColorChannel& alpha
    )
{
    DEBUG_FUNCTION_ENTER;

    r = red;
    g = green;
    b = blue;
    a = alpha;

    DEBUG_FUNCTION_EXIT;
}


Color::~Color ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


Color
Color::rgbRandomRange (
        const ColorChannel& start,
        const ColorChannel& end,
        const ColorChannel& alpha
    )
{
    DEBUG_FUNCTION_CALL;

    return Color (
        Random::range (start, end),
        Random::range (start, end),
        Random::range (start, end),
        alpha
    );
}


Color
Color::rgbRandomize (
        const ColorChannel& rand,
        const ColorChannel& alpha
    )
{
    DEBUG_FUNCTION_CALL;

    return Color (
        Random::randomize (rand),
        Random::randomize (rand),
        Random::randomize (rand),
        alpha
    );
}


Color
Color::rgbaRandomRange (
        const ColorChannel& start,
        const ColorChannel& end
    )
{
    DEBUG_FUNCTION_CALL;

    return Color (
        Random::range (start, end),
        Random::range (start, end),
        Random::range (start, end),
        Random::range (start, end)
    );
}


Color
Color::rgbaRandomize (const ColorChannel& rand)
{
    DEBUG_FUNCTION_CALL;

    return Color (
        Random::randomize (rand),
        Random::randomize (rand),
        Random::randomize (rand),
        Random::randomize (rand)
    );
}

