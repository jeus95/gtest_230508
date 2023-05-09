// 10_파라미터화테스트6.cpp
#include <gtest/gtest.h>

class SampleTest : public testing::TestWithParam<int> { };

// 0 - 999
// testing::Range(start, end, step)
//  : [start, end)

INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest,
    testing::Range(0, 1000, 3));

TEST_P(SampleTest, Sample)
{
    std::cout << GetParam() << std::endl;
}