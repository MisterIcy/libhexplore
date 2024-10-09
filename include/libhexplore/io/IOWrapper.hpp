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

#ifndef __LIBHEXPLORE_IO_IOWRAPPER_HPP__
#define __LIBHEXPLORE_IO_IOWRAPPER_HPP__

#include <libhexplore/libhexplore.hpp>
#include <string>

namespace libhexplore::io {
/**
 * @interface IOWrapper IOWrapper.hpp
 * @brief An interface for file I/O operations.
 * @remark This class provides a common interface for file I/O operations to the
 * other components of the library. The class is abstract; the library user must
 * implement the actual file I/O operations. The library implements a concret
 * class, IO, that uses the standard C++ file I/O operations.
 * @see    libhexplore::io::IO
 * @author Alexandros Koutroulis <icyd3mon@gmail.com>
 * @version 0.1.0
 * @license GPL-2.0-only
 */
class LIBHEXPLORE_EXPORT IOWrapper {
public:
  /**
   * Default Constructor.
   */
  IOWrapper() {}

  /**
   * Default Destructor.
   */
  virtual ~IOWrapper() = default;

  virtual int close() = 0;
  virtual bool eof() = 0;
  virtual int hasError() = 0;
  virtual int flush() = 0;
  virtual int getPosition(fpos_t* position) = 0;
  virtual bool open(const std::string filename, const std::string mode) = 0;
  virtual size_t read(void* pointer, const size_t size, const size_t numElements) = 0;
  virtual int seek(const long int offset, const int whence) = 0;
  virtual int setPosition(const fpos_t *position) = 0;
  virtual long int tell() = 0;
  virtual size_t write(const void* pointer, const size_t size, const size_t numElements) = 0;
  virtual void rewindFile() = 0;

};
} // namespace libhexplore::io
#endif