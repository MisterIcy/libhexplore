# Hexplore Sound Files

## Soundbanks (.sbk)

Hexplore uses two sound bank files (.sbk), one for music (_musbank.sbk_) and another for other samples (_smpbank.sbk). The structure of the files is as follows:

### Header

| Field           | Size | Position | Description                       |
|-----------------|------|----------|-----------------------------------|
| containsSamples | 4    | 0x00     | Always 1                          |
| numberOfEntries | 4    | 0x04     | The number of samples in the file |

From `0xC` it contains `numberOfEntries` entries, which indicate where an entry starts. For example, in the _musbank.sbk_ file, the value at `0xc` is `0x34` stating that the first sample begins there.

At the starting position of each sample, there's a 12-byte `WAVEFORMATEX` structure, that identifies the sound format of the file. There are another 4 bytes (need to be investigated) and then the sound data begin. The sound data are in PCM format (ready to be played in DirectX) and its format adhere to the `WAVEFORMATEX` structure.

## The SMP.BIN files

Accompanying the sound banks, there are some _xxxsmp.bin_ files (e.g. musicsmp.bin) which contain additional information regarding how the sounds are to be played. Their structure is the following:

```c
typedef struct 
{
    int minFrequency;
    int maxFrequency;
    int sampleId;
    char volume;
    char volumeMod;
    char pan;
    char panMod;
} SbkBin;
```

