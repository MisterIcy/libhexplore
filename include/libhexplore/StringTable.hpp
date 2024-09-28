#ifndef __LIBHEXPLORE_STRINGTABLE_HPP__
#define __LIBHEXPLORE_STRINGTABLE_HPP__

#include <libhexplore/libhexplore.hpp>
#include <libhexplore/io/IOWrapper.hpp>

namespace libhexplore {
    class LIBHEXPLORE_EXPORT StringTable {
        public:
            StringTable(libhexplore::io::IOWrapper io);
            ~StringTable();
    };
}
#endif