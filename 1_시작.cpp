// 1_시작.cpp
#include <gtest/gtest.h>

// 아래의 코드는 항상 동일합니다.
// > main 함수를 라이브러리에 포함시켜서 사용하는 경우가 있습니다.
#if 0
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif

// $ g++ 1_시작.cpp -I ./googletest/googletest/include -L. -lgtest -pthread