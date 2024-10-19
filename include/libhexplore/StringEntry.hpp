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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#ifndef __LIBHEXPLORE_STRINGENTRY_HPP__
#define __LIBHEXPLORE_STRINGENTRY_HPP__
#include <libhexplore/libhexplore.hpp>
#include <string>


namespace libhexplore {
/**
 * @class StringEntry StringEntry.hpp
 * @author Alexandros Koutroulis <icyd3mon@gmail.com>
 * @version 0.1.0
 * @license GPL-2.0-only
 */
class LIBHEXPLORE_EXPORT StringEntry {
public:
  int id;
  std::string string;
  int unknown1;
  int unknown2;

  StringEntry(int id, std::string string, int unknown1, int unknown2)
      : id(id), string(string), unknown1(unknown1), unknown2(unknown2) {}
};
} // namespace libhexplore
#endif
