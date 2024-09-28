#ifndef __LIBHEXPLORE_IO_IOWRAPPER_HPP__
#define __LIBHEXPLORE_IO_IOWRAPPER_HPP__

#include <libhexplore/libhexplore.hpp>
#include <string>

#define IO_ERROR_NONE 0 
#define IO_ERROR_ALREADY_OPEN 1
#define IO_ERROR_OPEN_FAILED 2
#define IO_ERROR_FILE_NOT_OPEN 3
#define IO_ERROR_BUFFER_ALREADY_ALLOCATED 4
#define IO_ERROR_BUFFER_ALLOC_FAILED 5
#define IO_ERROR_READ_FAILED 6


namespace libhexplore::io {
    /**
     * @class IOWrapper
     * @interface
     * 
     * @brief An interface for file I/O operations.
     * @remark This class provides a common interface for file I/O operations to the other
     *         components of the library. The class is abstract; the library user must implement
     *         the actual file I/O operations. 
     *         The library implements a concret class, IO, that uses the standard C++ file I/O
     *         operations.
     * @see    libhexplore::io::IO
     * @author Alexandros Koutroulis <icyd3mon@gmail.com>
     * @version 0.1.0
     * @license GPL-2.0-only
     */
    class LIBHEXPLORE_EXPORT IOWrapper {
        public:
            /**
             * Constructor.
             */
            IOWrapper() {}

            /**
             * Destructor.
             */
            virtual ~IOWrapper() {}
            /**
             * Opens a file for reading and writing.
             * 
             * @param [in] file The file to open.
             * @return `true` if the file was opened successfully, `false` otherwise. To get the 
             *         error code use getLastError().
             * @see    getLastError()
             */
            virtual bool open(std::string file) = 0;

            /**
             * Checks if the file is open.
             * @return `true` if the file is open, `false` otherwise.
             */
            virtual bool isOpen() = 0;

            /**
             * Closes the file.
             * 
             * @remark If the file is not open, the function will do nothing.
             */
            virtual void close() = 0;
            
            /**
             * Returns the last error occured. If no error occured, the function will return IO_ERROR_NONE.
             * 
             * @return The last error code.
             */
            uint8_t getLastError() {
                return this->lastError;
            }

            /**
             * Clears the last error.
             */
            void clearLastError() {
                this->lastError = IO_ERROR_NONE;
            }

            virtual bool read(char*& buffer, size_t size) = 0;

        protected:
            std::string fileName;
            
            /**
             * Sets the last error.
             * 
             * @param [in] error The error code.
             */
            void setLastError(uint8_t error) {
                this->lastError = error;
            }

        private:
            uint8_t lastError = IO_ERROR_NONE;

    };
}
#endif