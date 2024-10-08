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

#ifndef __LIBHEXPLORE_IO_STANDARDIO_HPP__
#define __LIBHEXPLORE_IO_STANDARDIO_HPP__

#include "IOWrapper.hpp"
#include <stdio.h>


namespace libhexplore::io {
/**
 * @class StandardIO StandardIO.hpp
 * @brief An implementation of Standard I/O
 * @see    libhexplore::io::IOWrapper
 * @author Alexandros Koutroulis <icyd3mon@gmail.com>
 * @version 0.1.0
 * @license GPL-2.0-only
 */
class LIBHEXPLORE_EXPORT StandardIO : public IOWrapper {
    public:
        StandardIO() : IOWrapper() {
            this->fp = nullptr;
        }
        ~StandardIO();
        int close() override;
        bool eof() override;
        int hasError() override;
        int flush() override;
        int getPosition(fpos_t* position) override;
        bool open(const std::string filename, const std::string mode) override;
        size_t read(void* pointer, const size_t size, const size_t numElements) override;
        int seek(const long int offset, const int whence) override;
        int setPosition(const fpos_t *position) override;
        long int tell() override;
        size_t write(const void* pointer, const size_t size, const size_t numElements) override;
        void rewindFile() override;
    private:
        FILE* fp;
};
}
#endif 
