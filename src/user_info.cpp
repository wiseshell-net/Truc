/*
 * user_info.cpp
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

#include "user_info.hpp"

#include "debug.hpp"
#include "error.hpp"


/* thread */


extern int
userInfoAnimationThread (void * const data)
{
    DEBUG_FUNCTION_ENTER;

    UserInfo * const instance = (UserInfo *) data;

    if (instance == nullptr)
    {
        Error::runtimeError (
            "Unable to run animation thread.",
            __func__,
            "Null pointer on user info instance."
        );

        return ERROR_EXIT_FAILURE;
    }

    if (!instance->tryLockThreadMutex ())
    {
        Debug::info ("Could not lock thread mutex. Exiting.");

        return ERROR_EXIT_FAILURE;
    }

    const Delay delay_ms = instance->m_animation_duration_ms ?
        instance->m_animation_duration_ms : USER_INFO_DELAY;

    const uint8_t steps = 10;

    const float_t ratio = (ColorChannel) -1 / (float_t) steps;

    const Delay delay1 = delay_ms / 4 / steps;

    const Delay delay2 = delay_ms / 2;

    ColorChannel& alpha = instance->m_text_sprite.color.a;

    alpha = 0;

    if (delay1)
    {
        for (uint8_t i = 0;
             i < steps && instance->isThreadEnabled ();
             i++
            )
        {
            alpha = i * ratio;

            SDL_Delay (delay1);
        }
    }

    alpha = -1;

    SDL_Delay (delay2);

    if (delay1)
    {
        while (alpha >= ratio && instance->isThreadEnabled ())
        {
            alpha -= ratio;

            SDL_Delay (delay1);
        }
    }

    alpha = 0;

    instance->unlockThreadMutex ();

    instance->endThreadFunction ();

    DEBUG_FUNCTION_EXIT;

    return ERROR_EXIT_SUCCESS;
}


/* UserInfo */


UserInfo::UserInfo (Game& game) :
GamePart (game),
Threadable ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


UserInfo::~UserInfo ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


int
UserInfo::draw (SDL_Renderer * const renderer)
{
    DEBUG_FUNCTION_ENTER;

    return m_text_sprite.draw (renderer);

    DEBUG_FUNCTION_EXIT;
}


bool
UserInfo::initialize ()
{
    DEBUG_FUNCTION_ENTER;

    if (!initializeThread ())
    {
        return Error::runtimeError (
            "Unable to initialize thread support.",
            __func__,
            "Thread inits failed."
        );
    }

    reset ();

    DEBUG_FUNCTION_EXIT;

    return true;
}


void
UserInfo::reset ()
{
    DEBUG_FUNCTION_ENTER;

    resetAnchoragePoint ();
    resetColor ();
    resetFontIndex ();

    DEBUG_FUNCTION_EXIT;
}


void
UserInfo::resetAnchoragePoint ()
{
    DEBUG_FUNCTION_ENTER;

    setAnchoragePoint (
        USER_INFO_ANCHOR_X,
        USER_INFO_ANCHOR_Y,
        USER_INFO_ANCHORAGE
    );

    DEBUG_FUNCTION_EXIT;
}


void
UserInfo::resetColor ()
{
    DEBUG_FUNCTION_ENTER;

    setColor (USER_INFO_COLOR);

    DEBUG_FUNCTION_EXIT;
}


void
UserInfo::resetFontIndex ()
{
    DEBUG_FUNCTION_ENTER;

    setFontIndex (USER_INFO_FONT);

    DEBUG_FUNCTION_EXIT;
}


void
UserInfo::setAnchoragePoint (
        const int anchor_x,
        const int anchor_y,
        const AnchorageEnum& anchorage
    )
{
    DEBUG_FUNCTION_ENTER;

    m_text_sprite.setPosition (anchor_x, anchor_y, anchorage);

    DEBUG_FUNCTION_EXIT;
}


void
UserInfo::setColor (const Color& color)
{
    DEBUG_FUNCTION_ENTER;

    m_text_sprite.color = color;
    m_text_sprite.color.a = 0;

    DEBUG_FUNCTION_EXIT;
}


void
UserInfo::setFontIndex (const FontEnum& font_index)
{
    DEBUG_FUNCTION_ENTER;

    m_font_index = font_index;

    DEBUG_FUNCTION_EXIT;
}


bool
UserInfo::show (
        SDL_Renderer * const renderer,
        const std::string& message,
        const Delay& delay_ms
    )
{
    DEBUG_FUNCTION_ENTER;

    if (renderer == nullptr || message.empty () || !delay_ms)
    {
        return Error::runtimeError (
            "Unable to show user info text.",
            __func__,
            "Invalid arguments (renderer/message/delay)."
        );
    }

    m_text_sprite.setText (
        renderer,
        message,
        game.getFont (m_font_index),
        m_text_sprite.color
    );

    m_text_sprite.color.a = -1;

    m_animation_duration_ms = std::fmax (10, delay_ms);

    if (!THREAD_START (userInfoAnimationThread, this))
    {
        return false;
    }

    detachThread ();

    DEBUG_FUNCTION_EXIT;

    return true;
}

