// 6_GoogleTest2.cpp
#include <gtest/gtest.h>

// 6. 테스트 필터
// > 원하는 테스트만 선택적으로 수행할 수 있습니다.
// : 테스트의 이름을 잘 구성해야 합니다.
// - P_foo
// - N_foo
// - I_foo

// $ ./a.out --gtest_filter=ImageTest.foo
// $ ./a.out --gtest_filter=ImageTest.foo:ImageProcessorTest.goo
// $ ./a.out --gtest_filter=*.foo
// $ ./a.out --gtest_filter=Image*.*
// $ ./a.out --gtest_filter=Image*.*:-*.goo

// ImageTest.foo
TEST(ImageTest, foo) { }

// ImageTest.goo
TEST(ImageTest, goo) { }

// ImageTest.hoo
TEST(ImageTest, hoo) { }

TEST(ImageProcessorTest, foo) { }
TEST(ImageProcessorTest, goo) { }
TEST(ImageProcessorTest, hoo) { }

//----
// 7. 반복 테스트 / 순서 무작위
//  => "변덕스러운 테스트"를 확인할 수 있습니다.
// $ ./a.out --gtest_repeat=10
// $ ./a.out --gtest_repeat=10 --gtest_shuffle
// $ ./a.out --gtest_repeat=10 --gtest_shuffle --gtest_break_on_failure

int cnt = 0;
int GetCount() { return ++cnt; }

TEST(SampleTest, Sample1)
{
    EXPECT_EQ(GetCount(), 1);
}

TEST(SampleTest, Sample2)
{
    EXPECT_EQ(GetCount(), 2);
    cnt = 0;
}