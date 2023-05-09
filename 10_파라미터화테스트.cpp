// 10_파라미터화테스트.cpp

bool IsPrime(int value)
{
    for (int i = 2; i < value; ++i) {
        if (value % i == 0) {
            return false;
        }
    }

    return true;
}

#include <gtest/gtest.h>

TEST(PrimeTest, IsPrime)
{
    EXPECT_TRUE(IsPrime(2));
}

TEST(PrimeTest, IsPrime2)
{
    EXPECT_TRUE(IsPrime(3));
}

TEST(PrimeTest, IsPrime3)
{
    int data[] = { 2, 3, 5, 7, 11, 13, 15, 17, 23, 29, 31 };
    for (int e : data) {
        EXPECT_TRUE(IsPrime(e)) << "e: " << e;
    }
}
