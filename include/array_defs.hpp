/*
 * array_defs.hpp
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

#ifndef _ARRAY_DEFS_HPP
#define _ARRAY_DEFS_HPP


/**
 * \file
 * \brief Macro defs and typedefs for array management.
 *
 * This header file defines preprocessor macros and typedefs for array
 * management purpose.
 *
 * \author Raphaël SEBAN <<raphael.seban@laposte.net>>
 */

#include <cstddef>


#define ARRAY_SIZE(name)    (sizeof (name) / sizeof (*(name)))


typedef std::size_t ArraySize;
typedef ArraySize   ArrayIndex;


#endif /* _ARRAY_DEFS_HPP */
