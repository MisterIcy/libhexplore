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
#include <libhexplore/StringTable.hpp>
#include <libhexplore/io/StandardIO.hpp>

TEST(StringTable, ReadFile) {
    libhexplore::io::StandardIO *io = new libhexplore::io::StandardIO();
    libhexplore::StringTable *st = new libhexplore::StringTable(io);
    int result = st->load("/home/akoutroulis/Downloads/Hexplore.v1.0.GOG.PROPER-SiMPLEX/common/Gbtxt.st1");
    ASSERT_EQ(1, result);
}