/*
 * threadable.hpp
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

#ifndef _THREADABLE_HPP
#define _THREADABLE_HPP

/**
 * \file
 * \brief Interface for threadable objects.
 *
 * This header file declares an interface structure to re-implement in
 * threadable descendant structures / classes, if necessary.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <SDL.h>


/* Threadable interface */


/**
 * \brief Type definition for function to be called by thread.
 */
typedef int ThreadFunction (void * const data);


/**
 * \brief Interface for threadable object structures / classes.
 */
struct Threadable
{
protected:

    SDL_Thread *    m_thread;
    SDL_mutex *     m_thread_mutex;
    bool            m_thread_enabled;

public:

    /**
     * \brief Structure constructor.
     */
    Threadable ();


    /**
     * \brief Structure destructor.
     */
    virtual ~Threadable ();


    /**
     * \brief Makes thread independent from caller i.e. from main
     * running thread, generally.
     */
    virtual void detachThread ();


    /**
     * \brief Finalizes thread before exiting callback function.
     *
     * Clears up thread internals.
     */
    virtual void endThreadFunction ();


    /**
     * \brief Tries to initialize thread support.
     *
     * \return true if all went OK, false otherwise.
     */
    virtual bool initializeThread ();


    /**
     * \brief Tells if thread is currently attached to main thread (and
     * thus running) or not.
     *
     * \return true if thread is now attached, false otherwise.
     */
    virtual bool isThreadAttached () const;


    /**
     * \brief Tells if thread is currently enabled or not.
     *
     * Useful for unlocking loops in thread function callbacks.
     *
     * \return true if thread is now enabled, false otherwise.
     */
    virtual bool isThreadEnabled () const;


    /**
     * \brief Locks thread's mutex - waits until locking is complete.
     */
    virtual void lockThreadMutex ();


    /**
     * \brief Starts a new thread.
     *
     * \param thread_function - function callback to be called by
     * thread, once launched.
     * \param thread_name - thread identification name, string of
     * chars.
     * \param thread_data - opaque pointer for thread data to pass to
     * thread_function callback.
     * \param safe_mode - true, starts in safe mode i.e. ensures thread
     * mutex is unlocked and available, false, starts straight away.
     *
     * \return true if all went OK, false otherwise.
     *
     * \note THREAD_START (thread_function, thread_data) and
     * THREAD_START_SAFE (thread_function, thread_data) macro defines
     * are also available.
     */
    virtual bool startThread (
        ThreadFunction * const thread_function,
        const char * const thread_name,
        void * const thread_data,
        const bool safe_mode = false
    );


    /**
     * \brief Asks current running thread to stop.
     *
     * Thread function callback must ensure to unlock loops with
     * isThreadEnabled () test.
     *
     * If thread is attached to main running thread, this method will
     * wait for thread to end up before going on.
     *
     * Detached thread will only be asked to stop through
     * isThreadEnabled () test with no longer waiting.
     */
    virtual void stopThread ();


    /**
     * \brief Tries to lock thread mutex with no longer waiting.
     *
     * \return true if thread mutex got locked, false otherwise.
     */
    virtual bool tryLockThreadMutex ();


    /**
     * \brief Unlocks thread mutex.
     */
    virtual void unlockThreadMutex ();
};


#define THREAD_START(thread_function, thread_data) \
    startThread (thread_function, #thread_function, thread_data, false)

#define THREAD_START_SAFE(thread_function, thread_data) \
    startThread (thread_function, #thread_function, thread_data, true)


#endif /* _THREADABLE_HPP */
