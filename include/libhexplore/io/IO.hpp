#ifndef __LIBHEXPLORE_IO_IO_HPP__
#define __LIBHEXPLORE_IO_IO_HPP__
#include <libhexplore/io/IOWrapper.hpp>
#include <fstream>
#include <cstdint>
#include <cstring>

namespace libhexplore::io {
    class LIBHEXPLORE_EXPORT IO : public IOWrapper {
        public:
            IO() {}
            ~IO() override {}
            bool open(std::string file) override;
            bool isOpen() override;
            void close() override;
            virtual bool read(char*& buffer, std::size_t size) override;
    
        private:
            std::fstream stream;
    };
}

#endif