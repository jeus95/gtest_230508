// 3_테스트픽스쳐2.cpp

// SUT(System Under Test, 테스트 대상 시스템)
//  - CUT(Class Under Test / Code Under Test)
#if 0
class Calc {
public:
    // Calc(int n) { }

    double Display() { return 0.0; }

    void Enter(double n) { }
    void PressPlus() { }
    void PressMinus() { }
    void PressEquals() { }
};
//-----
#include <gtest/gtest.h>

// 2. Test Fixture를 설치하는 방법 3가지
//  2) Delegate Set Up(위임 설치)
//  > 픽스쳐 설치에 관한 코드를 별도의 "테스트 유틸리티 함수"를 통해 캡슐화합니다.

#define SPEC(msg) printf(msg "\n")

TEST(CalcTest, PressPlus)
{
    SPEC("2 더하기 2를 하였을 때, 결과가 4가 나오지는 여부를 검증합니다.");
    // Arrange
    Calc* calc = new Calc;

    // Act
    calc->Enter(2);
    calc->PressPlus();
    calc->Enter(2);
    calc->PressEquals();

    // Assert
    if (calc->Display() == 4) {
        SUCCEED();
    } else {
        FAIL() << "2+2 하였을 때, 기대한 결과와 다릅니다.";
    }
}

TEST(CalcTest, PressPlus2)
{
    SPEC("2 더하기 2를 하였을 때, 결과가 4가 나오지는 여부를 검증합니다.");
    // Arrange
    Calc* calc = new Calc;

    // Act
    calc->Enter(2);
    calc->PressPlus();
    calc->Enter(2);
    calc->PressEquals();

    // Assert
    // => xUnit 테스트 프레임워크가 제공하는 단언문을 이용해야 합니다.
    // ASSERT_EQ / NE / LT / LE / GT / GE / TRUE / FALSE ...
    ASSERT_EQ(calc->Display(), 4) << "2+2 하였을 때";
}
#endif

//--------
// g++ -E 3_테스트픽스쳐2.cpp -I ./googletest/googletest/include/
#include <gtest/gtest.h>

//              testing::Test
//                     |
//      -----------------------------
//      |                           |
// SampleTest_foo_Test      SampleTest_goo_Test

// TEST(SampleTest, foo) { }
// class SampleTest_foo_Test : public ::testing::Test {};

// TEST(SampleTest, goo) { }
// class SampleTest_goo_Test : public ::testing::Test {};

//------------------------------------
// 명시적인 Test Suite 클래스를 제공합니다.
// => 테스트 유틸리티 함수를 정의하기 위해서

//              testing::Test
//                     |
//                 SampleTest   <-- Test Suite Class
//                     |
//      -----------------------------
//      |                           |
// SampleTest_foo_Test      SampleTest_goo_Test

class SampleTest : public testing::Test { };

// class SampleTest_foo_Test : public SampleTest
TEST_F(SampleTest, foo) { }

// class SampleTest_goo_Test : public SampleTest
TEST_F(SampleTest, goo) { }