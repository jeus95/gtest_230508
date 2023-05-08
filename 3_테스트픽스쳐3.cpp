// 3_테스트픽스쳐3.cpp
#include <iostream>

// SUT(System Under Test, 테스트 대상 시스템)
//  - CUT(Class Under Test / Code Under Test)
class Calc {
public:
    Calc(int n) { }
    ~Calc() { std::cout << "~Calc()" << std::endl; }

    double Display() { return 0.0; }

    void Enter(double n) { }
    void PressPlus() { }
    void PressMinus() { }
    void PressEquals() { }
};
//-----
#include <gtest/gtest.h>

// 2. Test Fixture를 설치하는 방법 3가지
//  3) Implicit Set Up / Tear Down(암묵적 설치/해체)
//   => xUnit Test Framework이 제공하는 기능입니다.
//   => 여러 테스트케이스에서 같은 테스트 픽스쳐 설치의 코드를 암묵적으로 호출되는
//      함수를 통해서 처리합니다.
//    > 명시적인 테스트 스위트 클래스를 정의해야 합니다.
//  장점: 테스트 코드 중복을 제거하고, 불필요한 준비 과정을 제거할 수 있습니다.
//  단점: 픽스쳐 설치 코드가 테스트 케이스 외부에 존재하기 때문에
//       테스트 케이스만으로 테스트 코드를 분석하기 어려울 수 있다.

// 3. xUnit Test Framework
//  => 4단계 테스트 패턴(Four Phase Test Pattern)
//  : xUnit Test Pattern에서 테스트 케이스를 구성하는 방법.
// 1단계: 테스트 픽스쳐를 설치하거나, 실제 결과를 관찰하기 위해서 필요한 것을
//       설정합니다. => SetUp()
// 2단계: SUT와 상호 작용합니다. => TestBody()
// 3단계: 기대 결과를 확인합니다. => TestBody()
// 4단계: 테스트 픽스쳐를 해체해서, 테스트 시작 이전의 상태로 돌려놓습니다.
//       => TearDown()

#define SPEC(msg) printf(msg "\n")

class CalcTest : public testing::Test {
protected:
    Calc* calc = nullptr;

    void SetUp() override
    {
        std::cout << "SetUp" << std::endl;
        calc = new Calc(0);
    }

    void TearDown() override
    {
        std::cout << "TearDown" << std::endl;
        delete calc; // !!!
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

    // 이전의 단언문이 실패할 경우, 이후의 코드가 수행되지 않습니다.
    // delete calc;
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

    // delete calc;
}