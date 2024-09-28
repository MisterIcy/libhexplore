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

#include <gtest/gtest.h>
#include <libhexplore/io/IO.hpp>
#include <fstream>

TEST(IO, OpenWhenFileExists) {
    libhexplore::io::IO io;
    // Create a file
    std::string file = "open-when-file-exists.txt";
    std::string fileContent = "Hello, World!";
    std::fstream fs(file, std::ios::out);
    fs.write(fileContent.c_str(), fileContent.size());
    fs.close();

    // Open the file
    EXPECT_TRUE(io.open(file));
    EXPECT_TRUE(io.isOpen());

    // Delete the file
    std::remove(file.c_str());
}

TEST(IO, OpenWhenFileIsAlreadyOpened) {
    libhexplore::io::IO io;
    // Create a file
    std::string file = "open-when-file-is-already-opened.txt";
    std::string contents = "Hello, World!";
    std::fstream fs(file, std::ios::out);
    fs.write(contents.c_str(), contents.size());
    fs.close();

    // Open the file
    EXPECT_TRUE(io.open(file));
    EXPECT_TRUE(io.isOpen());
    // Try to open the file again
    EXPECT_FALSE(io.open(file));
    EXPECT_EQ(io.getLastError(), 1);

    // Delete the file
    std::remove(file.c_str());    
}

TEST(IO, OpenFileWhenFileDoesNotExist) {
    libhexplore::io::IO io;
    // Try to open a file that does not exist
    EXPECT_FALSE(io.open("non_existent_file.txt"));
    EXPECT_EQ(io.getLastError(), 2);
}

TEST(IO, IOErrorIsSetToNoneAfterInitialization) {
    libhexplore::io::IO io;
    EXPECT_EQ(io.getLastError(), 0);
}

TEST(IO, ReadFile) {
    libhexplore::io::IO io;
    
    // Create a file
    std::string file = "read-file.txt";
    std::string contents = "Read this file!";
    std::fstream fs(file, std::ios::out);
    fs.write(contents.c_str(), contents.size());
    fs.close();

    // Open the file
    EXPECT_TRUE(io.open(file));
    char* buffer = nullptr;
    bool result = io.read(buffer, contents.size());    
    EXPECT_EQ(io.getLastError(), 0);
    EXPECT_TRUE(result);
    EXPECT_STREQ(buffer, contents.c_str());

    // Delete the file
    std::remove(file.c_str());
}

TEST(IO, ReadFileWhenNotOpen) {
    libhexplore::io::IO io;
    char* buffer = nullptr;
    EXPECT_FALSE(io.read(buffer, 0));
    EXPECT_EQ(io.getLastError(), 3);
}

TEST(IO, ReadFileWhenPointerIsAllocated) {
    libhexplore::io::IO io;
    // Create a file
    std::string file = "read-file-when-pointer-is-allocated.txt";
    std::string contents = "Read this file!";
    std::fstream fs(file, std::ios::out);
    fs.write(contents.c_str(), contents.size());
    fs.close();

    // Open the file
    EXPECT_TRUE(io.open(file));
    char* buffer = (char*)std::malloc(sizeof(char) * contents.size() + 1);
    EXPECT_FALSE(io.read(buffer, contents.size()));
    EXPECT_EQ(io.getLastError(), 4);

    // Delete the file
    std::remove(file.c_str());
}

TEST(IO, ReadFileWhenBufferIsLargerThanFile) {
    libhexplore::io::IO io;
    // Create a file
    std::string file = "read-file-when-buffer-is-larger-than-file.txt";
    std::string contents = "Read this file!";
    std::fstream fs(file, std::ios::out);
    fs.write(contents.c_str(), contents.size());
    fs.close();

    // Open the file
    EXPECT_TRUE(io.open(file));
    char* buffer = nullptr;
    EXPECT_FALSE(io.read(buffer, contents.size() + 1));
    EXPECT_EQ(io.getLastError(), 6);

    // Delete the file
    std::remove(file.c_str());
}