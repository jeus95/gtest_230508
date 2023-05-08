// 5_전역픽스쳐.cpp
// => xUnit Test Framework의 기능이 아닙니다.
// => Google Test 고유의 기능입니다.
// => 프로그램의 시작/종료에서 픽스쳐를 설치하거나 해체하는 기능을 제공합니다.

#include <gtest/gtest.h>

// 전역 픽스쳐를 사용하는 방법
// 1) testing::Environment의 자식 클래스를 정의해서,
//    설치와 해체 코드를 작성합니다.

class MyTestEnvironment : public testing::Environment {
public:
    void SetUp() override
    {
        std::cout << "라이브러리1 초기화" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "라이브러리1 정리" << std::endl;
    }
};

TEST(SampleTest, foo) { }
TEST(SampleTest, goo) { }

TEST(ImageTest, Resize) { }
TEST(ImageTest, Blur) { }

// 2) 전역 픽스쳐를 설치하는 방법
//   1. 전역 변수
testing::Environment* my_env = testing::AddGlobalTestEnvironment(new MyTestEnvironment);

//   2. main 함수
#if 0
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    // 주의사항: new로 생성해서 전달해야 합니다.
    testing::AddGlobalTestEnvironment(new MyTestEnvironment);

    return RUN_ALL_TESTS();
}
#endif