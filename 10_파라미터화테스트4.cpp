// 10_파라미터화테스트4.cpp
#include <gtest/gtest.h>

class StringTest : public testing::TestWithParam<std::string> { };

// 1. testing::Values
#if 0
INSTANTIATE_TEST_SUITE_P(StringValues, StringTest,
    testing::Values("hello", "world", "show", "me"));
#endif

std::vector<std::string> data = { "hello", "world", "show", "me" };
// std::string data[] = { "hello", "world", "show", "me" };

std::vector<std::string> LoadFromFile()
{
    std::vector<std::string> data = { "hello", "world", "show", "me" };
    // ...
    return data;
}

// 2. testing::ValuesIn
#if 0
INSTANTIATE_TEST_SUITE_P(StringValues, StringTest,
    testing::ValuesIn(data));
#endif
INSTANTIATE_TEST_SUITE_P(StringValues, StringTest,
    testing::ValuesIn(LoadFromFile()));

TEST_P(StringTest, Sample)
{
    std::cout << GetParam() << std::endl;
}