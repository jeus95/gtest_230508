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

class MyTestEnvironment2 : public testing::Environment {
public:
    void SetUp() override
    {
        std::cout << "라이브러리2 초기화" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "라이브러리2 정리" << std::endl;
    }
};

TEST(SampleTest, foo) { }
TEST(SampleTest, goo) { }

TEST(ImageTest, Resize) { }
TEST(ImageTest, Blur) { }

// 미정의 동작(Undefined)
TEST(SampleTest, hoo)
{
    int n = 1;
    int r = ++n + ++n; // 미정의 동작, 컴파일러마다 결과가 달라집니다.
    std::cout << r << std::endl;
}

int foo()
{
    std::cout << "foo" << std::endl;
    return 10;
}
int goo()
{
    std::cout << "goo" << std::endl;
    return 20;
}

void hoo(int a, int b) { }

// 미지정 동작(Unspecified)
TEST(SampleTest, koo)
{
    int rf = foo();
    int rg = goo();
    hoo(rf, rg);

    // hoo(foo(), goo()); // 인자로 전달된 함수의 호출 순서가 미지정입니다.
}

// 2) 전역 픽스쳐를 설치하는 방법
//  =>  main을 직접 정의해서 사용하는 것이 좋습니다.

//  1. 전역 변수
//   > 전역 변수의 초기화 순서가 파일별로 순서가 정의되지 않습니다.
//    => C++ 미지정 동작
// a.cpp
testing::Environment* my_env1 = testing::AddGlobalTestEnvironment(new MyTestEnvironment);

// b.cpp
testing::Environment* my_env2 = testing::AddGlobalTestEnvironment(new MyTestEnvironment2);

//  2. main 함수
#if 0
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    // 주의사항: new로 생성해서 전달해야 합니다.
    testing::AddGlobalTestEnvironment(new MyTestEnvironment);
    testing::AddGlobalTestEnvironment(new MyTestEnvironment2);

    return RUN_ALL_TESTS();
}
#endif