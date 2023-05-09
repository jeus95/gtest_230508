// 7_비기능테스트3.cpp

#include <iostream>
#include <string>

#define DECLARE_GTEST_LEAK_TEST()         \
    static int allocCount;                \
                                          \
    void* operator new(size_t size)       \
    {                                     \
        ++allocCount;                     \
        return malloc(size);              \
    }                                     \
                                          \
    void operator delete(void* p, size_t) \
    {                                     \
        --allocCount;                     \
        free(p);                          \
    }

#define IMPLEMENTS_GTEST_LEAK_TEST(classname) \
    int classname::allocCount = 0

class Image {
    std::string url;

public:
    Image(const std::string& s)
        : url(s)
    {
    }

    void Draw() const
    {
        std::cout << "Draw Image " << url << std::endl;
    }

    //------
    DECLARE_GTEST_LEAK_TEST();
};

IMPLEMENTS_GTEST_LEAK_TEST(Image);

bool DrawImage(const std::string& url)
{
    Image* image = new Image(url);
    image->Draw();

    // ....
    delete image;

    return true;
}

//-----
#include <gtest/gtest.h>

// 1. 메모리 누수 체크를 TestSuite 클래스를 통해 처리합니다.
// 2. 제품 코드의 메모리 관련 코드가 테스트 코드에서만 동작하도록 조건부 컴파일을 적용합니다.

class ImageTest : public testing::Test {
protected:
    int current;

    void SetUp() override
    {
        current = Image::allocCount;
    }

    void TearDown() override
    {
        int diff = Image::allocCount - current;
        EXPECT_EQ(diff, 0) << diff << " object(s) leaks";
    }
};

TEST_F(ImageTest, DrawImage)
{
    EXPECT_TRUE(DrawImage("https://a.com/a.jpg"));
}