/*
 * random.cpp
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

#include <cstdlib>
#include <ctime>

#include "random.hpp"

#include "debug.hpp"


namespace Random
{

void
initialize ()
{
    DEBUG_FUNCTION_ENTER;

    std::srand (std::time (nullptr));

    DEBUG_FUNCTION_EXIT;
}


int
randomize (const int n)
{
    DEBUG_FUNCTION_CALL;

    return (n + 1) ? std::rand () % (n + 1) : std::rand ();
}


int
range (const int start, const int end)
{
    DEBUG_FUNCTION_CALL;

    return (start > end) ?
        end + randomize (start - end)
        : start + randomize (end - start);
}

} /* namespace */

