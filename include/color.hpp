/*
 * color.hpp
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

#ifndef _COLOR_HPP
#define _COLOR_HPP

/**
 * \file
 * \brief Color API.
 *
 * This header file declares and defines general purpose API for color
 * management.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <cstdint>

#include <SDL.h>


typedef uint8_t     ColorChannel;
typedef uint32_t    RGBAChannels;
typedef uint32_t    RGBChannels;


/**
 * \brief Color management structure.
 *
 * This structure extends SDL_Color C API with new features.
 *
 */
struct Color : public SDL_Color
{
public:

    /**
     * \brief Structure constructor.
     */
    Color ();


    /**
     * \brief Structure constructor variant.
     *
     * Initializes object instance with an RGBA-encoded integer.
     *
     * \param rgba - RGBA-encoded 32-bit integer.
     */
    Color (
        const RGBAChannels& rgba
    );


    /**
     * \brief Structure constructor variant.
     *
     * Initializes object instance with an RGB-encoded integer and a
     * separate Alpha color channel.
     *
     * \param rgb   - RGB-encoded 32-bit integer.
     * \param alpha - Alpha 8-bit color channel (opacity).
     */
    Color (
        const RGBChannels& rgb,
        const ColorChannel& alpha
    );


    /**
     * \brief Structure constructor variant.
     *
     * Initializes object instance with detailed Red, Green, Blue and
     * Alpha color channels.
     *
     * \param red   - 8-bit color channel.
     * \param green - 8-bit color channel.
     * \param blue  - 8-bit color channel.
     * \param alpha - 8-bit color channel.
     */
    Color (
        const ColorChannel& red,
        const ColorChannel& green,
        const ColorChannel& blue,
        const ColorChannel& alpha
    );


    /**
     * \brief Structure destructor.
     */
    virtual ~Color ();


    /**
     * \brief Gets a random color object.
     *
     * Gets a color object with random RGB color channels in between a
     * given range and a fixed Alpha color channel.
     *
     * Each random color channel has its own distinct random value.
     *
     * \param start - 8-bit color channel, random range start value.
     * \param end   - 8-bit color channel, random range end value.
     * \param alpha - 8-bit color channel.
     *
     * \return color object.
     */
    static Color rgbRandomRange (
        const ColorChannel& start,
        const ColorChannel& end,
        const ColorChannel& alpha
    );


    /**
     * \brief Gets a random color object.
     *
     * Gets a random color object from a given value to randomize and a
     * fixed Alpha color channel.
     *
     * Each random color channel has its own distinct random value.
     *
     * \param rand  - 8-bit color channel.
     * \param alpha - 8-bit color channel.
     *
     * \return color object.
     */
    static Color rgbRandomize (
        const ColorChannel& rand,
        const ColorChannel& alpha
    );


    /**
     * \brief Gets a random color object.
     *
     * Gets a color object with random RGBA color channels in between a
     * given range.
     *
     * Each random color channel has its own distinct random value.
     *
     * \param start - 8-bit color channel, random range start value.
     * \param end   - 8-bit color channel, random range end value.
     *
     * \return color object.
     */
    static Color rgbaRandomRange (
        const ColorChannel& start,
        const ColorChannel& end
    );


    /**
     * \brief Gets a random color object.
     *
     * Gets a random color object from a given value to randomize.
     *
     * Each random color channel has its own distinct random value.
     *
     * \param rand  - 8-bit color channel.
     *
     * \return color object.
     */
    static Color rgbaRandomize (
        const ColorChannel& rand
    );

};


/* predefined colors */

#define COLOR_RGB_BLACK         0x000000
#define COLOR_RGB_WHITE         0xffffff
#define COLOR_RGB_RED           0xff0000
#define COLOR_RGB_GREEN         0x00ff00
#define COLOR_RGB_BLUE          0x0000ff
#define COLOR_RGB_YELLOW        0xffff00
#define COLOR_RGB_MAGENTA       0xff00ff
#define COLOR_RGB_CYAN          0x00ffff

#define COLOR_RGBA_TRANSPARENT  0x00000000
#define COLOR_RGBA_BLACK        0x000000ff
#define COLOR_RGBA_WHITE        0xffffffff
#define COLOR_RGBA_RED          0xff0000ff
#define COLOR_RGBA_GREEN        0x00ff00ff
#define COLOR_RGBA_BLUE         0x0000ffff
#define COLOR_RGBA_YELLOW       0xffff00ff
#define COLOR_RGBA_MAGENTA      0xff00ffff
#define COLOR_RGBA_CYAN         0x00ffffff

/*
 * CAUTION:
 *
 * at runtime, C++ constructs objects BEFORE running main ()
 * --> SDL_Color does NOT exist until SDL_Init () /!\
 * --> SDL_Color is dynamically loaded with SDL.h
 * --> SEGFAULT on predefined colors (see hack below)
 *
 */

/*
    /!\ this approach causes SEGFAULT /!\

static const Color& Transparent =    { 0x00, 0x00, 0x00, 0x00 };
static const Color& Black =          { 0x00, 0x00, 0x00, 0xff };
static const Color& White =          { 0xff, 0xff, 0xff, 0xff };
static const Color& Red =            { 0xff, 0x00, 0x00, 0xff };
static const Color& Green =          { 0x00, 0xff, 0x00, 0xff };
static const Color& Blue =           { 0x00, 0x00, 0xff, 0xff };
static const Color& Yellow =         { 0xff, 0xff, 0x00, 0xff };
static const Color& Magenta =        { 0xff, 0x00, 0xff, 0xff };
static const Color& Cyan =           { 0x00, 0xff, 0xff, 0xff };

*/

#define Transparent     Color (COLOR_RGBA_TRANSPARENT)
#define Black           Color (COLOR_RGBA_BLACK)
#define White           Color (COLOR_RGBA_WHITE)
#define Red             Color (COLOR_RGBA_RED)
#define Green           Color (COLOR_RGBA_GREEN)
#define Blue            Color (COLOR_RGBA_BLUE)
#define Yellow          Color (COLOR_RGBA_YELLOW)
#define Magenta         Color (COLOR_RGBA_MAGENTA)
#define Cyan            Color (COLOR_RGBA_CYAN)


#endif /* _COLOR_HPP */
