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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#include <fstream>
#include <gtest/gtest.h>
#include <libhexplore/io/StandardIO.hpp>

TEST(StandardIO, CloseWhenFileIsClosed) {
  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  ASSERT_EQ(-1, io->close());
}

TEST(StandardIO, CloseWhenFileIsOpened) {
  std::string fileName = "CloseWhenFileIsOpened";
  std::string text = "foo!";
  std::fstream fs;
  fs.open(fileName, std::ios::binary | std::ios::out);
  fs.write(text.c_str(), text.length());
  fs.close();

  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  io->open(fileName, "rb");
  ASSERT_EQ(0, io->close());

  std::remove(fileName.c_str());
}

TEST(StandardIO, IsEofWhenFileClosed) {
  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  ASSERT_FALSE(io->eof()); 
}

TEST(StandardIO, IsEofWhenFileNotEof) {
  std::string fileName = "IsEofWhenFileNotEof";
  std::string text = "foo!";
  std::fstream fs;
  fs.open(fileName, std::ios::binary | std::ios::out);
  fs.write(text.c_str(), text.length());
  fs.close();

  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  io->open(fileName, "rb");
  ASSERT_FALSE(io->eof());

  std::remove(fileName.c_str());
}

TEST(StandardIO, IsEofWhenFileEof) {
  std::string fileName = "IsEofWhenFileEof";
  std::string text = "foo!";
  std::fstream fs;
  fs.open(fileName, std::ios::binary | std::ios::out);
  fs.write(text.c_str(), text.length());
  fs.close();

  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  io->open(fileName, "rb");
  
  char buffer[5];
  io->read(buffer, 1, 5);
  
  ASSERT_TRUE(io->eof());

  std::remove(fileName.c_str());
}

TEST(StandardIO, HasErrorWhenFileClosed) {
  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  ASSERT_EQ(-1, io->hasError()); 
}

TEST(StandardIO, HasErrorWhenFileOpen) {
  std::string fileName = "HasErrorWhenFileOpen";
  std::string text = "foo!";
  std::fstream fs;
  fs.open(fileName, std::ios::binary | std::ios::out);
  fs.write(text.c_str(), text.length());
  fs.close();

  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  io->open(fileName, "rb");
  ASSERT_EQ(0, io->hasError());

  std::remove(fileName.c_str());
}


/**
 * TODO: Find a way to trigger the error
 */
TEST(StandardIO, HasErrorWhenFileErrored) {
  GTEST_SKIP();
}

TEST(StandardIO, FlushWhenFileNotOpen) {
  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  ASSERT_EQ(-1, io->flush()); 
}

TEST(StandardIO, FlushWhenFileOpen) {
  std::string fileName = "FlushWhenFileOpen";
  std::string text = "foo!";
  std::fstream fs;
  fs.open(fileName, std::ios::binary | std::ios::out);
  fs.write(text.c_str(), text.length());
  fs.close();

  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  io->open(fileName, "rb");
  
  char buffer[5] = {'B', 'A', 'R', '!', 0};
  io->write(buffer, 1, 5);
  
  ASSERT_EQ(0, io->flush());

  std::remove(fileName.c_str());
}

TEST(StandardIO, GetPositionWhenFileIsNotOpen) {
  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  fpos_t pos;
  ASSERT_EQ(-1, io->getPosition(&pos));
}

TEST(StandardIO, GetPositionWhenFileIsOpen) {
  std::string fileName = "GetPositionWhenFileIsOpen";
  std::string text = "foo!";
  std::fstream fs;
  fs.open(fileName, std::ios::binary | std::ios::out);
  fs.write(text.c_str(), text.length());
  fs.close();

  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  io->open(fileName, "rb");
  io->seek(1, SEEK_SET);
  
  fpos_t position;
  ASSERT_EQ(0, io->getPosition(&position));
  ASSERT_EQ(1, position.__pos);

  std::remove(fileName.c_str());
}

TEST(StandardIO, OpenWhenFileIsOpened) {
  std::string fileName = "OpenWhenFileIsOpened";
  std::string text = "foo!";
  std::fstream fs;
  fs.open(fileName, std::ios::binary | std::ios::out);
  fs.write(text.c_str(), text.length());
  fs.close();

  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  io->open(fileName, "rb");
  ASSERT_FALSE(io->open(fileName, "rb"));

  std::remove(fileName.c_str());
}

TEST(StandardIO, OpenWhenFileIsNotOpen) {
  std::string fileName = "OpenWhenFileIsOpened";
  std::string text = "foo!";
  std::fstream fs;
  fs.open(fileName, std::ios::binary | std::ios::out);
  fs.write(text.c_str(), text.length());
  fs.close();

  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  ASSERT_TRUE(io->open(fileName, "rb"));

  std::remove(fileName.c_str());
}

TEST(StandardIO, ReadFileWhenNotOpen) {
  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  char c;
  ASSERT_EQ(-1, io->read(&c, 1, 1));
}

TEST(StandardIO, ReadFileWhenOpen) {
  std::string fileName = "ReadFileWhenOpen";
  std::string text = "foo!";
  std::fstream fs;
  fs.open(fileName, std::ios::binary | std::ios::out);
  fs.write(text.c_str(), text.length());
  fs.close();

  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  io->open(fileName, "rb");
  char data[4] = {0,0,0,0};

  ASSERT_EQ(3, io->read(data,1,3));
  ASSERT_STREQ("foo", data);

  std::remove(fileName.c_str());
}

TEST(StandardIO, TestSetPositionWhenFileIsClosed) {
  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  fpos_t position;
  ASSERT_EQ(-1, io->setPosition(&position)); 
}

TEST(StandardIO, TestSetPositionWhenFileIsOpen) {
  std::string fileName = "TestSetPositionWhenFileIsOpen";
  std::string text = "foo!";
  std::fstream fs;
  fs.open(fileName, std::ios::binary | std::ios::out);
  fs.write(text.c_str(), text.length());
  fs.close();

  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  io->open(fileName, "rb");
  io->seek(2, SEEK_SET);
  fpos_t position;
  io->getPosition(&position);

  io->seek(0, SEEK_SET);
  char temp;
  io->read(&temp, 1,1);
  ASSERT_EQ('f', temp);

  ASSERT_EQ(0, io->setPosition(&position));
  io->read(&temp, 1,1);
  ASSERT_EQ('o', temp);

  std::remove(fileName.c_str());
}

TEST(StandardIO, TestTellWhenFileIsClosed) {
  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  ASSERT_EQ(-1, io->tell()); 
}

TEST(StandardIO, TellWhenFileIsOpen) {
  std::string fileName = "TellWhenFileIsOpen";
  std::string text = "foo!";
  std::fstream fs;
  fs.open(fileName, std::ios::binary | std::ios::out);
  fs.write(text.c_str(), text.length());
  fs.close();

  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  io->open(fileName, "rb");
  io->seek(2, SEEK_SET);
  ASSERT_EQ(2, io->tell());

  std::remove(fileName.c_str());
}

TEST(StandardIO, WriteWhenFileIsNotOpen) {
  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  char buffer[4] = {'B', 'a', 'r', '\0'};
  ASSERT_EQ(-1, io->write(buffer, 1, 4)); 
}

TEST(StandardIO, WriteWhenFileIsOpen) {
  std::string fileName = "WriteWhenFileIsOpen";
  std::string text = "foo!";
  std::fstream fs;
  fs.open(fileName, std::ios::binary | std::ios::out);
  fs.write(text.c_str(), text.length());
  fs.close();

  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  io->open(fileName, "wb");
  char buffer[4] = {'B', 'a', 'r', '\0'};
  ASSERT_EQ(3, io->write(buffer, 1, 3));
  io->close();
  io->open(fileName, "rb");
  io->seek(0, SEEK_SET);
  char buffer2[4] = {0,0,0,0};
  ASSERT_EQ(3, io->read(buffer2, 1, 3));
  ASSERT_STREQ("Bar", buffer2);

  std::remove(fileName.c_str());
}

TEST(StandardIO, SeekWhenFileIsNotOpen) {
  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  ASSERT_EQ(-1, io->seek(0, SEEK_SET)); 
}

TEST(StandardIO, SeekWhenFileIsOpen) {
  std::string fileName = "SeekWhenFileIsOpen";
  std::string text = "foo!";
  std::fstream fs;
  fs.open(fileName, std::ios::binary | std::ios::out);
  fs.write(text.c_str(), text.length());
  fs.close();

  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  io->open(fileName, "rb");
  io->seek(2, SEEK_SET);
  char buffer;
  ASSERT_EQ(1, io->read(&buffer, 1, 1));
  ASSERT_EQ('o', buffer);

  std::remove(fileName.c_str());
}


TEST(StandardIO, RewindWhenFileIsOpen) {
std::string fileName = "RewindWhenFileIsOpen";
  std::string text = "foo!";
  std::fstream fs;
  fs.open(fileName, std::ios::binary | std::ios::out);
  fs.write(text.c_str(), text.length());
  fs.close();

  libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
  io->open(fileName, "rb");
  io->seek(2, SEEK_SET);
  ASSERT_EQ(2, io->tell());
  io->rewindFile();
  ASSERT_EQ(0, io->tell());
  
  std::remove(fileName.c_str());
}