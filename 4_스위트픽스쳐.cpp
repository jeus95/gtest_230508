// 4_스위트픽스쳐.cpp
#include <string>
#include <unistd.h>

class Terminal {
public:
    // 가정: Connect / Disconnect 느립니다.
    void Connect() { sleep(2); }
    void Disconnect() { sleep(1); }

    void Login(const std::string& id, const std::string& password) { }
    void Logout() { }

    bool IsLogin() { return false; }
};

//------
#include <gtest/gtest.h>

// 문제점
// : SetUp / TearDown이 느려서(픽스쳐의 설치와 해체가 느려서)
//   테스트케이스가 추가될 때마다 전체적인 테스트의 수행 시간이 늘어나는 문제가
//   있습니다.
// => Slow Test 문제
//  1) 테스트가 너무 느려서, 테스트를 수행하는 개발자의 생산성을 떨어뜨립니다.
//  2) 테스트가 너무 느려서, 아무도 코드가 변경되어도 테스트를 수행하지 않습니다.

// 해결 방법
// => Suite Fixture SetUp / TearDown
//  : 테스트 스위트 클래스 객체가 생성되기 전에 호출되고,
//    테스트 스위트 클래스가 파괴된 이후에 수행됩니다.
//    테스트 스위트의 첫번째 테스트가 수행되기 전에 호출되고,
//    테스트 스위트의 마지막 테스트가 수행된 후 호출됩니다.
// => 정적 메소드의 형태로 제공됩니다.

// Suite Fixture
// => "신선한 픽스쳐" 전략이 아닌 "공유 픽스쳐" 전략입니다.
// 문제점: 테스트 스위트 안의 모든 테스트 케이스가 같은 픽스쳐를 공유합니다.
//       각각의 테스트 케이스는 독립적이지 않습니다.
//       성능은 빠르게 동작하지만, 이전의 테스트케이스가 픽스쳐를 망가뜨리면
//       이후의 테스트의 결과를 신뢰할 수 없는 문제가 발생할 가능성이 있습니다.
//       "변덕스러운 테스트"

class TerminalTest : public testing::Test {
protected:
    // Terminal* ts = nullptr;
    static Terminal* ts;

    static void SetUpTestSuite()
    {
        std::cout << "---- SetUpTestSuite ----" << std::endl;
        ts = new Terminal;
        ts->Connect();
    }

    static void TearDownTestSuite()
    {
        std::cout << "---- TearDownTestSuite ----" << std::endl;
        ts->Disconnect();
        delete ts;
    }

    void SetUp() override
    {
        // ts = new Terminal;
        // ts->Connect();
    }

    void TearDown() override
    {
        // ts->Disconnect();
        // delete ts;
    }
};

// !!!
Terminal* TerminalTest::ts = nullptr;

TEST_F(TerminalTest, Login)
{
    ts->Login("test_id", "test_password");

    ASSERT_TRUE(ts->IsLogin()) << "로그인 하였을 때";
}

TEST_F(TerminalTest, Logout)
{
    ts->Login("test_id", "test_password");
    ts->Logout();

    ASSERT_FALSE(ts->IsLogin()) << "로그아웃 하였을 때";
}

TEST_F(TerminalTest, foo) { }
TEST_F(TerminalTest, goo) { }

// 아래의 코드를 암묵적 설치 / 해체를 이용해서 변경해보세요.
#if 0
TEST(TerminalTest, Login)
{
    Terminal* ts = new Terminal;
    ts->Connect();

    ts->Login("test_id", "test_password");

    ASSERT_TRUE(ts->IsLogin()) << "로그인 하였을 때";

    ts->Disconnect();
    delete ts;
}

TEST(TerminalTest, Logout)
{
    Terminal* ts = new Terminal;
    ts->Connect();

    ts->Login("test_id", "test_password");
    ts->Logout();

    ASSERT_FALSE(ts->IsLogin()) << "로그아웃 하였을 때";

    ts->Disconnect();
    delete ts;
}
#endif