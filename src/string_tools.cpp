/*
 * string_tools.cpp
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

#include "string_tools.hpp"

#include "debug.hpp"


namespace StringTools
{

const std::string
format (const std::string& format, ...)
{
    DEBUG_FUNCTION_ENTER;

    std::string buffer;

    if (!format.empty ())
    {
        std::va_list args;

        va_start (args, format);

        const std::size_t size =
            1 + vsnprintf (nullptr, 0, format.c_str (), args);

        buffer.resize (size);

        va_start (args, format);

        vsnprintf (&buffer[0], size, format.c_str (), args);

        va_end (args);
    }

    DEBUG_FUNCTION_EXIT;

    return buffer;
}

} /* namespace */


namespace Utf8
{

/*
 * HINT:
 *
 * (c & 0xc0) == 0xc0 --> UTF-8 code point start char
 *
 * (c & 0xc0) == 0x80 --> UTF-8 code point component char (after start)
 *
 * (c & 0xc0) != 0x80 --> ASCII char or UTF-8 code point start char
 *
 * 0xc0 == 11000000b
 * 0x80 == 10000000b
 *
 * UTF-8 structure (more detail on wikipedia):
 *
 * 0 xxxxxxx                                ASCII [0x00-0x7F]
 * 1 10 xxxxx, 10 xxxxxx                    UTF-8 (start + 1 component)
 * 11 10 xxxx, 10 xxxxxx, 10 xxxxxx         UTF-8 (start + 2 components)
 * 111 10 xxx, 10 xxxxxx, 10 xxxxxx, 10 xxxxxx    (start + 3 components)
 *
 * UTF-8 code point varies from 1 to 4 bytes long.
 *
 * Notice: ASCII chars are considered UTF-8 U+0000 to U+007F
 *
 *         --> UTF-8 code point on 1 byte
 *
 */


#define UTF8_PARTS(c)   (((c) & 0xc0) == 0x80)
#define UTF8_START(c)   (((c) & 0xc0) != 0x80)


const std::string
copy (const std::string& source, const std::size_t& utf8_count)
{
    DEBUG_FUNCTION_ENTER;

    std::string destination;

    copy (destination, source, utf8_count);

    DEBUG_FUNCTION_EXIT;

    return destination;
}


std::size_t
copy (
        std::string& destination,
        const std::string& source,
        std::size_t utf8_count
    )
{
    DEBUG_FUNCTION_ENTER;

    std::size_t bytes = 0;

    destination.clear ();

    if (!source.empty () && utf8_count)
    {
        for (const char c: source)
        {
            if (c && (utf8_count || UTF8_PARTS (c)))
            {
                destination += c;

                bytes++;

                if (UTF8_START (c))
                {
                    utf8_count--;
                }
            }
            else
            {
                break;
            }
        }
    }

    DEBUG_FUNCTION_EXIT;

    return bytes;
}


std::size_t
length (const std::string& string)
{
    DEBUG_FUNCTION_ENTER;

    std::size_t count = 0;

    for (const char& c: string)
    {
        if (UTF8_START (c))
        {
            count++;
        }
    }

    DEBUG_FUNCTION_EXIT;

    return count;
}


std::size_t
popLast (std::string& string)
{
    DEBUG_FUNCTION_ENTER;

    std::size_t bytes = 0;

    while (!string.empty ())
    {
        const char c = string.back ();
        string.pop_back ();
        bytes++;

        if (UTF8_START (c)) break;
    }

    DEBUG_FUNCTION_EXIT;

    return bytes;
}

} /* namespace */

