// 1_시작2.cpp
#include <gtest/gtest.h>

// 1. Google Test에서 테스트케이스를 만드는 방법
// => TEST(테스트스위트 이름, 테스트케이스 이름)

// 2. 테스트스위트
//   - 테스트케이스
//   - 테스트케이스
//   - 테스트케이스

// ImageTest.ResizeImage
TEST(ImageTest, ResizeImage) { }

// ImageTest.BlurImage
TEST(ImageTest, BlurImage)
{
    // 작성 중인 테스트는 명시적으로 실패해야 합니다.
    //  > 실패의 이유를 작성해주어야 합니다.
    FAIL() << "작성 중입니다.";
}