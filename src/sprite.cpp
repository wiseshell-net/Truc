/*
 * sprite.cpp
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

#include "sprite.hpp"

#include "debug.hpp"
#include "error.hpp"
#include "geometry.hpp"


Sprite::Sprite () :
Drawable (),
Movable (),
texture (nullptr),
texture_rect { 0, 0, 0, 0 },
renderer_rect { 0, 0, 0, 0 },
box (renderer_rect),
color (White),
texture_is_internal (false)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


Sprite::Sprite (SDL_Texture * const texture) :
Sprite ()
{
    DEBUG_FUNCTION_ENTER;

    setTexture (texture, false);

    DEBUG_FUNCTION_EXIT;
}


Sprite::Sprite (
        SDL_Renderer * const renderer,
        SDL_Surface * const surface
    ) :
Sprite ()
{
    DEBUG_FUNCTION_ENTER;

    setTexture (renderer, surface);

    DEBUG_FUNCTION_EXIT;
}


Sprite::Sprite (
        SDL_Renderer * const renderer,
        const std::string& text,
        TTF_Font * const font,
        const Color& color
    ) :
Sprite ()
{
    DEBUG_FUNCTION_ENTER;

    setText (renderer, text, font, color);

    DEBUG_FUNCTION_EXIT;
}


Sprite::~Sprite ()
{
    DEBUG_FUNCTION_ENTER;

    clearTexture ();

    DEBUG_FUNCTION_EXIT;
}


void
Sprite::clearTexture ()
{
    DEBUG_FUNCTION_ENTER;

    if (texture_is_internal)
    {
        SDL_DestroyTexture (texture);
    }

    texture = nullptr;

    texture_is_internal = false;

    DEBUG_FUNCTION_EXIT;
}


bool
Sprite::collides (const Sprite * const sprite)
{
    DEBUG_FUNCTION_CALL;

    return (sprite != nullptr) ? box.intersects (sprite->box) : false;
}


bool
Sprite::collides (const Sprite& sprite)
{
    DEBUG_FUNCTION_CALL;

    return box.intersects (sprite.box);
}


int
Sprite::draw (SDL_Renderer * const renderer)
{
    DEBUG_FUNCTION_CALL;

    return draw (renderer, color);
}


int
Sprite::draw (SDL_Renderer * const renderer, const ColorChannel& alpha)
{
    DEBUG_FUNCTION_CALL;

    color.a = alpha;

    return draw (renderer, color);
}


int
Sprite::draw (SDL_Renderer * const renderer, const Color& color)
{
    DEBUG_FUNCTION_CALL;

    if (!color.a || !is_visible)
    {
        return ERROR_EXIT_SUCCESS;
    }

    if (SDL_SetTextureColorMod (texture, color.r, color.g, color.b)
            != ERROR_EXIT_SUCCESS
        || SDL_SetTextureAlphaMod (texture, color.a)
            != ERROR_EXIT_SUCCESS)
    {
        return ERROR_EXIT_FAILURE;
    }

    return SDL_RenderCopy (
        renderer,
        texture,
        &texture_rect,
        &renderer_rect
    );
}


bool
Sprite::setText (
        SDL_Renderer * const renderer,
        const std::string& text,
        TTF_Font * const font,
        const Color& color_
    )
{
    DEBUG_FUNCTION_CALL;

    if (renderer != nullptr && !text.empty() && font != nullptr)
    {
        SDL_Surface * const surface =
            TTF_RenderUTF8_Blended (font, text.c_str (), White);

        if (surface != nullptr)
        {
            const bool ok = setTexture (renderer, surface);

            SDL_FreeSurface (surface);

            color = color_;

            return ok;
        }
    }

    return false;
}


bool
Sprite::setTexture (SDL_Texture * const texture_, bool internal)
{
    DEBUG_FUNCTION_ENTER;

    if (texture_ != nullptr)
    {
        clearTexture ();

        texture = texture_;

        texture_is_internal = internal;

        texture_rect = { 0, 0, 0, 0 };

        SDL_QueryTexture (
            texture,
            nullptr,
            nullptr,
            &texture_rect.w,
            &texture_rect.h
        );

        renderer_rect = texture_rect;

        updatePosition ();

        return true;
    }

    DEBUG_FUNCTION_EXIT;

    return false;
}


bool
Sprite::setTexture (
        SDL_Renderer * const renderer,
        SDL_Surface * const surface
    )
{
    DEBUG_FUNCTION_CALL;

    return setTexture (
        SDL_CreateTextureFromSurface (renderer, surface),
        true
    );
}


void
Sprite::updatePosition ()
{
    DEBUG_FUNCTION_ENTER;

    Geometry::anchorRectangle (
        renderer_rect.x,
        renderer_rect.y,
        renderer_rect.w,
        renderer_rect.h,
        anchor.x,
        anchor.y,
        anchorage
    );

    DEBUG_FUNCTION_EXIT;
}

