// 11_테스트리스너2.cpp

#include <iostream>
#include <string>

#define GTEST_LEAK_TEST

#ifdef GTEST_LEAK_TEST
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

#else
#define DECLARE_GTEST_LEAK_TEST()
#define IMPLEMENTS_GTEST_LEAK_TEST(classname)
#endif

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

    // new Image("a.com");
    // new Image("a.com");
    // new Image("a.com");

    // ....
    // delete image;

    return true;
}

//-----
#include <gtest/gtest.h>

TEST(ImageTest, DrawImage)
{
    EXPECT_TRUE(DrawImage("https://a.com/a.jpg"));
}

class LeakChecker : public testing::EmptyTestEventListener {
    int current;

public:
    void OnTestStart(const testing::TestInfo& /*test_info*/) override
    {
#ifdef GTEST_LEAK_TEST
        current = Image::allocCount;
#endif
    }

    void OnTestEnd(const testing::TestInfo& /*test_info*/) override
    {
#ifdef GTEST_LEAK_TEST
        int diff = Image::allocCount - current;
        EXPECT_EQ(diff, 0) << diff << " object(s) leaks";
#endif
    }
};

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    bool check_for_leaks = false;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--check_for_leaks") == 0) {
            check_for_leaks = true;
            break;
        }
    }

    if (check_for_leaks) {
        testing::UnitTest::GetInstance()->listeners().Append(new LeakChecker);
    }

    return RUN_ALL_TESTS();
}