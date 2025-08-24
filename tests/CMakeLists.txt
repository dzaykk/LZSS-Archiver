add_executable(lzss_tests LZSS_Tests.cpp)
target_link_libraries(lzss_tests PRIVATE gtest_main lzss)

include(GoogleTest)
gtest_discover_tests(lzss_tests)