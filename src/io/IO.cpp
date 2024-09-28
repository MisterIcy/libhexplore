#include <libhexplore/io/IO.hpp>

namespace libhexplore::io {
    IO::IO() {
    }

    IO::~IO() {
        if (this->stream.is_open()) {
            this->stream.close();
        }
    }

    int IO::open(std::string file) {
        this->stream.open(file, std::ios::in | std::ios::out | std::ios::binary);
        if (this->stream.is_open()) {
            this->fileName = file;
            return 0;
        }

        return -1;
    }

    void IO::close() {
        if (this->stream.is_open()) {
            this->stream.close();
        }
    }

    bool IO::isOpen() {
        return this->stream.is_open();
    }

    
}