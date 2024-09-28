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

#include <libhexplore/io/IO.hpp>

namespace libhexplore::io {
    bool IO::open(std::string file) {
        if (stream.is_open()) {
            this->setLastError(IO_ERROR_ALREADY_OPEN);
            return false;
        }

        stream.open(file, std::ios::in | std::ios::out | std::ios::binary);
        
        if (!stream.is_open()) {
            this->setLastError(IO_ERROR_OPEN_FAILED);
            return false;
        }

        this->fileName = file;
        this->clearLastError();
        return true;
    }

    bool IO::isOpen() {
        return this->stream.is_open();
    }

    void IO::close() {
        if (this->stream.is_open()) {
            stream.close();
            this->clearLastError();
        }
    }

    bool IO::read(char*& buffer, std::size_t size) {
        if (this->isOpen() == false)  {
            this->setLastError(IO_ERROR_FILE_NOT_OPEN);
            return false;
        }

        if (buffer != nullptr) {
            this->setLastError(IO_ERROR_BUFFER_ALREADY_ALLOCATED);
            return false;
        }

        buffer = (char*)std::malloc(sizeof(char) * size + 1);

        if (buffer == nullptr) {
            this->setLastError(IO_ERROR_BUFFER_ALLOC_FAILED);
            return false;
        }

        std::memset(buffer, 0, size + 1);

        this->stream.seekg(0, std::ios::beg);
        this->stream.read(buffer, size);

        if ((size_t)this->stream.gcount() != size) {
            this->setLastError(IO_ERROR_READ_FAILED);
            return false;
        }

        this->clearLastError();

        return true;
    }
}
