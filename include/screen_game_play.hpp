/*
 * screen_game_play.hpp
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

#ifndef _SCREEN_GAME_PLAY_HPP
#define _SCREEN_GAME_PLAY_HPP

#include "animated_sprite.hpp"
#include "screen_base.hpp"
#include "sprite_array.hpp"
#include "sprite.hpp"
#include "sprite_layer_area.hpp"
#include "sprite_layer.hpp"


struct ScreenGamePlay : public ScreenBase
{
protected:

    AnimatedSprite *    m_bird_sprites [3];
    AnimatedSprite *    m_boat_sprite;
    AnimatedSprite *    m_crab_sprite;
    AnimatedSprite *    m_fish_sprites [3];
    AnimatedSprite *    m_golden_fish_sprite;
    AnimatedSprite *    m_player_sprite;
    AnimatedSprite *    m_treasure_sprite;

    SpriteArray         m_cloud_sprites;
    SpriteArray         m_ground_item_sprites;
    SpriteLayerArea     m_sprite_layer0;
    SpriteLayer         m_sprite_layer1;

    Sprite              m_game_paused_sprite;
    Sprite              m_ground_sprite;
    Sprite              m_score_sprite;
    Sprite              m_sky_sprite;

    uint8_t             m_bird_index;
    uint8_t             m_fish_index;
    uint8_t             m_oxygen_prc;     /* 0 - 100% */
    uint8_t             m_score;

    uint16_t            m_golden_fish_lifetime;

    bool                m_game_is_paused;
    bool                m_wait_sync;

public:

    ScreenGamePlay (Game& game);

    virtual ~ScreenGamePlay ();

    virtual bool initialize ();

protected:

    virtual void changeBird (
        const SDL_Point& anchor,
        const SDL_Point& direction
    );

    virtual void changeFish (
        const SDL_Point& anchor,
        const SDL_Point& direction
    );

    virtual ScreenEnum doDrawings ();

    virtual ScreenEnum doEvents ();

    virtual ScreenEnum doLogic ();
    virtual ScreenEnum doLogicDeepWater ();
    virtual ScreenEnum doLogicShallowWater ();

    virtual bool initializeBird ();
    virtual bool initializeBoat ();
    virtual bool initializeCrab ();
    virtual bool initializeFish ();
    virtual bool initializeGoldenFish ();
    virtual bool initializePlayer ();
    virtual bool initializeTreasure ();

    virtual ScreenEnum onExit (ScreenEnum screen);

    virtual void playerAction ();
    virtual void playerIdle ();
    virtual void playerMoveDown ();
    virtual void playerMoveLeft ();
    virtual void playerMoveRight ();
    virtual void playerMoveUp ();
    virtual void playerRecenter ();

    virtual ScreenEnum reset ();

    virtual void toggleGamePause ();
};


#endif /* _SCREEN_GAME_PLAY_HPP */
