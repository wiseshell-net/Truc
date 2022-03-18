/*
 * game_part.hpp
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

#ifndef _GAME_PART_HPP
#define _GAME_PART_HPP

/**
 * \file
 * \brief Base class for game component.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include "game.hpp"


/**
 * \brief Base class for game component.
 */
class GamePart
{
public:

    Game&   game;

public:

    /**
     * \brief Class constructor.
     */
    GamePart (Game& game);


    /**
     * \brief Class destructor.
     */
    virtual ~GamePart ();

};


#endif /* _GAME_PART_HPP */
