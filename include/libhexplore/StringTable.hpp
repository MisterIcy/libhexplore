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

#ifndef __LIBHEXPLORE_STRINGTABLE_HPP__
#define __LIBHEXPLORE_STRINGTABLE_HPP__

#include <libhexplore/io/IOWrapper.hpp>
#include <libhexplore/libhexplore.hpp>
#include <libhexplore/StringEntry.hpp>
#include <stdexcept>
#include <cstring>
#include <unordered_map>
#include <functional>

/**
 * Magic Number of String Table Header
 */
#define ST1_MAGIC 0x54585442

namespace libhexplore {

typedef struct
{
  uint32_t magic;
  uint32_t version;
  uint32_t nEntries;
  uint32_t addrIdx;
  uint32_t addrStrLoc;
  uint32_t addrStrSec;
  uint32_t addrExtra;
} ST1Header;


/**
 * @class StringTable StringTable.hpp
 * @brief A class that manipulates Hexplore's .st1 files (string tables).
 * @author Alexandros Koutroulis <icyd3mon@gmail.com>
 * @version 0.1.0
 * @license GPL-2.0-only
 */
class LIBHEXPLORE_EXPORT StringTable {
public:
  StringTable(libhexplore::io::IOWrapper *io);
  ~StringTable();

  /**
   * Loads a string table (.st1)
   *
   * @param [in] file The path to the file to load.
   * @return 0 if the file was loaded successfully, a negative error code
   * otherwise.
   */
  int load(std::string file);
  std::function<void()> onFileLoaded;
  std::function<void(const StringEntry&)> onStringLoaded;
  std::function<void()> onDecrypted;


private:
  libhexplore::io::IOWrapper *io;

  /**
   * Decrypts the buffer loaded from the file.
   *
   * @param [in,out] buffer The buffer to decrypt.
   * @param [in] size The size of the buffer.
   * @return 0 if the buffer was decrypted successfully, a negative error code
   * otherwise.
   * @remark The buffer will be decrypted in place.
   * @details Hexplore's .st1 files are encrypted using a stream cipher. The
   * decryption algorithm is as follows:
   *          1. We start with a key of 0x37.
   *          2. We load the first byte of the file and store it in a variable
   *          3. We XOR the key with the byte and store the result back in the
   * buffer
   *          4. We add 0x33 to the key and the unencrypted byte
   *          5. We repeat the process for the rest of the file
   */
  void decrypt(char *buffer, std::size_t size);
  void readHeader(const int* buffer);
  char *buffer = nullptr;
  StringEntry* extractEntryAt(int index, const char *buffer);
  ST1Header fileHeader;
  std::unordered_map<uint32_t, StringEntry*> entries;
};
} // namespace libhexplore
#endif