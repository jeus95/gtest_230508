// 6_GoogleTest.cpp
//  1) Fixture
//  2) Assertion

#include <gtest/gtest.h>

int foo() { return 4; }
int goo() { return 1; }

// 1. ASSERT_XXX
//  > 단언문이 실패할 경우, 이후의 코드를 수행하지 않습니다.
//  - 하나의 테스트케이스 안에 여러개의 단언문이 존재할 경우,
//    이후의 단언문이 수행되지 않는 문제가 발생할 수 있습니다.
//    "죽은 단언문"
//    - 하나의 테스트케이스 안에 여러 개의 단언문을 두지 말자.
//    > "중복된 테스트케이스" 문제
//  해결 방법(Google Test)
//   - 새로운 단언문을 제공합니다.
//     EXPECT_XXX
//     > 단언문이 실패할 경우, 테스트의 결과는 실패합니다.
//       이후의 코드를 계속 수행합니다.
TEST(SampleTest, Sample1)
{
    int actualFoo = foo();
    int actualGoo = goo();

    ASSERT_EQ(actualFoo, 42);
    ASSERT_EQ(actualGoo, 100);
}

TEST(SampleTest, Sample2)
{
    int actualFoo = foo();
    int actualGoo = goo();

    EXPECT_EQ(actualFoo, 42);
    EXPECT_EQ(actualGoo, 100);
}

class User {
    std::string name = "Tom";
    int age = 42;

public:
    std::string GetName() const { return name; }
    int GetAge() const { return age; }
};

// User* GetUser() { return new User(); }
User* GetUser() { return nullptr; }

TEST(SampleTest, Sample3)
{
    User* user = GetUser();

    ASSERT_NE(user, nullptr); // 사전 조건 단언문
    EXPECT_EQ(user->GetName(), "Tom");
    EXPECT_EQ(user->GetAge(), 42);
}

// 2. 문자열 비교 단언문
//  : C의 문자열을 비교할 때 사용됩니다.
//    char[] / const char*
//    - EXPECT_STREQ / STRNE
//    - EXPECT_STRCASEEQ / STRCASENE - 대소문자 무시
TEST(SampleTest2, Sample)
{
    std::string s1 = "hello";
    std::string s2 = "hello";
    EXPECT_EQ(s1, s2);

    const char* s3 = "Hello";
    char s4[] = "hello";
    // EXPECT_EQ(s3, s4); // X
    // EXPECT_STREQ(s3, s4);
    EXPECT_STRCASEEQ(s3, s4);
}

// 3. 부동 소수점 비교 단언문
//  - EXPECT_FLOAT_EQ / NE
//    EXPECT_DOUBLE_EQ / NE

//  - EXPECT_NEAR
//    > 오차 범위를 직접 정의할 수 있습니다.

TEST(SampleTest3, Sample)
{
    double a = 0.7;
    double b = 0.1 * 7;

    // EXPECT_EQ(a, b); // X
    EXPECT_DOUBLE_EQ(a, b);
    EXPECT_NEAR(a, b, 0.00000000001);
}

// 4. 예외 검증 단언문
// -     EXPECT_THROW: 기대한 예외 발생 여부
// - EXPECT_ANY_THROW: 예외 발생 여부
// -  EXPECT_NO_THROW: 예외가 발생하지 않음을 검증합니다.
void OpenFile(const std::string& filename)
{
    if (filename.empty()) {
        // throw 1;
        // throw std::invalid_argument("invalid filename");
    }

    // ...
}

TEST(SampleTest4, OpenFile2)
{
    std::string emptyFilename = "";

    EXPECT_THROW(OpenFile(emptyFilename), std::invalid_argument);
}

// 빈 파일명이 전달되었을 때, invalid_argument 예외가 발생하는지 여부를
// 검증하고 싶습니다.
TEST(SampleTest4, OpenFile)
{
    std::string emptyFilename = "";

    try {
        OpenFile(emptyFilename);
        FAIL() << "예외가 발생하지 않음.";
    } catch (std::invalid_argument& e) {
        SUCCEED();
    } catch (...) {
        FAIL() << "다른 종류의 예외가 발생하였음.";
    }
}

// junit4: @Ignore -> junit5: @Disabled

// 5. 테스트 비활성화
// 1) 테스트가 유지보수의 대상일 경우, 명시적으로 실패해야 합니다.
// 2) 테스트를 비활성화하기 위해서, 주석 처리 하면 안됩니다.
//   "잊혀진 테스트"
// 3) 유지보수중인 테스트를 실행하지 않는 기능이 필요합니다.
//    테스트의 결과에 포함되지는 않지만, 존재함을 알릴 수 있어야 합니다.
// 4) Google Test에서는 테스트 스위트 이름 또는 테스트 케이스의 이름이
//    DISABLED_ 시작하면, 비활성화됩니다.
// 5) 비활성화된 테스트를 구동할 수 있는 기능도 제공합니다.
//   $ ./a.out --gtest_also_run_disabled_tests

TEST(ImageProcessorTest, DISABLED_BlurImage)
{
    // 작성 중입니다.
    FAIL() << "작성 중입니다.";
}

class DISABLED_ImageTest : public testing::Test { };

TEST_F(DISABLED_ImageTest, foo) { }
TEST_F(DISABLED_ImageTest, goo) { }
TEST_F(DISABLED_ImageTest, hoo) { }
