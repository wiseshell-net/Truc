/*
 * sprite_animation.cpp
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

#include "sprite_animation.hpp"

#include "debug.hpp"
#include "error.hpp"
#include "random.hpp"


/* thread */


extern int
spriteAnimationThread (void * const data)
{
    DEBUG_FUNCTION_ENTER;

    SpriteAnimation * const instance = (SpriteAnimation *) data;

    if (instance == nullptr)
    {
        Error::runtimeError (
            "Unable to run sprite animation thread.",
            __func__,
            "Null pointer instance parameter."
        );

        return ERROR_EXIT_FAILURE;
    }

    if (!instance->tryLockThreadMutex ())
    {
        Debug::info ("Could not lock thread mutex. Exiting.");

        return ERROR_EXIT_FAILURE;
    }

    Delay delay_ms;

    while (instance->isThreadEnabled ())
    {
        delay_ms = instance->nextAnimationFrame ();

        SDL_Delay (delay_ms > 0 ? delay_ms : 50);
    }

    instance->unlockThreadMutex ();

    instance->endThreadFunction ();

    DEBUG_FUNCTION_EXIT;

    return ERROR_EXIT_SUCCESS;
}


/* SpriteAnimation */


SpriteAnimation::SpriteAnimation () :
Threadable (),
type (SPRITE_ANIMATION_TYPE_STATIC),
state_flags (0),
direction_flags (0),
sequence_ended (false),
tile_set_index (0),
tile_set_columns (0),
tile_rect (nullptr)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


SpriteAnimation::~SpriteAnimation ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


Delay
SpriteAnimation::nextAnimationFrame ()
{
    DEBUG_FUNCTION_ENTER;

    if (tile_rect == nullptr || data_array.empty ())
    {
        Error::runtimeError (
            "Unable to compute next frame in sprite animation.",
            __func__,
            "Invalid parameters."
        );

        return 0;
    }

    SpriteAnimationData * data = nullptr;

    for (ArrayIndex i = 0; i < data_array.size (); i++)
    {
        const ArrayIndex j =
            (data_array.getIndex () + i) % data_array.size ();

        SpriteAnimationData& d = data_array [j];

        if (d.state_flags == state_flags
            && d.direction_flags == direction_flags)
        {
            data = &d;
            data_array.setIndex (j);
            break;
        }
    }

    if (data == nullptr)
    {
        Error::runtimeError (
            "Unable to compute next frame in sprite animation.",
            __func__,
            "Missing sprite animation data for required animation "
            "states and directions."
        );

        return 0;
    }

    data->tile_set_index_count =
        std::fmax (1, data->tile_set_index_count);

    const TileSetIndex index_start = data->tile_set_index_start;

    const TileSetIndex index_end =
        index_start + data->tile_set_index_count - 1;

    if (tile_set_index < index_start || tile_set_index > index_end)
    {
        tile_set_index = index_start;
    }

    switch (type)
    {
        case SPRITE_ANIMATION_TYPE_STATIC:
            sequence_ended = true;
            break;

        case SPRITE_ANIMATION_TYPE_SEQUENTIAL:
            tile_set_index = std::fmin (tile_set_index + 1, index_end);
            sequence_ended = (tile_set_index == index_end);
            break;

        case SPRITE_ANIMATION_TYPE_RANDOM:
            tile_set_index = Random::range (index_start, index_end);
            sequence_ended = false;
            break;

        case SPRITE_ANIMATION_TYPE_LOOP:
            tile_set_index++;
            if (tile_set_index > index_end)
            {
                tile_set_index = index_start;
            }
            sequence_ended = (tile_set_index == index_end);
            break;

        default:
            break;
    }

    tile_rect->x = tile_rect->w * (tile_set_index % tile_set_columns);

    tile_rect->y = tile_rect->h * (tile_set_index / tile_set_columns);

    DEBUG_FUNCTION_EXIT;

    return data->frame_delay_ms;
}


void
SpriteAnimation::reset (
        const SpriteAnimationTypeEnum& animation_type,
        const SpriteAnimationStateFlags& s_flags,
        const SpriteAnimationDirectionFlags& d_flags
    )
{
    DEBUG_FUNCTION_ENTER;

    type = animation_type;
    state_flags = s_flags;
    direction_flags = d_flags;

    DEBUG_FUNCTION_EXIT;
}


bool
SpriteAnimation::startAnimation ()
{
    DEBUG_FUNCTION_ENTER;

    if (!initializeThread ())
    {
        return Error::runtimeError (
            "Unable to start sprite animation thread.",
            __func__,
            "Thread support inits failed."
        );
    }

    if (!THREAD_START_SAFE (spriteAnimationThread, this))
    {
        return Error::runtimeError (
            "Unable to start sprite animation thread.",
            __func__,
            "Thread start failed."
        );
    }

    detachThread ();

    DEBUG_FUNCTION_EXIT;

    return true;
}


void
SpriteAnimation::stopAnimation ()
{
    DEBUG_FUNCTION_ENTER;

    stopThread ();

    DEBUG_FUNCTION_EXIT;
}

