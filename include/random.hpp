/*
 * random.hpp
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

#ifndef _RANDOM_HPP
#define _RANDOM_HPP

/**
 * \file
 * \brief Random number utility tools.
 *
 * This header file declares random number utility tools.
 *
 * \see https://en.cppreference.com/w/cpp/numeric/random/rand
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */


/**
 * \brief Random number utility tools namespace.
 *
 * \see https://en.cppreference.com/w/cpp/numeric/random/rand
 */
namespace Random
{

    /**
     * \brief Initializes random number seeds.
     */
    void initialize ();


    /**
     * \brief Gets a random number between 0 and given value (bounds
     * included).
     *
     * \param n - highest value in random selection.
     *
     * \return random number between 0 and n (bounds included).
     *
     * \see https://en.cppreference.com/w/cpp/numeric/random/RAND_MAX
     */
    int randomize (const int n);


    /**
     * \brief Gets a random number between a given start value and a
     * given end value (bounds included).
     *
     * \param start - lowest value in random selection.
     * \param end   - highest value in random selection.
     *
     * \return random number between start and end (bounds included).
     *
     * \see https://en.cppreference.com/w/cpp/numeric/random/RAND_MAX
     */
    int range (const int start, const int end);

} /* namespace */


#endif /* _RANDOM_HPP */
