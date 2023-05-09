// 9_테스트전용하위클래스.cpp

class User {
    int age = 10;

protected: // !!!
    int GetAge() const { return age; }

public:
    void NextYear() { age += 1; }
};

#include <gtest/gtest.h>

// 문제점: 테스트에서 확인하고자 하는 상태가 protected 입니다.
// 해결 방법
// => 테스트 전용 하위 클래스 패턴(Test Specific Subclass Pattern)
// 의도: SUT가 클래스에 테스트를 위한 기능을 제공하고 있지 않으면
//      SUT를 상속하는 하위 클래스를 만들어서 테스트 되지 않은 요구사항을 검증할 수
//      있습니다.
// 장점
//  - 제품 코드를 변경하지 않고, 테스트를 수행할 수 있습니다.

class TestUser : public User {
public:
    int GetAge() const { return User::GetAge(); }
};

TEST(UserTest, NextYear)
{
    TestUser user;
    user.NextYear();

    EXPECT_EQ(user.GetAge(), 11);
}