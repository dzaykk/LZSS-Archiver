#include "lzss.h"
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>

int LZSS::findLongestMatch(const char* window, int windowStart,
    const char* buffer, int bufferSize, int& matchOffset)
{
    int bestLength = 0;
    int bestOffset = 0;

    for (int i = 0; i < WINDOW_SIZE; ++i) {
        int length = 0;
        while (length < bufferSize &&
            window[(windowStart + i + length) % WINDOW_SIZE] == buffer[length]) {
            ++length;
        }
        if (length > bestLength) {
            bestLength = length;
            bestOffset = i;
        }
    }

    matchOffset = bestOffset;
    return bestLength;
}

void LZSS::compress(const std::string& inputFile, const std::string& outputFile)
{
    std::ifstream in(inputFile, std::ios::binary);
    std::ofstream out(outputFile, std::ios::binary);
    if (!in || !out) return;

    char window[WINDOW_SIZE] = { 0 };
    char buffer[BUFFER_SIZE];
    int windowStart = 0;
    int bufferSize = 0;

    in.read(buffer, BUFFER_SIZE);
    bufferSize = static_cast<int>(in.gcount());

    while (bufferSize > 0) {
        int matchOffset = 0;
        int matchLength = findLongestMatch(window, windowStart, buffer, bufferSize, matchOffset);

        const int MAX_MATCH = MIN_MATCH_LENGTH + 15;
        if (matchLength > MAX_MATCH) matchLength = MAX_MATCH;

        if (matchLength >= MIN_MATCH_LENGTH) {
            out.put(static_cast<char>(1));
            unsigned char b1 = static_cast<unsigned char>(matchOffset >> 4);
            unsigned char b2 = static_cast<unsigned char>(((matchOffset & 0x0F) << 4) |
                (matchLength - MIN_MATCH_LENGTH));
            out.put(static_cast<char>(b1));
            out.put(static_cast<char>(b2));

            for (int i = 0; i < matchLength; ++i) {
                window[(windowStart + i) % WINDOW_SIZE] = buffer[i];
            }
            windowStart = (windowStart + matchLength) % WINDOW_SIZE;

            std::memmove(buffer, buffer + matchLength, static_cast<size_t>(bufferSize - matchLength));
            in.read(buffer + (bufferSize - matchLength), matchLength);
            int readBytes = static_cast<int>(in.gcount());
            bufferSize = bufferSize - matchLength + readBytes;
        }
        else {
            out.put(static_cast<char>(0));
            out.put(buffer[0]);

            window[windowStart] = buffer[0];
            windowStart = (windowStart + 1) % WINDOW_SIZE;

            std::memmove(buffer, buffer + 1, static_cast<size_t>(bufferSize - 1));
            in.read(buffer + (bufferSize - 1), 1);
            int readBytes = static_cast<int>(in.gcount());
            bufferSize = bufferSize - 1 + readBytes;
        }
    }
}

void LZSS::decompress(const std::string& inputFile, const std::string& outputFile)
{
    std::ifstream in(inputFile, std::ios::binary);
    std::ofstream out(outputFile, std::ios::binary);
    if (!in || !out) return;

    char window[WINDOW_SIZE] = { 0 };
    int windowStart = 0;

    for (;;) {
        int flag = in.get();
        if (flag == EOF) break;

        if (flag == 0) {
            int c = in.get();
            if (c == EOF) break;
            out.put(static_cast<char>(c));
            window[windowStart] = static_cast<char>(c);
            windowStart = (windowStart + 1) % WINDOW_SIZE;
        }
        else {
            int byte1 = in.get();
            int byte2 = in.get();
            if (byte1 == EOF || byte2 == EOF) break;

            int offset = ((byte1 & 0xFF) << 4) | ((byte2 & 0xF0) >> 4);
            int length = (byte2 & 0x0F) + MIN_MATCH_LENGTH;

            int src = (windowStart + offset) % WINDOW_SIZE;

            for (int i = 0; i < length; ++i) {
                char c = window[(src + i) % WINDOW_SIZE];
                out.put(c);
                window[windowStart] = c;
                windowStart = (windowStart + 1) % WINDOW_SIZE;
            }
        }
    }
}
