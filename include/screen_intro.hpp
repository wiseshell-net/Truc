/*
 * screen_intro.hpp
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

#ifndef _SCREEN_INTRO_HPP
#define _SCREEN_INTRO_HPP

#include <vector>

#include <SDL.h>

#include "screen_base.hpp"
#include "sprite_array.hpp"
#include "sprite.hpp"


struct ScreenIntro : public ScreenBase
{
protected:

    SpriteArray m_sprites;
    Sprite      m_title_sprite;
    Sprite      m_tip_sprite;

public:

    ScreenIntro (Game& game);

    virtual ~ScreenIntro ();

    virtual bool initialize ();

protected:

    virtual ScreenEnum doDrawings ();

    virtual ScreenEnum doEvents ();

    virtual ScreenEnum doLogic ();

    virtual ScreenEnum onExit (ScreenEnum screen);

    virtual ScreenEnum reset ();

};


#endif /* _SCREEN_INTRO_HPP */