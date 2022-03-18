/*
 * screen_game_play.cpp
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

#include "screen_game_play.hpp"

#include "debug.hpp"
#include "error.hpp"
#include "geometry.hpp"
#include "random.hpp"
#include "screens.hpp"


ScreenGamePlay::ScreenGamePlay (Game& game) :
ScreenBase (game),
m_bird_sprites { nullptr },
m_boat_sprite (nullptr),
m_crab_sprite (nullptr),
m_fish_sprites { nullptr },
m_golden_fish_sprite (nullptr),
m_player_sprite (nullptr),
m_treasure_sprite (nullptr)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


ScreenGamePlay::~ScreenGamePlay ()
{
    DEBUG_FUNCTION_ENTER;

    if (m_sprite_layer0.empty ())
    {
        delete m_boat_sprite;
        delete m_crab_sprite;
        delete m_player_sprite;
        delete m_treasure_sprite;
    }
    else
    {
        m_sprite_layer0.clear ();
    }

    if (m_sprite_layer1.empty ())
    {
        for (auto * sprite: m_bird_sprites)
        {
            delete sprite;
        }

        for (auto * sprite: m_fish_sprites)
        {
            delete sprite;
        }

        delete m_golden_fish_sprite;
    }
    else
    {
        m_sprite_layer1.clear ();
    }

    DEBUG_FUNCTION_EXIT;
}


void
ScreenGamePlay::changeBird (
        const SDL_Point& anchor,
        const SDL_Point& direction
    )
{
    DEBUG_FUNCTION_ENTER;

    for (auto * const sprite: m_bird_sprites)
    {
        sprite->is_visible = false;
        sprite->anchor = anchor;
        sprite->direction = direction;
        sprite->dx = 3;
        sprite->dy = 0;
        sprite->stopAnimation ();
    }

    m_bird_index = (m_bird_index + 1) % ARRAY_SIZE (m_bird_sprites);

    AnimatedSprite * const bird = m_bird_sprites [m_bird_index];

    bird->lockThreadMutex ();

    bird->direction.x = (direction.x > 0) ? +1 : -1;

    bird->reset (
        SPRITE_ANIMATION_TYPE_LOOP,
        SPRITE_ANIMATION_STATE_FLY,
        (direction.x > 0) ?
            SPRITE_ANIMATION_DIRECTION_RIGHT :
            SPRITE_ANIMATION_DIRECTION_LEFT
    );

    bird->setPosition (
        anchor.x - bird->direction.x * bird->renderer_rect.w / 2,
        m_sprite_layer0.box.topSide () + Random::range (
            bird->renderer_rect.h / 2,
            game.window_center.y - bird->renderer_rect.h / 2
        ),
        ANCHOR_CENTER
    );

    bird->unlockThreadMutex ();

    bird->startAnimation ();

    bird->is_visible = true;

    DEBUG_FUNCTION_EXIT;
}


void
ScreenGamePlay::changeFish (
        const SDL_Point& anchor,
        const SDL_Point& direction
    )
{
    DEBUG_FUNCTION_ENTER;

    for (auto * const sprite: m_fish_sprites)
    {
        sprite->is_visible = false;
        sprite->anchor = anchor;
        sprite->direction = direction;
        sprite->dx = 3;
        sprite->dy = 0;
        sprite->stopAnimation ();
    }

    m_fish_index = (m_fish_index + 1) % ARRAY_SIZE (m_fish_sprites);

    AnimatedSprite * const fish = m_fish_sprites [m_fish_index];

    fish->lockThreadMutex ();

    fish->direction.x = (direction.x > 0) ? +1 : -1;

    fish->reset (
        SPRITE_ANIMATION_TYPE_LOOP,
        SPRITE_ANIMATION_STATE_SWIM,
        (direction.x > 0) ?
            SPRITE_ANIMATION_DIRECTION_RIGHT :
            SPRITE_ANIMATION_DIRECTION_LEFT
    );

    fish->setPosition (
        anchor.x - fish->direction.x * fish->renderer_rect.w / 2,
        m_sprite_layer0.box.topSide () + game.window_size.h +
            Random::range (50, 150),
        ANCHOR_CENTER
    );

    fish->unlockThreadMutex ();

    fish->startAnimation ();

    fish->is_visible = true;

    DEBUG_FUNCTION_EXIT;
}


ScreenEnum
ScreenGamePlay::doDrawings ()
{
    DEBUG_FUNCTION_ENTER;

    Render::clear (game.renderer, game.background_color);

    m_sky_sprite.draw (game.renderer);

    m_cloud_sprites.draw (game.renderer);

    m_ground_sprite.draw (game.renderer);

    m_ground_item_sprites.draw (game.renderer);

    m_sprite_layer0.draw (game.renderer);

    m_sprite_layer1.draw (game.renderer);

    if (m_game_is_paused)
    {
        m_game_paused_sprite.draw (game.renderer);
    }

    for (uint8_t i = 0; i < m_score; i++)
    {
        m_score_sprite.setPosition (
            game.window_size.w -
                i * (m_score_sprite.renderer_rect.w - 10),
            0,
            ANCHOR_NORTH_EAST
        );

        m_score_sprite.draw (game.renderer);
    }

    SDL_Rect gauge =
        { 10, game.window_center.y + 100, 20, -2 * m_oxygen_prc };

    Render::setDrawColor (
        game.renderer,
        Color (
            std::min (255, 300 - 2 * m_oxygen_prc),
            std::min (255, 3 * m_oxygen_prc),
            50 + 2 * m_oxygen_prc,
            200)
    );

    SDL_RenderFillRect (game.renderer, &gauge);

    gauge = { 10, game.window_center.y - 100, 20, 200 };

    Render::setDrawColor (game.renderer, Red);

    SDL_RenderDrawRect (game.renderer, &gauge);

    game.user_info->draw (game.renderer);

    Render::display (game.renderer);

    SDL_Delay (GAME_DRAWINGS_DELAY_MS);

    DEBUG_FUNCTION_EXIT;

    return SCREEN_DEFAULT;
}


ScreenEnum
ScreenGamePlay::doEvents ()
{
    DEBUG_FUNCTION_ENTER;

    SDL_Event event;

    while (SDL_PollEvent (&event))
    {
        ScreenEnum screen =
            game.screens->fromCommonEvent (event, SCREEN_DEFAULT);

        if (screen != SCREEN_DEFAULT) return screen;

        switch (event.type)
        {
            case SDL_MOUSEMOTION:
                SDL_ShowCursor (SDL_ENABLE);
                break;

            case SDL_KEYUP:
                SDL_ShowCursor (SDL_DISABLE);
                switch (event.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        playerMoveLeft ();
                        break;

                    case SDLK_RIGHT:
                        playerMoveRight ();
                        break;

                    case SDLK_UP:
                        playerMoveUp ();
                        break;

                    case SDLK_DOWN:
                        playerMoveDown ();
                        break;

                    case SDLK_SPACE:
                    case SDLK_RCTRL:
                        playerAction ();
                        break;

                    case SDLK_RSHIFT:
                        playerIdle ();
                        break;

                    case SDLK_RETURN:
                        playerRecenter ();
                        break;

                    case SDLK_p:
                        toggleGamePause ();
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }

    DEBUG_FUNCTION_EXIT;

    return SCREEN_DEFAULT;
}


ScreenEnum
ScreenGamePlay::doLogic ()
{
    DEBUG_FUNCTION_ENTER;

    /* game pause */

    if (m_game_is_paused)
    {
        return SCREEN_DEFAULT;
    }

    /* player */

    m_player_sprite->move ();

    if (m_player_sprite->box.rightSide () >
        m_sprite_layer0.box.rightSide ())
    {
        m_player_sprite->moveDirection (-1, 0);
        playerIdle ();
    }
    else
    if (m_player_sprite->box.leftSide () <
        m_sprite_layer0.box.leftSide ())
    {
        m_player_sprite->moveDirection (+1, 0);
        playerIdle ();
    }

    if (m_player_sprite->box.bottomSide () >
        m_sprite_layer0.box.bottomSide ())
    {
        m_player_sprite->moveDirection (0, -1);
        playerIdle ();
    }
    else
    if (m_player_sprite->anchor.y <
        m_sprite_layer0.box.topSide () + game.window_center.y)
    {
        m_player_sprite->setPosition (
            m_player_sprite->anchor.x,
            m_sprite_layer0.box.topSide () + game.window_center.y
        );

        playerIdle ();

        if (m_oxygen_prc < 100)
        {
            m_oxygen_prc++;
        }
    }

    if (m_player_sprite->anchor.y <=
        m_sprite_layer0.box.topSide () + game.window_center.y
        && m_oxygen_prc < 100)
    {
        m_oxygen_prc++;
    }
    else
    if (Random::randomize (10) == 3)
    {
        m_oxygen_prc--;
    }

    if (!m_oxygen_prc)
    {
        return SCREEN_GAME_OVER;
    }

    /* golden fish */

    if (m_golden_fish_lifetime)
    {
        m_golden_fish_lifetime--;

        m_golden_fish_sprite->color.a =
            (m_golden_fish_lifetime <= 50) ?
            10 * (m_golden_fish_lifetime / 10)  : -1;

        m_golden_fish_sprite->move ();
    }

    /* treasure chest */

    if (m_score > 3)
    {
        return SCREEN_LEVEL_COMPLETE;
    }

    if (m_treasure_sprite->state_flags != SPRITE_ANIMATION_STATE_IDLE
        && m_treasure_sprite->sequence_ended)
    {
        m_wait_sync = true;

        if (m_treasure_sprite->color.a > 5)
        {
            m_treasure_sprite->color.a -= 5;
        }
        else
        {
            m_treasure_sprite->reset (
                SPRITE_ANIMATION_TYPE_STATIC,
                SPRITE_ANIMATION_STATE_IDLE,
                SPRITE_ANIMATION_DIRECTION_LEFT
            );

            m_treasure_sprite->tile_set_index = 0;

            m_treasure_sprite->setPosition (
                Random::range (
                    m_sprite_layer0.box.leftSide () + 100,
                    m_sprite_layer0.box.rightSide () - 100
                ),
                m_sprite_layer0.box.bottomSide () -
                    Random::range (40, 100),
                ANCHOR_CENTER
            );

            SDL_Delay (GAME_DRAWINGS_DELAY_MS * 2);

            m_treasure_sprite->color.a = -1;

            m_wait_sync = false;
        }
    }

    /* sprite layers */

    m_sprite_layer0.direction =
    {
        -m_player_sprite->direction.x,
        -m_player_sprite->direction.y
    };

    m_sprite_layer0.moveAround ();

    m_sprite_layer1.moveDirection (m_sprite_layer0.direction);

    /* sky dome layer */

    m_sky_sprite.move
        (0, m_sprite_layer0.dy, m_sprite_layer0.direction);

    /* clouds layer */

    m_cloud_sprites.moveDirection (m_sprite_layer0.direction);

    /* ground layer */

    m_ground_sprite.move
        (0, m_sprite_layer0.dy, m_sprite_layer0.direction);

    /* ground items layer */

    m_ground_item_sprites.moveDirection (m_sprite_layer0.direction);

    /* shallow / deep waters logic */

    if (m_sprite_layer0.box.topSide () > -game.window_center.y)
    {
        DEBUG_FUNCTION_EXIT;

        return doLogicShallowWater ();
    }

    DEBUG_FUNCTION_EXIT;

    return doLogicDeepWater ();
}


ScreenEnum
ScreenGamePlay::doLogicDeepWater ()
{
    DEBUG_FUNCTION_ENTER;

    /* crab */

    if (Random::randomize (20) == 7)
    {
        m_crab_sprite->dx = Random::randomize (3);
        m_crab_sprite->direction.x = Random::range (-1, +1);
    }

    m_crab_sprite->move ();

    if (m_crab_sprite->box.rightSide () >
        m_sprite_layer0.box.rightSide ())
    {
        m_crab_sprite->direction.x = -1;
    }
    else
    if (m_crab_sprite->box.leftSide () <
        m_sprite_layer0.box.leftSide ())
    {
        m_crab_sprite->direction.x = +1;
    }

    /* fish */

    m_fish_sprites [m_fish_index]->move ();

    if (m_fish_sprites [m_fish_index]->box.leftSide () >
        m_sprite_layer0.box.rightSide ())
    {
        changeFish (
            { m_sprite_layer0.box.rightSide (), 0 },
            { -1, 0 }
        );
    }
    else
    if (m_fish_sprites [m_fish_index]->box.rightSide () <
        m_sprite_layer0.box.leftSide ())
    {
        changeFish (
            { m_sprite_layer0.box.leftSide (), 0 },
            { +1, 0 }
        );
    }

    /* golden fish */

    if (!m_golden_fish_lifetime && Random::randomize (500) == 42)
    {
        m_golden_fish_lifetime = 200 * Random::range (1, 5);

        m_golden_fish_sprite->direction =
            { (Random::randomize (1) ? +1 : -1), 0 };

        m_golden_fish_sprite->setPosition (
            (m_golden_fish_sprite->direction.x > 0) ?
                0 : game.window_size.w,
            Random::range
                (game.window_center.y / 2, game.window_center.y),
            ANCHOR_CENTER
        );

        m_golden_fish_sprite->reset (
            SPRITE_ANIMATION_TYPE_LOOP,
            SPRITE_ANIMATION_STATE_SWIM,
            (m_golden_fish_sprite->direction.x > 0) ?
                SPRITE_ANIMATION_DIRECTION_RIGHT :
                SPRITE_ANIMATION_DIRECTION_LEFT
        );

        game.emitSound (SOUND_GOLDEN_FISH);
    }

    DEBUG_FUNCTION_EXIT;

    return SCREEN_DEFAULT;
}


ScreenEnum
ScreenGamePlay::doLogicShallowWater ()
{
    DEBUG_FUNCTION_ENTER;

    /* clouds */

    for (auto& sprite: m_cloud_sprites)
    {
        if (Random::randomize (10) == 3)
        {
            sprite.move ();

            if (sprite.box.rightSide () >
                m_sprite_layer0.box.rightSide ())
            {
                sprite.direction.x = -1;
            }
            else
            if (sprite.box.leftSide () <
                m_sprite_layer0.box.leftSide ())
            {
                sprite.direction.x = +1;
            }
        }
    }

    /* bird */

    m_bird_sprites [m_bird_index]->move ();

    if (m_bird_sprites [m_bird_index]->box.leftSide () >
        m_sprite_layer0.box.rightSide ())
    {
        changeBird (m_sprite_layer0.box.topRight (), { -1, 0 });
    }
    else
    if (m_bird_sprites [m_bird_index]->box.rightSide () <
        m_sprite_layer0.box.leftSide ())
    {
        changeBird (m_sprite_layer0.box.topLeft (), { +1, 0 });
    }

    DEBUG_FUNCTION_EXIT;

    return SCREEN_DEFAULT;
}


bool
ScreenGamePlay::initialize ()
{
    DEBUG_FUNCTION_ENTER;

    /* game paused text */

    m_game_paused_sprite.setText (
        game.renderer,
        GAME_PAUSE_TEXT,
        game.getFont (GAME_PAUSE_FONT),
        GAME_PAUSE_COLOR
    );

    m_game_paused_sprite.setPosition
        (game.window_center, ANCHOR_CENTER);

    /* m_score */

    m_score_sprite.setTexture
        (game.renderer, game.getImage (IMAGE_TREASURE_CHEST_01));

    m_score_sprite.renderer_rect = m_score_sprite.texture_rect =
        { 600, 0, 100, 100 };

    /* sky dome layer */

    m_sky_sprite.setTexture
        (game.renderer, game.getImage (IMAGE_SKY_01));

    /* clouds layer */

    m_cloud_sprites.resize (3);

    m_cloud_sprites[0].setTexture
        (game.renderer, game.getImage (IMAGE_CLOUD_01));

    m_cloud_sprites[1].setTexture
        (game.renderer, game.getImage (IMAGE_CLOUD_02));

    m_cloud_sprites[2].setTexture
        (game.renderer, game.getImage (IMAGE_CLOUD_03));

    /* ground layer */

    m_ground_sprite.setTexture
        (game.renderer, game.getImage (IMAGE_GROUND_01));

    /* ground items layer */

    m_ground_item_sprites.resize (7);

    for (auto& sprite: m_ground_item_sprites)
    {
        sprite.setTexture (
            game.renderer,
            game.getImage ( (ImageEnum)
                Random::range (
                    IMAGE_GROUND_ITEM_01, IMAGE_GROUND_ITEM_03
                )
            )
        );
    }

    /* sprites */

    bool status = (
        initializeBird () &&
        initializeBoat () &&
        initializeCrab () &&
        initializeFish () &&
        initializeGoldenFish () &&
        initializePlayer () &&
        initializeTreasure () &&
        true
    );

    if (!status)
    {
        return false;
    }

    /* sprite layers */

    SDL_RenderGetViewport
        (game.renderer, &m_sprite_layer0.viewport_rect);

    m_sprite_layer0.setArea (GAME_CANVAS_WIDTH, GAME_CANVAS_HEIGHT);

    m_sprite_layer0.clear ();

    m_sprite_layer0.push_back (m_boat_sprite);
    m_sprite_layer0.push_back (m_treasure_sprite);
    m_sprite_layer0.push_back (m_crab_sprite);
    m_sprite_layer0.push_back (m_player_sprite);

    m_sprite_layer1.clear ();

    for (auto * const sprite: m_bird_sprites)
    {
        m_sprite_layer1.push_back (sprite);
    }

    for (auto * const sprite: m_fish_sprites)
    {
        m_sprite_layer1.push_back (sprite);
    }

    m_sprite_layer1.push_back (m_golden_fish_sprite);

    DEBUG_FUNCTION_EXIT;

    return true;
}


bool
ScreenGamePlay::initializeBird ()
{
    DEBUG_FUNCTION_ENTER;

    const Delay delay = GAME_DRAWINGS_DELAY_MS * 4;

    const ArraySize columns = 6;

    const ArraySize array_size = ARRAY_SIZE (m_bird_sprites);

    const ISize tile [array_size] =
    {
        { 160, 150 },
        { 90, 80 },
        { 120, 90 },
    };

    for (ArrayIndex i = 0; i < array_size; i++)
    {
        TileSetIndex row = 0;

        m_bird_sprites [i] = new AnimatedSprite;

        if (m_bird_sprites [i] == nullptr ||
            !m_bird_sprites [i]->initialize
            (game.renderer, game.getImage ((ImageEnum) (IMAGE_BIRD_01
            + i)), columns, tile [i].w, tile [i].h))
        {
            return Error::runtimeError (
                "Unable to create bird sprite.",
                __func__,
                "Null pointer sprite."
            );
        }

        m_bird_sprites [i]->data_array.clear ();

        m_bird_sprites [i]->data_array.push_back (
            {
                SPRITE_ANIMATION_STATE_FLY,
                SPRITE_ANIMATION_DIRECTION_LEFT,
                columns * row++,
                columns,
                delay
            }
        );

        m_bird_sprites [i]->data_array.push_back (
            {
                SPRITE_ANIMATION_STATE_FLY,
                SPRITE_ANIMATION_DIRECTION_RIGHT,
                columns * row++,
                columns,
                delay
            }
        );
    }

    DEBUG_FUNCTION_EXIT;

    return true;
}


bool
ScreenGamePlay::initializeBoat ()
{
    DEBUG_FUNCTION_ENTER;

    const Delay delay = GAME_DRAWINGS_DELAY_MS * 5;

    const ArraySize columns = 6;

    TileSetIndex row = 0;

    m_boat_sprite = new AnimatedSprite;

    if (m_boat_sprite == nullptr
        || !m_boat_sprite->initialize (game.renderer, game.getImage
        (IMAGE_BOAT_03), columns, 200, 150))
    {
        return Error::runtimeError (
            "Unable to create boat sprite.",
            __func__,
            "Null pointer sprite."
        );
    }

    m_boat_sprite->data_array.clear ();

    m_boat_sprite->data_array.push_back (
        {
            SPRITE_ANIMATION_STATE_WALK,
            SPRITE_ANIMATION_DIRECTION_LEFT,
            columns * row++,
            columns,
            delay
        }
    );

    m_boat_sprite->data_array.push_back (
        {
            SPRITE_ANIMATION_STATE_WALK,
            SPRITE_ANIMATION_DIRECTION_RIGHT,
            columns * row++,
            columns,
            delay
        }
    );

    m_boat_sprite->data_array.push_back (
        {
            SPRITE_ANIMATION_STATE_IDLE,
            SPRITE_ANIMATION_DIRECTION_LEFT,
            columns * row++,
            4,
            delay * 4
        }
    );

    m_boat_sprite->data_array.push_back (
        {
            SPRITE_ANIMATION_STATE_IDLE,
            SPRITE_ANIMATION_DIRECTION_RIGHT,
            columns * row++,
            4,
            delay * 4
        }
    );

    DEBUG_FUNCTION_EXIT;

    return true;
}


bool
ScreenGamePlay::initializeCrab ()
{
    DEBUG_FUNCTION_ENTER;

    const Delay delay = GAME_DRAWINGS_DELAY_MS * 20;

    const ArraySize columns = 2;

    m_crab_sprite = new AnimatedSprite;

    if (m_crab_sprite == nullptr
        || !m_crab_sprite->initialize (game.renderer, game.getImage
        (IMAGE_CRAB_01), columns, 110, 75))
    {
        return Error::runtimeError (
            "Unable to create crab sprite.",
            __func__,
            "Null pointer sprite."
        );
    }

    m_crab_sprite->data_array.clear ();

    m_crab_sprite->data_array.push_back (
        {
            SPRITE_ANIMATION_STATE_IDLE,
            SPRITE_ANIMATION_DIRECTION_LEFT,
            0,
            columns,
            delay
        }
    );

    DEBUG_FUNCTION_EXIT;

    return true;
}


bool
ScreenGamePlay::initializeFish ()
{
    DEBUG_FUNCTION_ENTER;

    const Delay delay = GAME_DRAWINGS_DELAY_MS * 8;

    const ArraySize columns = 12;

    const ArraySize array_size = ARRAY_SIZE (m_bird_sprites);

    const ISize tile [array_size] =
    {
        { 140, 110 },
        { 100, 70 },
        { 140, 150 },
    };

    for (ArrayIndex i = 0; i < array_size; i++)
    {
        TileSetIndex row = 0;

        m_fish_sprites [i] = new AnimatedSprite;

        if (m_fish_sprites [i] == nullptr
            || !m_fish_sprites [i]->initialize (game.renderer,
            game.getImage ((ImageEnum) (IMAGE_FISH_01 + i)), columns,
            tile [i].w, tile [i].h))
        {
            return Error::runtimeError (
                "Unable to create fish sprite.",
                __func__,
                "Null pointer sprite."
            );
        }

        m_fish_sprites [i]->data_array.clear ();

        m_fish_sprites [i]->data_array.push_back (
            {
                SPRITE_ANIMATION_STATE_SWIM,
                SPRITE_ANIMATION_DIRECTION_LEFT,
                columns * row++,
                columns,
                delay
            }
        );

        m_fish_sprites [i]->data_array.push_back (
            {
                SPRITE_ANIMATION_STATE_SWIM,
                SPRITE_ANIMATION_DIRECTION_RIGHT,
                columns * row++,
                columns,
                delay
            }
        );
    }

    DEBUG_FUNCTION_EXIT;

    return true;
}


bool
ScreenGamePlay::initializeGoldenFish ()
{
    DEBUG_FUNCTION_ENTER;

    const Delay delay = GAME_DRAWINGS_DELAY_MS * 8;

    const ArraySize columns = 6;

    TileSetIndex row = 0;

    m_golden_fish_sprite = new AnimatedSprite;

    if (m_golden_fish_sprite == nullptr
        || !m_golden_fish_sprite->initialize (game.renderer,
        game.getImage (IMAGE_GOLDEN_FISH_01), columns, 150, 100))
    {
        return Error::runtimeError (
            "Unable to create golden fish sprite.",
            __func__,
            "Null pointer sprite."
        );
    }

    m_golden_fish_sprite->data_array.clear ();

    m_golden_fish_sprite->data_array.push_back (
        {
            SPRITE_ANIMATION_STATE_SWIM,
            SPRITE_ANIMATION_DIRECTION_LEFT,
            columns * row++,
            columns,
            delay
        }
    );

    m_golden_fish_sprite->data_array.push_back (
        {
            SPRITE_ANIMATION_STATE_SWIM,
            SPRITE_ANIMATION_DIRECTION_RIGHT,
            columns * row++,
            columns,
            delay
        }
    );

    DEBUG_FUNCTION_EXIT;

    return true;
}


bool
ScreenGamePlay::initializePlayer ()
{
    DEBUG_FUNCTION_ENTER;

    const Delay delay = GAME_DRAWINGS_DELAY_MS * 8;

    const ArraySize columns = 12;

    TileSetIndex row = 0;

    m_player_sprite = new AnimatedSprite;

    if (m_player_sprite == nullptr
        || !m_player_sprite->initialize (game.renderer, game.getImage
        (IMAGE_SCUBA_DIVER_01), columns, 240, 200))
    {
        return Error::runtimeError (
            "Unable to create player sprite.",
            __func__,
            "Null pointer sprite."
        );
    }

    SpriteAnimationStateFlags states [] =
    {
        SPRITE_ANIMATION_STATE_ENJOY,
        SPRITE_ANIMATION_STATE_IDLE,
        SPRITE_ANIMATION_STATE_SWIM
    };

    m_player_sprite->data_array.clear ();

    for (const auto& state: states)
    {
        m_player_sprite->data_array.push_back (
            {
                state,
                SPRITE_ANIMATION_DIRECTION_LEFT,
                columns * row++,
                columns,
                delay
            }
        );

        m_player_sprite->data_array.push_back (
            {
                state,
                SPRITE_ANIMATION_DIRECTION_RIGHT,
                columns * row++,
                columns,
                delay
            }
        );
    }

    DEBUG_FUNCTION_EXIT;

    return true;
}


bool
ScreenGamePlay::initializeTreasure ()
{
    DEBUG_FUNCTION_ENTER;

    const Delay delay = GAME_DRAWINGS_DELAY_MS * 4;

    m_treasure_sprite = new AnimatedSprite;

    if (m_treasure_sprite == nullptr
        || !m_treasure_sprite->initialize (game.renderer, game.getImage
        (IMAGE_TREASURE_CHEST_01), 7, 100, 100))
    {
        return Error::runtimeError (
            "Unable to create treasure sprite.",
            __func__,
            "Null pointer sprite."
        );
    }

    m_treasure_sprite->data_array.clear ();

    m_treasure_sprite->data_array.push_back (
        {
            SPRITE_ANIMATION_STATE_IDLE,
            SPRITE_ANIMATION_DIRECTION_LEFT,
            0,
            1,
            0
        }
    );

    m_treasure_sprite->data_array.push_back (
        {
            SPRITE_ANIMATION_STATE_LOSE,
            SPRITE_ANIMATION_DIRECTION_LEFT,
            0,
            6,
            delay
        }
    );

    m_treasure_sprite->data_array.push_back (
        {
            SPRITE_ANIMATION_STATE_WIN,
            SPRITE_ANIMATION_DIRECTION_LEFT,
            0,
            7,
            delay
        }
    );

    DEBUG_FUNCTION_EXIT;

    return true;
}


ScreenEnum
ScreenGamePlay::onExit (ScreenEnum screen)
{
    DEBUG_FUNCTION_ENTER;

    m_bird_sprites [m_bird_index]->stopAnimation ();
    m_boat_sprite->stopAnimation ();
    m_crab_sprite->stopAnimation ();
    m_fish_sprites [m_fish_index]->stopAnimation ();
    m_golden_fish_sprite->stopAnimation ();
    m_player_sprite->stopAnimation ();
    m_treasure_sprite->stopAnimation ();

    DEBUG_FUNCTION_EXIT;

    return screen;
}


void
ScreenGamePlay::playerAction ()
{
    DEBUG_FUNCTION_ENTER;

    if (m_game_is_paused) return;

    /* golden fish */

    if (m_golden_fish_lifetime
        && m_player_sprite->collides (m_golden_fish_sprite))
    {
        m_oxygen_prc = std::min (100, m_oxygen_prc + 25);
        m_golden_fish_lifetime = 0;
        m_golden_fish_sprite->color.a = 0;
    }

    /* treasure chest */

    if (m_player_sprite->collides (m_treasure_sprite) && !m_wait_sync)
    {
        m_wait_sync = true;

        playerIdle ();

        if (Random::randomize (3) == 1)
        {
            m_treasure_sprite->reset (
                SPRITE_ANIMATION_TYPE_SEQUENTIAL,
                SPRITE_ANIMATION_STATE_WIN,
                SPRITE_ANIMATION_DIRECTION_LEFT
            );

            if (m_score++ < 3)
            {
                game.emitSound (SOUND_WIN);
            }
        }
        else
        {
            m_treasure_sprite->reset (
                SPRITE_ANIMATION_TYPE_SEQUENTIAL,
                SPRITE_ANIMATION_STATE_LOSE,
                SPRITE_ANIMATION_DIRECTION_LEFT
            );

            game.emitSound (SOUND_LOSE);
        }

        m_treasure_sprite->tile_set_index = 0;
        m_treasure_sprite->sequence_ended = false;
    }

    DEBUG_FUNCTION_EXIT;
}


void
ScreenGamePlay::playerIdle ()
{
    DEBUG_FUNCTION_ENTER;

    if (m_game_is_paused) return;

    m_player_sprite->direction = { 0, 0 };

    if (m_player_sprite->anchor.y >
        m_sprite_layer0.box.topSide () + game.window_center.y)
    {
        m_player_sprite->reset (
            SPRITE_ANIMATION_TYPE_LOOP,
            SPRITE_ANIMATION_STATE_IDLE,
            m_player_sprite->direction_flags
        );
    }
    else
    {
        m_player_sprite->reset (
            SPRITE_ANIMATION_TYPE_LOOP,
            SPRITE_ANIMATION_STATE_ENJOY,
            m_player_sprite->direction_flags
        );
    }

    DEBUG_FUNCTION_EXIT;
}


void
ScreenGamePlay::playerMoveDown ()
{
    DEBUG_FUNCTION_ENTER;

    if (m_game_is_paused) return;

    m_player_sprite->direction.y =
        std::min (+1, m_player_sprite->direction.y + 1);

    if (m_player_sprite->direction.x || m_player_sprite->direction.y)
    {
        m_player_sprite->reset (
            SPRITE_ANIMATION_TYPE_LOOP,
            SPRITE_ANIMATION_STATE_SWIM,
            m_player_sprite->direction_flags
        );
    }
    else
    {
        playerIdle ();
    }

    DEBUG_FUNCTION_EXIT;
}


void
ScreenGamePlay::playerMoveLeft ()
{
    DEBUG_FUNCTION_ENTER;

    if (m_game_is_paused) return;

    m_player_sprite->direction.x =
        std::max (-1, m_player_sprite->direction.x - 1);

    if (m_player_sprite->direction.x || m_player_sprite->direction.y)
    {
        m_player_sprite->reset (
            SPRITE_ANIMATION_TYPE_LOOP,
            SPRITE_ANIMATION_STATE_SWIM,
            (m_player_sprite->direction.x < 0) ?
            SPRITE_ANIMATION_DIRECTION_LEFT :
            SPRITE_ANIMATION_DIRECTION_RIGHT
        );
    }
    else
    {
        playerIdle ();
    }

    DEBUG_FUNCTION_EXIT;
}


void
ScreenGamePlay::playerMoveRight ()
{
    DEBUG_FUNCTION_ENTER;

    if (m_game_is_paused) return;

    m_player_sprite->direction.x =
        std::min (+1, m_player_sprite->direction.x + 1);

    if (m_player_sprite->direction.x || m_player_sprite->direction.y)
    {
        m_player_sprite->reset (
            SPRITE_ANIMATION_TYPE_LOOP,
            SPRITE_ANIMATION_STATE_SWIM,
            (m_player_sprite->direction.x > 0) ?
            SPRITE_ANIMATION_DIRECTION_RIGHT :
            SPRITE_ANIMATION_DIRECTION_LEFT
        );
    }
    else
    {
        playerIdle ();
    }

    DEBUG_FUNCTION_EXIT;
}


void
ScreenGamePlay::playerMoveUp ()
{
    DEBUG_FUNCTION_ENTER;

    if (m_game_is_paused) return;

    m_player_sprite->direction.y =
        std::max (-1, m_player_sprite->direction.y - 1);

    if (m_player_sprite->direction.x || m_player_sprite->direction.y)
    {
        m_player_sprite->reset (
            SPRITE_ANIMATION_TYPE_LOOP,
            SPRITE_ANIMATION_STATE_SWIM,
            m_player_sprite->direction_flags
        );
    }
    else
    {
        playerIdle ();
    }

    DEBUG_FUNCTION_EXIT;
}


void
ScreenGamePlay::playerRecenter ()
{
    DEBUG_FUNCTION_ENTER;

    if (m_game_is_paused) return;

    m_player_sprite->setPosition (
        game.window_center.x,
        m_player_sprite->anchor.y
    );

    playerIdle ();

    DEBUG_FUNCTION_EXIT;
}


ScreenEnum
ScreenGamePlay::reset ()
{
    DEBUG_FUNCTION_ENTER;

    /* misc */

    game.playMusic ( (MusicEnum)
        Random::range (MUSIC_PLAY_1, MUSIC_PLAY_2)
    );

    game.user_info->reset ();

    m_game_is_paused = false;
    m_wait_sync = false;

    m_oxygen_prc = 100;
    m_score = 0;

    const int common_dy = 5;

    /* sky dome layer */

    m_sky_sprite.setPosition (0, 0, ANCHOR_NORTH_WEST);

    /* clouds layer */

    m_cloud_sprites.setPosition (0, 0, ANCHOR_NORTH_WEST);

    m_cloud_sprites.dx = 3;
    m_cloud_sprites.dy = common_dy;
    m_cloud_sprites.direction = { 0, 0 };

    for (auto& sprite: m_cloud_sprites)
    {
        sprite.setPosition (
            Random::randomize (game.window_size.w),
            Random::range (20, game.window_center.y - 50),
            ANCHOR_CENTER
        );
        sprite.dx = 1;
        sprite.dy = 0;
        sprite.direction = { (Random::randomize (1) ? +1 : -1), 0 };
    }

    /* sprite layer 0 */

    m_sprite_layer0.setPosition
        (game.window_center.x, 0, ANCHOR_NORTH);

    m_sprite_layer0.dx = 5;
    m_sprite_layer0.dy = common_dy;
    m_sprite_layer0.direction = { 0, 0 };

    /* sprite layer 1 */

    m_sprite_layer1.setPosition (0, 0, ANCHOR_NORTH_WEST);

    m_sprite_layer1.dx = 7;
    m_sprite_layer1.dy = common_dy;
    m_sprite_layer1.direction = { 0, 0 };

    /* ground layer */

    m_ground_sprite.setPosition
        (0, m_sprite_layer0.box.bottomSide (), ANCHOR_SOUTH_WEST);

    /* ground items layer */

    m_ground_item_sprites.setPosition (0, 0, ANCHOR_NORTH_WEST);

    m_ground_item_sprites.dx = m_sprite_layer0.dx;
    m_ground_item_sprites.dy = common_dy;
    m_ground_item_sprites.direction = { 0, 0 };

    const int w =
        m_sprite_layer0.area().w / m_ground_item_sprites.size ();

    ArrayIndex i = 0;

    for (auto& sprite: m_ground_item_sprites)
    {
        sprite.setPosition (
            m_sprite_layer0.box.leftSide () + i * w +
                Random::randomize (w),
            m_sprite_layer0.box.bottomSide () -
                10 * Random::range (8, 11),
            ANCHOR_CENTER
        );
        i++;
    }

    /* player */

    m_player_sprite->setPosition (
        game.window_center.x / 2,
        game.window_center.y,
        ANCHOR_CENTER
    );

    m_player_sprite->dx = m_sprite_layer0.dx;
    m_player_sprite->dy = m_sprite_layer0.dy;
    m_player_sprite->direction = { 0, 0 };

    m_player_sprite->reset (
        SPRITE_ANIMATION_TYPE_LOOP,
        SPRITE_ANIMATION_STATE_ENJOY,
        SPRITE_ANIMATION_DIRECTION_RIGHT
    );

    playerIdle ();

    m_player_sprite->startAnimation ();

    /* bird */

    changeBird (
        { game.window_center.x + Random::range (-50, +50), 0 },
        { Random::randomize (1), 0 }
    );

    /* boat */

    m_boat_sprite->setPosition (
        game.window_center.x +
            Random::randomize (game.window_size.w / 4),
        game.window_center.y - 40,
        ANCHOR_CENTER
    );

    m_boat_sprite->reset (
        SPRITE_ANIMATION_TYPE_LOOP,
        SPRITE_ANIMATION_STATE_IDLE,
        SPRITE_ANIMATION_DIRECTION_LEFT
    );

    m_boat_sprite->startAnimation ();

    /* crab */

    m_crab_sprite->setPosition (
        Random::randomize (game.window_size.w),
        m_sprite_layer0.box.bottomSide () - 10,
        ANCHOR_SOUTH
    );

    m_crab_sprite->dx = 0;
    m_crab_sprite->dy = 0;
    m_crab_sprite->direction = { 0, 0 };

    m_crab_sprite->reset (
        SPRITE_ANIMATION_TYPE_LOOP,
        SPRITE_ANIMATION_STATE_IDLE,
        SPRITE_ANIMATION_DIRECTION_LEFT
    );

    m_crab_sprite->startAnimation ();

    /* fish */

    changeFish ( game.window_center, { Random::range (-1, +1), 0 } );

    /* golden fish */

    m_golden_fish_sprite->setPosition
        (game.window_center, ANCHOR_CENTER);

    m_golden_fish_sprite->color.a = 0;

    m_golden_fish_lifetime = 0;

    m_golden_fish_sprite->dx = 3;
    m_golden_fish_sprite->dy = 0;
    m_golden_fish_sprite->direction = { 0, 0 };

    m_golden_fish_sprite->reset (
        SPRITE_ANIMATION_TYPE_LOOP,
        SPRITE_ANIMATION_STATE_SWIM,
        SPRITE_ANIMATION_DIRECTION_LEFT
    );

    m_golden_fish_sprite->startAnimation ();

    /* treasure chest */

    m_treasure_sprite->setPosition (
        Random::range (
            m_sprite_layer0.box.leftSide () + 100,
            m_sprite_layer0.box.rightSide () - 100
        ),
        m_sprite_layer0.box.bottomSide () - Random::range (40, 100),
        ANCHOR_CENTER
    );

    m_treasure_sprite->dx = 0;
    m_treasure_sprite->dy = 0;
    m_treasure_sprite->direction = { 0, 0 };

    m_treasure_sprite->color.a = -1;

    m_treasure_sprite->reset (
        SPRITE_ANIMATION_TYPE_STATIC,
        SPRITE_ANIMATION_STATE_IDLE,
        SPRITE_ANIMATION_DIRECTION_LEFT
    );

    m_treasure_sprite->startAnimation ();

    DEBUG_FUNCTION_EXIT;

    return SCREEN_DEFAULT;
}


void
ScreenGamePlay::toggleGamePause ()
{
    DEBUG_FUNCTION_ENTER;

    m_game_is_paused = !m_game_is_paused;

    DEBUG_FUNCTION_EXIT;
}

