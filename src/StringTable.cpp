#include <libhexplore/StringTable.hpp>

namespace libhexplore {
StringTable::StringTable(libhexplore::io::IOWrapper *io) { this->io = io; }

int StringTable::load(std::string file) {
  bool result = this->io->open(file, "rb");
  if (result == false) {
    return -1;
  }

  io->seek(0, SEEK_END);
  size_t fileSize = io->tell();
  io->seek(0, SEEK_SET);

  char *buffer = (char *)malloc(sizeof(char) * fileSize);
  if (buffer == nullptr) {
    throw std::runtime_error("Allocation failed");
  }

  std::memset(buffer, 0, fileSize);
  size_t readBytes = io->read(buffer, 1, fileSize);

  if (readBytes != fileSize) {
    throw std::runtime_error("An error occured while reading the file");
  }

  this->decrypt(buffer, fileSize);
  int* bufferPtr = reinterpret_cast<int*>(buffer);
  this->readHeader(bufferPtr);

  io->close();

  for (uint32_t i = 0; i < this->fileHeader.nEntries; i++) {
    StringEntry *entry = this->extractEntryAt(i, buffer);
    this->entries[i] = entry;
    printf("%s\n", entry->string.c_str());
    if (onStringLoaded) {
      onStringLoaded(*entry);
    }
  }

  if (onFileLoaded) {
    onFileLoaded();
  }

  return 1;
}

StringEntry *StringTable::extractEntryAt(int index, const char *buffer) {
  auto readIntFromBuffer = [](const char *buf, int offset) -> int {
    return *reinterpret_cast<const int *>(buf + offset);
  };

  // Step 1: Read the string ID
  int stringIdOffset = this->fileHeader.addrIdx + index * sizeof(int);
  int stringId = readIntFromBuffer(buffer, stringIdOffset);

  // Step 2: Read the string location
  int stringLocOffset =
      this->fileHeader.addrIdx + (this->fileHeader.nEntries + index) * sizeof(int);
  int stringLoc = readIntFromBuffer(buffer, stringLocOffset);

  // Step 3: Extract the actual string from the buffer
  const char *stringStart = buffer + stringLoc;
  std::string extractedString(
      stringStart); // std::string takes care of memory allocation

  // Step 4: Read the extra data (u1, u2)
  int extraDataOffset = this->fileHeader.addrExtra + index * sizeof(int);
  int u1 = readIntFromBuffer(buffer, extraDataOffset);
  int u2 = readIntFromBuffer(buffer, extraDataOffset + sizeof(int));

  // Step 5: Return the new StringEntry object
  return new StringEntry(stringId, extractedString, u1, u2);
}

void StringTable::decrypt(char *buffer, std::size_t size) {
  char key = 0x37;
  int i = 0;
  while (i < (int)size) {
    char temp = buffer[i] ^ key;
    key = key + buffer[i] + 0x33;
    buffer[i] = temp;
    i++;
  }

  if (onDecrypted) {
    onDecrypted();
  }
}

void StringTable::readHeader(const int* buffer) {
  this->fileHeader.magic = *buffer;
  this->fileHeader.version = *(buffer+1);
  this->fileHeader.nEntries = *(buffer+2);
  this->fileHeader.addrIdx = *(buffer+3);
  this->fileHeader.addrStrLoc = *(buffer+4);
  this->fileHeader.addrStrSec = *(buffer+5);
  this->fileHeader.addrExtra = *(buffer+6);

  if (this->fileHeader.magic != ST1_MAGIC) {
    throw new std::runtime_error("Invalid header signature!");
  }
}

} // namespace libhexplore