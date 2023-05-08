// 2_3A.cpp

// SUT(System Under Test, 테스트 대상 시스템)
//  - CUT(Class Under Test / Code Under Test)
class Calc {
public:
    double Display() { return 0.0; }

    void Enter(double n) { }
    void PressPlus() { }
    void PressMinus() { }
    void PressEquals() { }
};
//-----
#include <gtest/gtest.h>

// 1. TestCase를 구성하는 방법
//  => Test Suite 이름
//   > 테스트 대상 클래스(모듈)의 이름의 마지막에
//     Test / Spec 접미를 붙이는 형태로 많이 사용합니다.

// 2. 3A
//  1) Arrange: 테스트 대상 코드를 초기화하고, 필요한 경우 설정하고 준비합니다.
//  2)     Act: 테스트 대상 코드에 작용을 가합니다.
//  3)  Assert: 기대하는 바를 단언합니다.

// CalcTest / CalcSpec
TEST(CalcTest, PressPlus)
{
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
        FAIL();
    }
}