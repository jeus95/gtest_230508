// 3_테스트픽스쳐3.cpp

// SUT(System Under Test, 테스트 대상 시스템)
//  - CUT(Class Under Test / Code Under Test)
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