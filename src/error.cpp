/*
 * error.cpp
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

#include "error.hpp"

#include <cstdio>
#include <cstdlib>

#include <SDL.h>


namespace Error
{

void
assertFatal (
        bool true_condition,
        const char * const message,
        ...
    )
{
    if (!true_condition)
    {
        va_list args;
        va_start (args, message);
        fatalError (message, args);
        va_end (args);
    }
}


void
assertWarn (
        bool true_condition,
        const char * const message,
        ...
    )
{
    if (!true_condition)
    {
        fprintf (stderr, "[WARNING]\t");

        if (message != nullptr && message [0])
        {
            va_list args;
            va_start (args, message);
            vfprintf (stderr, message, args);
            va_end (args);
        }
        else
        {
            fprintf (stderr, "Assertion failed.");
        }

        fprintf (stderr, "\n");
    }
}


void
fatalError (const char * const message, ...)
{
    fprintf (stderr, "[ERROR]\t");

    if (message != nullptr && message [0])
    {
        va_list args;
        va_start (args, message);
        vfprintf (stderr, message, args);
        va_end (args);
    }
    else
    {
        fprintf (stderr, "A fatal error has occurred.");
    }

    fprintf (stderr, "\n[FATAL]\tExiting by now.\n\n");

    exit (EXIT_FAILURE);
}


bool
runtimeError (
        const char * const message,
        const char * const origin,
        const char * const cause,
        ...
    )
{
    fprintf (stderr, "[ERROR]\t");

    if (message != nullptr && message [0])
    {
        fprintf (stderr, "%s\n", message);
    }
    else
    {
        fprintf (stderr, "A runtime error has occurred.\n");
    }

    if (origin != nullptr && origin [0]
        && cause != nullptr && cause [0])
    {
        va_list args;
        va_start (args, cause);
        fprintf (stderr, "[%s]\t", origin);
        vfprintf (stderr, cause, args);
        fprintf (stderr, "\n");
        va_end (args);
    }

    return false;
}


bool
sdlError (const char * const message, ...)
{
    fprintf (stderr, "[ERROR]\t");

    if (message != nullptr && message [0])
    {
        va_list args;
        va_start (args, message);
        vfprintf (stderr, message, args);
        va_end (args);
    }
    else
    {
        fprintf (stderr, "An SDL error has occurred.");
    }

    fprintf (stderr, "\n[SDL]\t%s\n", SDL_GetError ());

    return false;
}

} /* namespace */

