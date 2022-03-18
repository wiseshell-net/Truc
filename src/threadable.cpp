/*
 * threadable.cpp
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

#include "threadable.hpp"

#include "debug.hpp"
#include "error.hpp"


Threadable::Threadable () :
m_thread (nullptr),
m_thread_mutex (nullptr),
m_thread_enabled (false)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


Threadable::~Threadable ()
{
    DEBUG_FUNCTION_ENTER;

    m_thread_enabled = false;

    SDL_LockMutex (m_thread_mutex);
    SDL_UnlockMutex (m_thread_mutex);
    SDL_DestroyMutex (m_thread_mutex);

    SDL_WaitThread (m_thread, nullptr);

    DEBUG_FUNCTION_EXIT;
}


void
Threadable::detachThread ()
{
    DEBUG_FUNCTION_ENTER;

    SDL_DetachThread (m_thread);

    m_thread = nullptr;

    DEBUG_FUNCTION_EXIT;
}


void
Threadable::endThreadFunction ()
{
    DEBUG_FUNCTION_ENTER;

    m_thread_enabled = false;

    m_thread = nullptr;

    DEBUG_FUNCTION_EXIT;
}


bool
Threadable::initializeThread ()
{
    DEBUG_FUNCTION_ENTER;

    SDL_WaitThread (m_thread, nullptr);

    m_thread = nullptr;

    m_thread_enabled = false;

    if (m_thread_mutex == nullptr)
    {
        m_thread_mutex = SDL_CreateMutex ();

        if (m_thread_mutex == nullptr)
        {
            Error::runtimeError (
                "Unable to initialize thread support.",
                __func__,
                "Null pointer 'mutex' after initialization."
            );

            return Error::sdlError ("Unable to create mutex.");
        }
    }

    DEBUG_FUNCTION_EXIT;

    return true;
}


bool
Threadable::isThreadAttached () const
{
    DEBUG_FUNCTION_CALL;

    return (m_thread != nullptr);
}


bool
Threadable::isThreadEnabled () const
{
    DEBUG_FUNCTION_CALL;

    return m_thread_enabled;
}


void
Threadable::lockThreadMutex ()
{
    DEBUG_FUNCTION_ENTER;

    SDL_LockMutex (m_thread_mutex);

    DEBUG_FUNCTION_EXIT;
}


bool
Threadable::startThread (
        ThreadFunction * const thread_function,
        const char * const thread_name,
        void * const thread_data,
        const bool safe_mode
    )
{
    DEBUG_FUNCTION_CALL;

    if (thread_function != nullptr
        && thread_name != nullptr
        && thread_name [0])
    {
        if (isThreadAttached ())
        {
            return Error::runtimeError (
                "Unable to start thread.",
                __func__,
                "A thread is already attached and running."
            );
        }

        if (safe_mode)
        {
            if (!tryLockThreadMutex ())
            {
                return Error::runtimeError (
                    "Unable to start thread (SAFE MODE).",
                    __func__,
                    "Thread mutex is locked."
                );
            }

            unlockThreadMutex ();
        }

        m_thread_enabled = true;

        m_thread = SDL_CreateThread
            (thread_function, thread_name, thread_data);

        if (m_thread == nullptr)
        {
            m_thread_enabled = false;

            return Error::sdlError ("Unable to create thread.");
        }

        return true;
    }

    return Error::runtimeError (
        "Unable to start thread.",
        __func__,
        "Invalid arguments (thread_name / thread_function)."
    );
}


void
Threadable::stopThread ()
{
    DEBUG_FUNCTION_ENTER;

    m_thread_enabled = false;

    SDL_WaitThread (m_thread, nullptr);

    m_thread = nullptr;

    DEBUG_FUNCTION_EXIT;
}


bool
Threadable::tryLockThreadMutex ()
{
    DEBUG_FUNCTION_CALL;

    return (SDL_TryLockMutex (m_thread_mutex) == EXIT_SUCCESS);
}


void
Threadable::unlockThreadMutex ()
{
    DEBUG_FUNCTION_ENTER;

    SDL_UnlockMutex (m_thread_mutex);

    DEBUG_FUNCTION_EXIT;
}

