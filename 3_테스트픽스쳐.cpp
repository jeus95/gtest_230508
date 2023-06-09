// 3_테스트픽스쳐.cpp

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

// 1. 테스트 픽스쳐(Test Fixture)
// 정의: xUnit Test Framework에서 SUT를 실행하기 위해 준비해야하는 모든 것을
//      테스트 픽스쳐 라고 합니다.
//      테스트 픽스쳐를 구성하는 모든 코드의 로직 부분을 "픽스쳐 설치" 라고 합니다.

// 2. Test Fixture를 설치하는 방법 3가지
//  1) Inline Fixture Set Up
//  : 모든 픽스쳐 설치를 테스트 케이스 안에서 수행합니다.
//  장점: 픽스쳐를 설치하는 과정과 검증의 로직이 하나의 테스트 케이스 함수 안에 존재하기 때문에
//       인과 관계를 분석하기 쉽다.
//  단점: 모든 테스트 코드 안에서 "테스트 코드 중복"이 발생합니다.

// 3. 테스트 냄새
//  정의: 테스트 코드의 가독성 / 유지보수성 / 신뢰성을 떨어뜨리는 요소

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