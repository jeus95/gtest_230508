// 7_비기능테스트.cpp
#include <string>
#include <unistd.h>

// 아래 함수는 1초 안에 수행되어야 합니다.
void Connect(const std::string& url)
{
    sleep(2);
    // ...
}

// 비기능 테스트
// - 기능적인 동작 뿐 아니라 성능이나 메모리 등의 비기능적인 부분을 검증합니다.
#include <gtest/gtest.h>

// 사용자 정의 단언문
#define EXPECT_TIMEOUT(fn, limit)                                                \
    do {                                                                         \
        time_t startTime = time(nullptr);                                        \
        fn;                                                                      \
        time_t duration = time(nullptr) - startTime;                             \
        EXPECT_LE(duration, limit) << "Timeout: " << limit << " second(s) 초과"; \
    } while (0)

TEST(ConnectTest, Connect2)
{
    EXPECT_TIMEOUT(Connect("https://a.com"), 1);
}

TEST(ConnectTest, Connect)
{
    time_t limit = 1;
    time_t startTime = time(nullptr);

    Connect("https://a.com");
    time_t duration = time(nullptr) - startTime;

    EXPECT_LE(duration, limit);
}