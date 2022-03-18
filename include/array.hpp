/*
 * array.hpp
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

#ifndef _ARRAY_HPP
#define _ARRAY_HPP

/**
 * \file
 * \brief Generic types array management.
 *
 * This header file declares and defines a template structure for
 * generic types array management.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <vector>

#include "array_defs.hpp"


/**
 * \brief Template structure for generic types array management.
 *
 * This structure extends std::vector dynamic array class (STL) with
 * some specific features.
 *
 * It is optimized for object types and reference-only pointers to
 * object types.
 *
 * For array management of pointers to owned memory-allocated objects
 * requiring automatic garbage collection, please see PArray structure.
 */
template <typename T>
struct Array : public std::vector<T>
{
public:

    /**
     * \brief Structure constructor.
     */
    Array ();


    /**
     * \brief Structure constructor variant.
     *
     * Initializes array object with a predefined number of items.
     *
     * \param size - number of items to set up to array object.
     */
    explicit Array (const ArraySize& size);


    /**
     * \brief Structure destructor.
     */
    virtual ~Array ();


    /**
     * \brief Gets current array index.
     *
     * \return current array index.
     */
    virtual ArrayIndex getIndex () const;


    /**
     * \brief Gets maximum permitted index value.
     *
     * Gets maximum allowed index value for current array size.
     *
     * \return max array index value.
     */
    virtual ArrayIndex getIndexMax () const;


    /**
     * \brief Adds a given quantity to current index.
     *
     * Adds a signed quantity to current array index without bounds
     * control.
     *
     * \param qty - quantity value to add to current array index.
     */
    virtual void indexAdd (const int qty);


    /**
     * \brief Gets object referenced by current index.
     *
     * Gets an object reference pointed to by current array index.
     *
     * Throws std::out_of_range exception if index is out of array
     * bounds.
     *
     * \return object reference.
     */
    virtual T& indexedItem ();


    /**
     * \brief Gets a constant object referenced by current index.
     *
     * Gets a constant (read-only) object reference pointed to by
     * current array index.
     *
     * Throws std::out_of_range exception if index is out of array
     * bounds.
     *
     * \return constant object reference.
     */
    virtual const T& indexedItem () const;


    /**
     * \brief Ensures current index remains in array bounds.
     *
     * Ensures current array index will keep between array bounds
     * through mathematical modulation.
     */
    virtual void modulateIndex ();


    /**
     * \brief Sets current index with bounds control.
     *
     * Sets current array index value with array bounds control.
     *
     * Actually assigned value will never be over than max allowed
     * array index value.
     *
     * \param index - new array index value to set up.
     */
    virtual void setBoundIndex (const ArrayIndex& index);


    /**
     * \brief Sets current index without bounds control.
     *
     * Sets current array index value without array bounds control.
     *
     * \param index - new array index value to set up.
     */
    virtual void setIndex (const ArrayIndex& index);

protected:

    ArrayIndex  m_array_index;

};


/**
 * \brief Template structure for pointers array management.
 *
 * This structure extends Array structure to essentially add automatic
 * garbage collection support.
 *
 * It is optimized for pointers to owned memory-allocated objects that
 * generally need to be garbage collected automatically by the array
 * itself.
 *
 * For array management of generic object types or reference-only
 * pointers to object types, please see Array structure.
 */
template <typename T>
struct PArray : public Array<T>
{
public:

    /**
     * \brief Structure constructor.
     */
    PArray ();


    /**
     * \brief Structure constructor variant.
     *
     * Initializes array object with a predefined number of items.
     *
     * \param size - number of items to set up to array object.
     */
    explicit PArray (const ArraySize& size);


    /**
     * \brief Structure destructor.
     *
     * Also deletes all objects pointed-to by pointers in array.
     *
     * Garbage collection support.
     */
    virtual ~PArray ();


    /**
     * \brief Clears array contents with garbage collection support.
     *
     * Clears array contents and also deletes all objects pointed-to by
     * pointers in array.
     *
     * Garbage collection support.
     */
    virtual void clear ();
};


/*
 * template classes need on-board implementation to work correctly.
 */
#include "array.cpp"


#endif /* _ARRAY_HPP */
