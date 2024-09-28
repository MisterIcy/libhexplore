#ifndef __LIBHEXPLORE_IO_IO_HPP__
#define __LIBHEXPLORE_IO_IO_HPP__
#include <libhexplore/io/IOWrapper.hpp>
#include <fstream>

namespace libhexplore::io {
    class LIBHEXPLORE_EXPORT IO : public IOWrapper {
        public:
            IO();
            ~IO();

            virtual int open(std::string file) = 0;
            virtual bool isOpen() = 0;
            virtual void close() = 0;
        private:
            std::fstream stream;
    };
}

#endif