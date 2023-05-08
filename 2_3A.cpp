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

// 3. 테스트케이스 품질
// 1) 가독성: 테스트가 실패하였을 때, 실패의 원인이 실패 메세지를 통해 드러나는가?
//          테스트케이스의 이름을 통해, 테스트의 시나리오를 알수 있는가?
// 2) 유지보수성
//  > 테스트 코드도 유지보수의 대상입니다.
//   "유지보수의 비용이 최소화될 수 있어야 합니다."
//   "오류가 발생할 가능성이 있는 코드를 테스트 케이스 안에서는 지양해야 합니다."
//   - 제어 구문(조건문, 반복문, 예외 처리 등)의 사용을 최소화해야 합니다.

// 3) 신뢰성

#define SPEC(msg) printf(msg "\n")

// TEST(CalcTest, PressPlus_TwoPlusTwo_DisplaysFour)
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
    ASSERT_EQ(calc->Display(), 4) << "2+2 하였을 때";
}