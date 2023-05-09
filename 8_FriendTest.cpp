// 8_FriendTest.cpp

// 절대 사용하면 안됩니다.
// #define class struct
// #define private public
#include "User.h"
// #undef private
// #undef class

#include <gtest/gtest.h>

// NextYear를 호출하였을 때,
// age가 1 증가하는지 여부를 검증하고 싶다.

// 검증되지 않은 private 메소드 보다
// 검증된 public 메소드가 안전합니다.
// > public 메소드를 검증할 때,
//   private 메소드가 같이 검증되어야 합니다.
// > private 메소드는 public 메소드의 가독성을 높이기 위해
//   사용해야 합니다.

// > GoogleTest 는 FriendTest를 이용하면
//   SUT의 private 영역을 검증할 수 있습니다.
//   문제점: 제품 코드에 Google Test 의존성이 생깁니다.

TEST(UserTest, NextYear)
{
    User user;

    user.NextYear();

    EXPECT_EQ(user.GetAge(), 11);
}