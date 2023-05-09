// 13_Stub.cpp
#include <iostream>

class IConnection {
public:
    virtual ~IConnection() { }

    virtual void Move(int x, int y) = 0;
};

class NetworkException : public std::exception {
public:
    const char* what() const noexcept override
    {
        return "Bad Network State";
    }
};

class TCPConnection : public IConnection {
public:
    void Move(int x, int y) override
    {
        // TCP 패킷을 서버로 전송합니다.
    }
};

class Player {
    IConnection* conn;

public:
    Player(IConnection* p)
        : conn(p)
    {
    }

    void Move(int x, int y)
    {
        // ...
        try {
            conn->Move(x, y);
            // ...
        } catch (NetworkException& e) {
            // 네트워크 연결이 끊어졌을 때의 동작
            // ...
            throw e;
        }
        // ...
    }
};

//----
#include <gtest/gtest.h>

// Test Stub Pattern
//  의도: 다른 컴포넌트로부터의 간접 입력에 의존하는 로직을 독립적으로 검증하고 싶다.
//  방법: 실제 의존하는 객체를 테스트 대역으로 교체해서,
//       SUT가 테스트하는데 필요한 결과를 보내도록 제어합니다.

class StubConnection : public IConnection {
public:
    void Move(int x, int y) override
    {
        throw NetworkException();
    }
};

// Player의 Move를 수행하였을 때, 네트워크 예외 발생의 로직에서
// NetworkException이 외부로 전파되는지 여부를 검증하고 싶다.

// 의존성 주입
// > 제품 코드를 사용하는 방식 그대로 테스트를 수행할 수 있습니다.

TEST(PlayerTest, Move)
{
    // TCPConnection conn;
    StubConnection conn;
    Player player(&conn);

    EXPECT_THROW(player.Move(10, 20), NetworkException);
}