// 10_파라미터화테스트2.cpp

bool IsPrime(int value)
{
    for (int i = 2; i < value; ++i) {
        if (value % i == 0) {
            return false;
        }
    }

    return true;
}

#include <gtest/gtest.h>

// 파라미터화 테스트 패턴(Parameterized Test Pattern)
// : xUnit Test Framework가 제공하는 기능입니다.
// 의도: 입력 데이터를 바꿔가며, 반복 검사하는 데이터 중심의 테스트에서
//      테스트 코드 중복을 제거할 수 있습니다.

// 1. 명시적인 TestSuite 클래스가 필요합니다.
//         기존) class PrimeTest : public testing::Test
// 파라미터화테스트) class PrimeTest : public testing::TestWithParam<int>

class PrimeTest : public testing::TestWithParam<int> { };

// 2. 데이터 셋을 정의해야 합니다.
//  => 매크로
// INSTANTIATE_TEST_CASE_P  // 1.10 이전
// INSTANTIATE_TEST_SUITE_P // 1.10 이후

// INSTANTIATE_TEST_SUITE_P(데이터셋 접두, 테스트스위트 클래스, 데이터)
INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest,
    testing::Values(2, 3, 5, 7, 11, 13, 15, 22, 17, 23, 31));

// 3. 데이터 셋을 활용하는 테스트 케이스를 작성하면 됩니다.
//         기존) class PrimeTest : public testing::Test
//            => TEST_F

// 파라미터화테스트) class PrimeTest : public testing::TestWithParam<int>
//            => TEST_P
//             GetParam(): 정의된 데이터를 하나씩 가져올 수 있습니다.
TEST_P(PrimeTest, IsPrime)
{
    EXPECT_TRUE(IsPrime(GetParam()));
}