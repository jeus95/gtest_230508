// 3_테스트픽스쳐4.cpp
#include <gtest/gtest.h>

class ImageProcessorTest : public testing::Test {
protected:
    ImageProcessorTest() { std::cout << "ImageProcessorTest()" << std::endl; }
    ~ImageProcessorTest() { std::cout << "~ImageProcessorTest()" << std::endl; }

    void SetUp() override { std::cout << "SetUp()" << std::endl; }
    void TearDown() override { std::cout << "TearDown()" << std::endl; }
};

TEST_F(ImageProcessorTest, ResizeImage) { }
TEST_F(ImageProcessorTest, BlurImage) { }

// NUnit
// => "변덕스러운 테스트의 문제가 발생할 가능성이 높았습니다."

// --------
// > 신선한 픽스쳐 전략
//  : 각 테스트 케이스마다 새로운 테스트 스위트 클래스 객체를 생성함으로
//    신선한 픽스쳐를 유지합니다.
//  => 각각의 테스트 케이스를 독립적으로 수행할 수 있도록 도움을 줍니다.

// ts = new ImageProcessorTest;
// ts->SetUp();
// ts->ResizeImage();
// ts->TearDown();
// delete ts;

// ts = new ImageProcessorTest;
// ts->SetUp();
// ts->BlurImage();
// ts->TearDown();
// delete ts;
// -------