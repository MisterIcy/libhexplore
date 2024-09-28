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
        }
    }

    bool IO::read(char* buffer, std::size_t size) {
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

        this->stream.read(buffer, size);
        
        if ((size_t)this->stream.gcount() != size) {
            this->setLastError(IO_ERROR_READ_FAILED);
            return false;
        }

        return true;
    }
}