/*
 * debug.hpp
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

#ifndef _DEBUG_HPP
#define _DEBUG_HPP

/**
 * \file
 * \brief Debugging session utility tools.
 *
 * This header file declares debugging session utility tools.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <cstdarg>
#include <cstdio>


#ifdef DEBUG
    #define DEBUG_FUNCTION_CALL     Debug::functionCall (__func__)
    #define DEBUG_FUNCTION_ENTER    Debug::functionEnter (__func__)
    #define DEBUG_FUNCTION_EXIT     Debug::functionExit (__func__)
#else
    #define DEBUG_FUNCTION_CALL
    #define DEBUG_FUNCTION_ENTER
    #define DEBUG_FUNCTION_EXIT
#endif


/**
 * \brief Debugging session utility tools namespace.
 *
 * These utility tools become active only when DEBUG preprocessor macro
 * is defined, generally at compilation time e.g.
 * <tt>g++ -g -DDEBUG ...</tt>
 *
 * All debugging outputs are done through \c stderr file descriptor.
 */
namespace Debug
{

    /**
     * \brief Debugging trace on short function enter.
     *
     * Puts a debugging trace on function start where it is not
     * possible to also put a function end trace.
     *
     * \param function_name - function name where we are supposed to be
     * when the trace is put.
     */
    void functionCall (const char * const function_name);


    /**
     * \brief Debugging trace on function enter.
     *
     * Puts a debugging trace on function start where it is also
     * possible to put a function end trace.
     *
     * \param function_name - function name where we are supposed to be
     * when the trace is put.
     */
    void functionEnter (const char * const function_name);


    /**
     * \brief Debugging trace on function exit.
     *
     * Puts a debugging trace on function end.
     *
     * \param function_name - function name where we are supposed to be
     * when the trace is put.
     */
    void functionExit (const char * const function_name);


    /**
     * \brief Debugging trace user-defined information.
     *
     * Puts a debugging trace with user-defined formatted informations.
     *
     * Works as C function printf(), but only when DEBUG preprocessor
     * macro is defined (on debugging session).
     *
     * \param message - formatted message string of chars, same as in C
     * function printf(message, ...).
     * \param ... - any necessary additional argument, same as in C
     * function printf(message, ...).
     */
    void info (const char * const message, ...);

} /* namespace */


#endif /* _DEBUG_HPP */
