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
}