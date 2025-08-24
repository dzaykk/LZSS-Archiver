#include <gtest/gtest.h>
#include "../project/lzss.h"
#include <fstream>

TEST(LZSS, SimpleCompression) {
    std::ofstream("input.txt") << "hello hello hello lalala i love m";

    LZSS lzss;
    lzss.compress("input.txt", "compressed.lzss");
    lzss.decompress("compressed.lzss", "output.txt");

    std::ifstream in1("input.txt", std::ios::binary);
    std::ifstream in2("output.txt", std::ios::binary);

    std::string s1((std::istreambuf_iterator<char>(in1)), {});
    std::string s2((std::istreambuf_iterator<char>(in2)), {});

    EXPECT_EQ(s1, s2);
}