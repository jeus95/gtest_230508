// 10_파라미터화테스트6.cpp
#include <gtest/gtest.h>

class SampleTest : public testing::TestWithParam<int> {
protected:
    void SetUp() override
    {
        std::cout << "SetUp" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "TearDown" << std::endl;
    }

    static void SetUpTestSuite()
    {
        std::cout << "SetUpTestSuite" << std::endl;
    }

    static void TearDownTestSuite()
    {
        std::cout << "TearDownTestSuite" << std::endl;
    }
};

// 0 - 999
// testing::Range(start, end, step)
//  : [start, end)

INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest,
    testing::Range(0, 100, 3));

TEST_P(SampleTest, Sample)
{
    std::cout << GetParam() << std::endl;
}

// 총정리
// Parameterized Test
// > 데이터 셋 정의할 때 사용하는 함수
//  1) testing::Values
//  2) testing::ValuesIn
//  3) testing::Range
//  4) testing::Combine