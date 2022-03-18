/*
 * array.cpp
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

#ifndef _ARRAY_CPP
#define _ARRAY_CPP

#include "array.hpp"

#include "debug.hpp"


/* Array */


template <typename T>
Array<T>::Array () :
std::vector<T> (),
m_array_index (0)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


template <typename T>
Array<T>::Array (const ArraySize& size) :
std::vector<T> (size),
m_array_index (0)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


template <typename T>
Array<T>::~Array ()
{
    DEBUG_FUNCTION_ENTER;

    Debug::info ("clearing %zu items.", this->size ());

    DEBUG_FUNCTION_EXIT;
}


template <typename T>
ArrayIndex
Array<T>::getIndex () const
{
    DEBUG_FUNCTION_CALL;

    return m_array_index;
}


template <typename T>
ArrayIndex
Array<T>::getIndexMax () const
{
    DEBUG_FUNCTION_CALL;

    return this->size () - 1;
}


template <typename T>
void
Array<T>::indexAdd (const int qty)
{
    DEBUG_FUNCTION_ENTER;

    setIndex (getIndex () + qty);

    DEBUG_FUNCTION_EXIT;
}


template <typename T>
T&
Array<T>::indexedItem ()
{
    DEBUG_FUNCTION_CALL;

    return this->at (getIndex ());
}


template <typename T>
const T&
Array<T>::indexedItem () const
{
    DEBUG_FUNCTION_CALL;

    return this->at (getIndex ());
}


template <typename T>
void
Array<T>::modulateIndex ()
{
    DEBUG_FUNCTION_ENTER;

    setIndex (getIndex () % this->size ());

    DEBUG_FUNCTION_EXIT;
}


template <typename T>
void
Array<T>::setBoundIndex (const ArrayIndex& index)
{
    DEBUG_FUNCTION_ENTER;

    setIndex (std::min (index, getIndexMax ()));

    DEBUG_FUNCTION_EXIT;
}


template <typename T>
void
Array<T>::setIndex (const ArrayIndex& index)
{
    DEBUG_FUNCTION_ENTER;

    m_array_index = index;

    DEBUG_FUNCTION_EXIT;
}


/* PArray - Array of Pointers with automatic deletion on clear () */


template <typename T>
PArray<T>::PArray () :
Array<T> ()
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


template <typename T>
PArray<T>::PArray (const ArraySize& size) :
Array<T> (size)
{
    DEBUG_FUNCTION_ENTER;

    DEBUG_FUNCTION_EXIT;
}


template <typename T>
PArray<T>::~PArray ()
{
    DEBUG_FUNCTION_ENTER;

    clear ();

    DEBUG_FUNCTION_EXIT;
}


template <typename T>
void
PArray<T>::clear ()
{
    DEBUG_FUNCTION_ENTER;

    for (auto * const instance: *this)
    {
        delete instance;
    }

    Debug::info ("cleared %zu items.", this->size ());

    Array<T>::clear ();

    DEBUG_FUNCTION_EXIT;
}


#endif /* _ARRAY_CPP */
