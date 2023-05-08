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