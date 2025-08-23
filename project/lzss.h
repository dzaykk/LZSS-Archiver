#pragma once
#include <string>

class LZSS {
public:
	void compress(const std::string& InputFile, const std::string& OutputFile);
	void decompress(const std::string& InputFile, const std::string& OutputFile);

private:
	static constexpr int WINDOW_SIZE = 4096;
	static constexpr int BUFFER_SIZE = 18;
	static constexpr int MIN_MATCH_LENGTH = 3;

	int findLongestMatch(const char* window, int windowStart, const char* buffer, int bufferSize, int& matchOffset);
};