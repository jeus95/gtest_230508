// 3_테스트픽스쳐3.cpp

// SUT(System Under Test, 테스트 대상 시스템)
//  - CUT(Class Under Test / Code Under Test)
class Calc {
public:
    Calc(int n) { }

    double Display() { return 0.0; }

    void Enter(double n) { }
    void PressPlus() { }
    void PressMinus() { }
    void PressEquals() { }
};
//-----
#include <gtest/gtest.h>

// 2. Test Fixture를 설치하는 방법 3가지
//  3) Implicit Set Up(암묵적 설치)
//   => xUnit Test Framework이 제공하는 기능입니다.
//   => 여러 테스트케이스에서 같은 테스트 픽스쳐 설치의 코드를 암묵적으로 호출되는
//      함수를 통해서 처리합니다.
//    > 명시적인 테스트 스위트 클래스를 정의해야 합니다.
#define SPEC(msg) printf(msg "\n")

class CalcTest : public testing::Test {
protected:
    Calc* calc = nullptr;

    void SetUp() override
    {
        std::cout << "SetUp" << std::endl;
        calc = new Calc(0);
    }
};

TEST_F(CalcTest, PressPlus)
{
    SPEC("2 더하기 2를 하였을 때, 결과가 4가 나오지는 여부를 검증합니다.");

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

TEST_F(CalcTest, PressPlus2)
{
    SPEC("2 더하기 2를 하였을 때, 결과가 4가 나오지는 여부를 검증합니다.");

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