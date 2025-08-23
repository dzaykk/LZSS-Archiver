#include <iostream>
#include <fstream>
#include "lzss.h"

std::streamsize getFileSize(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary | std::ios::ate);
    if (!in) return -1;
    return in.tellg();
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: ./LZSS-Archiver [compress|decompress] input output\n";
        return 1;
    }

    std::string mode = argv[1];
    std::string input = argv[2];
    std::string output = argv[3];

    LZSS lzss;

    if (mode == "compress") {
        std::streamsize inputSize = getFileSize(input);
        if (inputSize < 0) {
            std::cout << "Error: could not open input file.\n";
            return 1;
        }

        std::cout << "Compressing file " << input << "...\n";
        lzss.compress(input, output);

        std::streamsize outputSize = getFileSize(output);
        if (outputSize < 0) {
            std::cout << "Error: could not create output file.\n";
            return 1;
        }

        double ratio = 100.0 - (100.0 * outputSize / inputSize);
        std::cout << "Compression complete! Original size: " << inputSize
            << " bytes, compressed size: " << outputSize
            << " bytes, savings: " << ratio << "%\n";

    }
    else if (mode == "decompress") {
        std::cout << "Decompressing file " << input << "...\n";
        lzss.decompress(input, output);
        std::cout << "Decompression complete! Output file: " << output << "\n";

    }
    else {
        std::cout << "Unknown mode: " << mode << "\n";
        return 1;
    }

    return 0;
}