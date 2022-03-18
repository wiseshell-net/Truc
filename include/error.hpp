/*
 * error.hpp
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

#ifndef _ERROR_HPP
#define _ERROR_HPP

/**
 * \file
 * \brief Error management API.
 *
 * This header file declares utility tools for error management.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <cstdarg>


#define ERROR_EXIT_SUCCESS   0
#define ERROR_EXIT_FAILURE  -1


/**
 * \brief Error management utility tools namespace.
 *
 * All error message outputs are done through \c stderr file
 * descriptor.
 */
namespace Error
{

    /**
     * \brief Outputs a user formatted message and exits program
     * immediately if the asserted expression reveals to be false.
     *
     * \param true_condition - boolean expression to evaluate as true.
     * \param message - user formatted message string of chars, same as
     * C function printf(message, ...).
     * \param ... - any necessary additional argument, same as C
     * function printf(message, ...).
     */
    void assertFatal (
        bool true_condition,
        const char * const message,
        ...
    );


    /**
     * \brief Outputs a user formatted message if the asserted
     * expression reveals to be false.
     *
     * \param true_condition - boolean expression to evaluate as true.
     * \param message - user formatted message string of chars, same as
     * C function printf(message, ...).
     * \param ... - any necessary additional argument, same as C
     * function printf(message, ...).
     */
    void assertWarn (
        bool true_condition,
        const char * const message,
        ...
    );


    /**
     * \brief Outputs a user formatted message and exits program
     * immediately.
     *
     * \param message - user formatted message string of chars, same as
     * C function printf(message, ...).
     * \param ... - any necessary additional argument, same as C
     * function printf(message, ...).
     */
    void fatalError (
        const char * const message,
        ...
    );


    /**
     * \brief Outputs a user formatted message.
     *
     * \param message - unformatted string of chars, mentions what
     * happened.
     * \param origin - unformatted string of chars, mentions where it
     * happened (in which function name).
     * \param cause - user formatted string of chars, same as C
     * function printf(cause, ...), more details about error.
     * \param ... - any necessary additional argument, same as C
     * function printf(cause, ...).
     *
     * \return always false.
     */
    bool runtimeError (
        const char * const message,
        const char * const origin,
        const char * const cause,
        ...
    );


    /**
     * \brief Outputs a user formatted message appended with an SDL
     * error message.
     *
     * \param message - user formatted message string of chars, same as
     * C function printf(message, ...).
     * \param ... - any necessary additional argument, same as C
     * function printf(message, ...).
     *
     * \return always false.
     */
    bool sdlError (
        const char * const message,
        ...
    );

} /* namespace */


#endif /* _ERROR_HPP */
