#ifndef __LIBHEXPLORE_IO_IOWRAPPER_HPP__
#define __LIBHEXPLORE_IO_IOWRAPPER_HPP__

#include <libhexplore/libhexplore.hpp>
#include <string>

namespace libhexplore::io {
    class LIBHEXPLORE_EXPORT IOWrapper {
        public:
            IOWrapper();
            virtual ~IOWrapper();

            virtual int open(std::string file) = 0;
            virtual bool isOpen() = 0;
            virtual void close() = 0;

        protected:
            std::string fileName;
    };
}
#endif