// User.h
#ifndef USER_H
#define USER_H

#include <gtest/gtest.h>

class User {
    int age = 10;

    int GetAge() const { return age; }

public:
    void NextYear() { age += 1; }

    FRIEND_TEST(UserTest, NextYear);
};

#endif