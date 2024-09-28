/**
 * libhexplore - Tools related to the game Hexplore.
 * Copyright (C) 2024 Alexandros Koutroulis
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef __LIBHEXPLORE_LIBHEXPLORE_HPP__
#define __LIBHEXPLORE_LIBHEXPLORE_HPP__

#if defined(_MSC_VER)
    #if defined(LIBHEXPLORE_EXPORTS)
        #define LIBHEXPLORE_EXPORT __declspec(dllexport)
    #else
        #define LIBHEXPLORE_EXPORT __declspec(dllimport)
    #endif
#elif defined(__GNUC__)
    #if defined(LIBHEXPLORE_EXPORTS)
        #define LIBHEXPLORE_EXPORT __attribute__((visibility("default")))
    #else
        #define LIBHEXPLORE_EXPORT
    #endif
#endif
#endif