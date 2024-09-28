#include <gtest/gtest.h>
#include <libhexplore/io/IO.hpp>
#include <fstream>

TEST(IO, OpenWhenFileExists) {
    libhexplore::io::IO io;
    // Create a file
    std::string file = "test.txt";
    std::fstream fs(file, std::ios::out);
    fs.write("Hello, World!", 13);
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
    std::string file = "test.txt";
    std::fstream fs(file, std::ios::out);
    fs.write("Hello, World!", 13);
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