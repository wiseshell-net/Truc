/*
 * string_tools.hpp
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

#ifndef _STRING_TOOLS_HPP
#define _STRING_TOOLS_HPP

/**
 * \file
 * \brief Generic string management utility tools.
 *
 * This header file declares generic string management utility tools.
 *
 * \author Raphaël Seban <<raphael.seban@laposte.net>>
 */

#include <cstdarg>
#include <cstddef>
#include <string>

/**
 * \brief Generic string management utility tools namespace.
 */
namespace StringTools
{

    /**
     * \brief Gets a formatted std::string the same way as C function
     * printf(format, ...).
     *
     * \param format - format string as in C function printf().
     * \param ...    - additional arguments as in C function printf().
     *
     * \return formatted std::string object.
     *
     * \see https://en.cppreference.com/w/cpp/io/c/fprintf
     */
    const std::string format (const std::string& format, ...);

} /* namespace */


/**
 * \brief UTF-8 string management utility tools namespace.
 */
namespace Utf8
{

    /**
     * \brief Copies a given number of actual UTF-8 glyphs (not bytes)
     * from a source string.
     *
     * \param source     - source string to copy from.
     * \param utf8_count - number of actual UTF-8 glyphs to copy out.
     *
     * \return well-formed UTF-8 string copy.
     */
    const std::string copy (
        const std::string& source,
        const std::size_t& utf8_count
    );


    /**
     * \brief Copies a given number of actual UTF-8 glyphs (not bytes)
     * from a given source string to a given destination string.
     *
     * \param destination - destination string to copy to.
     * \param source      - source string to copy from.
     * \param utf8_count  - number of actual UTF-8 glyphs to copy out.
     *
     * \return number of actually copied bytes (not glyphs).
     */
    std::size_t copy (
        std::string& destination,
        const std::string& source,
        std::size_t utf8_count
    );


    /**
     * \brief Gets length count of a given string in actual UTF-8
     * glyphs (not bytes).
     *
     * \param string - string to count in.
     *
     * \return number of actual UTF-8 glyphs (not bytes) in string.
     */
    std::size_t length (const std::string& string);


    /**
     * \brief Removes (pops) last actual UTF-8 glyph (not byte) from
     * given string.
     *
     * \param string - string to operate on.
     *
     * \return number of actual bytes (not glyphs) removed from string.
     */
    std::size_t popLast (std::string& string);

} /* namespace */


#endif /* _STRING_TOOLS_HPP */
