/*
 * debug.cpp
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

#include "debug.hpp"


namespace Debug
{

void
functionCall (const char * const function_name)
{
    if (function_name != nullptr && function_name [0])
    {
#ifdef DEBUG
        fprintf (
            stderr,
            "[DEBUG][CALL]\tCalling %s ().\n",
            function_name
        );
#endif
    }
}


void
functionEnter (const char * const function_name)
{
    if (function_name != nullptr && function_name [0])
    {
#ifdef DEBUG
        fprintf (
            stderr,
            "[DEBUG][ENTER]\tEntering %s ().\n",
            function_name
        );
#endif
    }
}


void
functionExit (const char * const function_name)
{
    if (function_name != nullptr && function_name [0])
    {
#ifdef DEBUG
        fprintf (
            stderr,
            "[DEBUG][EXIT]\tLeaving %s ().\n",
            function_name
        );
#endif
    }
}


void
info (const char * const message, ...)
{
    if (message != nullptr && message [0])
    {
#ifdef DEBUG
        fprintf (stderr, "[DEBUG][INFO]\t");
        va_list args;
        va_start (args, message);
        vfprintf (stderr, message, args);
        va_end (args);
        fprintf (stderr, "\n");
#endif
    }
}

} /* namespace */

