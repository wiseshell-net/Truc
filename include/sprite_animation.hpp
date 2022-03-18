/*
 * sprite_animation.hpp
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

#ifndef _SPRITE_ANIMATION_HPP
#define _SPRITE_ANIMATION_HPP

/**
 * \file
 * \brief Generic sprite animation API.
 *
 * This header file declares a minimal and generic API for sprite
 * threaded animation.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <SDL.h>

#include "array.hpp"
#include "defs.hpp"
#include "threadable.hpp"
#include "tile_defs.hpp"


enum SpriteAnimationTypeEnum
{
    SPRITE_ANIMATION_TYPE_STATIC = 0,
    SPRITE_ANIMATION_TYPE_SEQUENTIAL,
    SPRITE_ANIMATION_TYPE_RANDOM,
    SPRITE_ANIMATION_TYPE_LOOP,
};


enum SpriteAnimationStateEnum
{
    /* body states */
    SPRITE_ANIMATION_STATE_IDLE =       0,
    SPRITE_ANIMATION_STATE_WALK =       1 <<  0,
    SPRITE_ANIMATION_STATE_RUN =        1 <<  1,
    SPRITE_ANIMATION_STATE_JUMP =       1 <<  2,
    SPRITE_ANIMATION_STATE_CLIMB =      1 <<  3,
    SPRITE_ANIMATION_STATE_FALL =       1 <<  4,
    SPRITE_ANIMATION_STATE_SLIDE =      1 <<  5,
    SPRITE_ANIMATION_STATE_CRAWL =      1 <<  6,
    SPRITE_ANIMATION_STATE_SWIM =       1 <<  7,
    SPRITE_ANIMATION_STATE_DIVE =       1 <<  8,
    SPRITE_ANIMATION_STATE_FLY =        1 <<  9,
    /* body member states */
    SPRITE_ANIMATION_STATE_TAKE =       1 << 10,
    SPRITE_ANIMATION_STATE_GIVE =       1 << 11,
    SPRITE_ANIMATION_STATE_CATCH =      1 << 12,
    SPRITE_ANIMATION_STATE_THROW =      1 << 13,
    SPRITE_ANIMATION_STATE_HIT =        1 << 14,
    SPRITE_ANIMATION_STATE_SHOOT =      1 << 15,
    SPRITE_ANIMATION_STATE_MELEE =      1 << 16,
    SPRITE_ANIMATION_STATE_ATTACK =     1 << 17,
    SPRITE_ANIMATION_STATE_DEFEND =     1 << 18,
    SPRITE_ANIMATION_STATE_DRINK =      1 << 19,
    SPRITE_ANIMATION_STATE_EAT =        1 << 20,
    SPRITE_ANIMATION_STATE_SLEEP =      1 << 21,
    /* emotional states */
    SPRITE_ANIMATION_STATE_LAUGH =      1 << 22,
    SPRITE_ANIMATION_STATE_ENJOY =      1 << 23,
    SPRITE_ANIMATION_STATE_FURIOUS =    1 << 24,
    SPRITE_ANIMATION_STATE_DEPICTED =   1 << 25,
    /* game states */
    SPRITE_ANIMATION_STATE_WIN =        1 << 26,
    SPRITE_ANIMATION_STATE_LOSE =       1 << 27,
    SPRITE_ANIMATION_STATE_DEAD =       1 << 28,
    /* user defs */
    SPRITE_ANIMATION_STATE_USER_1 =     1 << 29,
    SPRITE_ANIMATION_STATE_USER_2 =     1 << 30,
    SPRITE_ANIMATION_STATE_USER_3 =     1 << 31,
};


typedef uint32_t SpriteAnimationStateFlags;


enum SpriteAnimationDirectionEnum
{
    SPRITE_ANIMATION_DIRECTION_NONE =   0,
    SPRITE_ANIMATION_DIRECTION_LEFT =   1 << 0,
    SPRITE_ANIMATION_DIRECTION_RIGHT =  1 << 1,
    SPRITE_ANIMATION_DIRECTION_UP =     1 << 2,
    SPRITE_ANIMATION_DIRECTION_DOWN =   1 << 3,
    SPRITE_ANIMATION_DIRECTION_FRONT =  1 << 4,
    SPRITE_ANIMATION_DIRECTION_BACK =   1 << 5,
    /* aliases */
    SPRITE_ANIMATION_DIRECTION_CENTER =
        SPRITE_ANIMATION_DIRECTION_NONE,
};


typedef uint8_t SpriteAnimationDirectionFlags;


/**
 * \brief %Sprite animation data holder structure.
 */
struct SpriteAnimationData
{
    SpriteAnimationStateFlags       state_flags;
    SpriteAnimationDirectionFlags   direction_flags;
    TileSetIndex                    tile_set_index_start;
    ArraySize                       tile_set_index_count;
    Delay                           frame_delay_ms;
};


/**
 * \brief Array of sprite animation data holders.
 */
struct SpriteAnimationDataArray : public Array<SpriteAnimationData> {};


/**
 * \brief Generic sprite animation API structure.
 */
struct SpriteAnimation : public Threadable
{
public:

    SpriteAnimationTypeEnum         type;
    SpriteAnimationStateFlags       state_flags;
    SpriteAnimationDirectionFlags   direction_flags;
    bool                            sequence_ended;

    TileSetIndex                    tile_set_index;
    ArraySize                       tile_set_columns;
    SpriteAnimationDataArray        data_array;

    SDL_Rect *                      tile_rect;

protected:

    /**
     * \brief Specific function called by animation thread.
     *
     * The \c friend keyword allows this function to access protected
     * members.
     *
     * \param data - opaque pointer to thread data.
     *
     * \return negative value on failure, zero (0) on success.
     */
    friend int spriteAnimationThread (void * const data);

public:

    /**
     * \brief Structure constructor.
     */
    SpriteAnimation ();


    /**
     * \brief Structure destructor.
     */
    virtual ~SpriteAnimation ();


    /**
     * \brief Resets internals to new values.
     *
     * \param animation_type - enumeration index number.
     * \param state_flags - SpriteAnimationStateEnum multiple OR'ed
     * values.
     * \param direction_flags - SpriteAnimationDirectionEnum multiple
     * OR'ed values.
     */
    virtual void reset (
        const SpriteAnimationTypeEnum& animation_type,
        const SpriteAnimationStateFlags& state_flags,
        const SpriteAnimationDirectionFlags& direction_flags
    );


    /**
     * \brief Starts animation in thread.
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool startAnimation ();


    /**
     * \brief Stops current animation's thread.
     */
    virtual void stopAnimation ();

protected:

    /**
     * \brief Computes next animation frame for sprite's animation
     * thread.
     *
     * \return display duration for next frame, in milliseconds.
     */
    virtual Delay nextAnimationFrame ();

};


#endif /* _SPRITE_ANIMATION_HPP */
