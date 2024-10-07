# String Table (.st1)

Hexplore stores all game strings in the **XXtxt.st1** file located under the directory _common_. The first two characters of the file name, also define the Game's Language (Gb for English).

## Encrytion

The file is encrypted. Decryption takes place when the game is first loading. The decryption algorithm is the following:

```c
// Buffer contains the encrypted data
char* buffer;

char key = 0x37; // Set the initial key
int i = 0; // Set the counter 
while (i < size) { // While there is data in the buffer
    char temp = buffer[i] ^ key; // XOR the current character with the key
    key = key + buffer[i] + 0x33; // Add 0x33, the current character, and the key to key
    buffer[i] = temp; // Store the decrypted character
    i++; // Increment the counter
}
```

## Header 

The file contains a header which is the following

| Field      | Size | Position | Description                                                                                                                                                                                      |
|------------|------|----------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| magic      | 4    | 0x00     | Magic Number (`BTXT`)                                                                                                                                                                            |
| unknown    | 4    | 0x04     | Always 0x100, probably the version of the file                                                                                                                                                   |
| nEntries   | 4    | 0x08     | Number of strings that exist in the file                                                                                                                                                         |
| addrIndex  | 4    | 0x0C     | The starting address of the index section. The index section contains all string IDs in `uint32_t` format and it has always `nEntries records                                                    |
| addrStrLoc | 4    | 0x10     | The starting address of the string location section. It contains `nEntries` elements, each of which point to the address where the string identified by its id found in the index section starts |
| addrStrSec | 4    | 0x14     | The starting address of the string section which contains the actual strings                                                                                                                     |
| addrExtra  | 4    | 0x18     | The starting address of the extra data location                                                                                                                                                  |

```c
typedef struct {
  int magic;
  int unknown;
  int nEntries;
  int addrIdx;
  int addrStrLoc;
  int addrStrSec;
  int addrExtra;
} StringTableHeader;
```

## String Entry

When Hexplore requires a string it will load it by ID. The function responsible for returning the string, will actually return a `StringEntry` structure like the following:

```c
typedef struct {
  char* string;   // Pointer to the actual string
  int unknown1;   // Unknown extra data
  int unknown2;   // Unknown extra data
} StringEntry;
```
