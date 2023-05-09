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
// 1. Parameterized Test
// > 데이터 셋 정의할 때 사용하는 함수
//  1) testing::Values
//  2) testing::ValuesIn
//  3) testing::Range
//  4) testing::Combine

// 2. 구글테스트에서 테스트 케이스를 만드는 방법 3가지
// 1) TEST
//  > 명시적인 테스트 스위트 클래스가 필요하지 않을 때

// 2) TEST_F
//  > 명시적인 테스트 스위트 클래스
//  class SampleTest : public testing::Test {};
//  TEST_F(SampleTest, foo) {}

// 3) TEST_P
//  > 명시적인 테스트 스위트 클래스 + 파라미터화 테스트
//  class SampleTest : public testing::TestWithParam<InputType> {};
//  INSTANTIATE_TEST_SUITE_P(..); /* 데이터 셋 정의 */
//  TEST_P(SampleTest, foo)
//  { GetParam(); }