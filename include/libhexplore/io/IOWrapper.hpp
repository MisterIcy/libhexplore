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

#ifndef __LIBHEXPLORE_IO_IOWRAPPER_HPP__
#define __LIBHEXPLORE_IO_IOWRAPPER_HPP__

#include <libhexplore/libhexplore.hpp>
#include <string>

#define IO_ERROR_NONE 0 // No error occured
#define IO_ERROR_ALREADY_OPEN 1 // A file is already open
#define IO_ERROR_OPEN_FAILED 2 // Failed to open a file
#define IO_ERROR_FILE_NOT_OPEN 3 // No file is currently open
#define IO_ERROR_BUFFER_ALREADY_ALLOCATED 4 // A buffer is already allocated
#define IO_ERROR_BUFFER_ALLOC_FAILED 5 // Failed to allocate a buffer
#define IO_ERROR_READ_FAILED 6 // Failed to read from a file

namespace libhexplore::io {
    /**
     * @interface IOWrapper IOWrapper.hpp
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
             * Default Constructor.
             */
            IOWrapper() {}

            /**
             * Default Destructor.
             */
            virtual ~IOWrapper() {}
            /**
             * Opens a file both for reading and for writing.
             * 
             * @param [in] file The path to the file to open.
             * @return `true` if the file was opened successfully, `false` otherwise. To get the 
             *         error code use `getLastError()`.
             * @see    getLastError()
             */
            virtual bool open(std::string file) = 0;

            /**
             * Checks if the file is open.
             * 
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

            /**
             * Reads data from the file.
             * 
             * @param [out] buffer A pointer to a buffer that will hold the data read from the file.
             *                     The buffer must not be allocated before calling this function; it will
             *                     be allocated by the function. The buffer must be deallocated by the caller.
             * @param [in] size    The size of the buffer to allocate.
             * @return `true` if the data was read successfully, `false` otherwise. To get the error code
             *         use `getLastError()`.             
             */
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