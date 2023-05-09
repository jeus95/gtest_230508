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

// 8. 테스트 결과 포맷터(Test Result Formatter)
// : 테스트의 결과를 XML 형식으로 출력할 수 있습니다.
// $ ./a.out --gtest_output=xml|json

// GoogleTest 1.10 이후: JSON 지원이 추가되었습니다.

// 9. test result formatter의 결과에 추가적인 정보도 기록할 수 있습니다.
// => RecordProperty(key, value)

#define SPEC(msg)                    \
    do {                             \
        printf("<SPEC> " msg "\n");  \
        RecordProperty("spec", msg); \
    } while (0)

TEST(ImageProcessorTest, ResizeImage)
{
    SPEC("이미지 프로세서에서 이미지 리사이즈 했을 때를 검증한다.");

    RecordProperty("cpu", 30);
    RecordProperty("mem", 10000);
}