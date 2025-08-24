# LZSS-Archiver

A simple implementation of the **LZSS compression algorithm** in C++.

## Features
- Compresses and decompresses files using LZSS.
- Works with any binary/text files (not only `.txt`).
- Unit tests with **GoogleTest** are included.

## Build

The project uses **CMake** (C++17).

```bash
git clone https://github.com/dzaykk/LZSS-Archiver.git
cd LZSS-Archiver
cmake -S . -B build
cmake --build build
```

## Usage
```bash
# Compress
./LZSS-Archiver input.txt compressed.lzss

# Decompress
./LZSS-Archiver compressed.lzss output.txt
```

## Tests
GoogleTest is used for unit testing.
```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
cd build
ctest
```
