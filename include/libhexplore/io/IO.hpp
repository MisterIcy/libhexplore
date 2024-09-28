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

#ifndef __LIBHEXPLORE_IO_IO_HPP__
#define __LIBHEXPLORE_IO_IO_HPP__
#include <cstdint>
#include <cstring>
#include <fstream>
#include <libhexplore/io/IOWrapper.hpp>

namespace libhexplore::io {
/**
 * @class IO IO.hpp
 * @brief A concrete class that implements the IOWrapper interface using the
 * standard C++ file I/O operations.
 * @see    libhexplore::io::IOWrapper
 * @author Alexandros Koutroulis <icyd3mon@gmail.com>
 * @version 0.1.0
 * @license GPL-2.0-only
 */
class LIBHEXPLORE_EXPORT IO : public IOWrapper {
public:
  /**
   * Default Constructor.
   */
  IO() {}
  /**
   * Default Destructor.
   */
  ~IO() override {}

  /**
   * Opens a file both for reading and for writing.
   *
   * @param [in] file The path to the file to open.
   * @return `true` if the file was opened successfully, `false` otherwise. To
   * get the error code use `getLastError()`.
   * @see    getLastError()
   */
  bool open(std::string file) override;

  /**
   * Checks if the file is open.
   *
   * @return `true` if the file is open, `false` otherwise.
   */
  bool isOpen() override;

  /**
   * Closes the file.
   *
   * @remark If the file is not open, the function will do nothing.
   */
  void close() override;

  /**
   * Reads data from the file.
   *
   * @param [out] buffer A pointer to a buffer that will hold the data read from
   * the file. The buffer must not be allocated before calling this function; it
   * will be allocated by the function. The buffer must be deallocated by the
   * caller.
   * @param [in] size    The size of the buffer to allocate.
   * @return `true` if the data was read successfully, `false` otherwise. To get
   * the error code use `getLastError()`.
   */
  virtual bool read(char *&buffer, std::size_t size) override;

private:
  std::fstream stream;
};
} // namespace libhexplore::io

#endif