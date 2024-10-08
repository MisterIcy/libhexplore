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

#include <libhexplore/io/StandardIO.hpp>

namespace libhexplore::io {

int StandardIO::close() {
    if (this->fp == nullptr) {
        return -1;
    }

    auto result = fclose(this->fp);
    this->fp = nullptr;

    return result;
}

bool StandardIO::eof() {
    if (this->fp == nullptr) {
        return false;
    }

    return feof(this->fp);
}

int StandardIO::hasError() {
    if (this->fp == nullptr) {
        return -1;
    }

    return ferror(fp);
}

int StandardIO::flush() {
    if (this->fp == nullptr) {
        return -1;
    }

    return fflush(fp);
}

int StandardIO::getPosition(fpos_t* position) {
    if (this->fp == nullptr) {
        return -1;
    }

    return fgetpos(fp, position);
}

bool StandardIO::open(const std::string filename, const std::string mode) {
    if (this->fp != nullptr) {
        return false;
    }

    this->fp = fopen(filename.c_str(), mode.c_str());

    return this->fp != nullptr;
}

size_t StandardIO::read(void* pointer, const size_t size, const size_t numElements) {
    if (this->fp == nullptr) {
        return -1;
    }

    return fread(pointer, size, numElements, this->fp);
}

int StandardIO::setPosition(const fpos_t *position) {
    if (this->fp == nullptr) {
        return -1;
    }

    return fsetpos(this->fp, position);
}

long int StandardIO::tell() {
    if (this->fp == nullptr) {
        return -1;
    }

    return ftell(this->fp);
}

size_t StandardIO::write(const void* pointer, const size_t size, const size_t numElements) {
    if (this->fp == nullptr) {
        return -1;
    }

    return fwrite(pointer, size, numElements, this->fp);
}

int StandardIO::seek(const long int offset, const int whence) {
    if (this->fp == nullptr) {
        return -1;
    }

    return fseek(this->fp, offset, whence);
}

void StandardIO::rewindFile() {
    if (this->fp != nullptr) {
        rewind(this->fp);
    }
}

StandardIO::~StandardIO() {
    this->close();
}

}
