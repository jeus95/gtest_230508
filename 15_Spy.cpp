// 15_Spy.cpp
#include <string>
#include <vector>

enum Level {
    INFO,
    WARN,
    ERROR
};

class DLoggerTarget {
public:
    virtual ~DLoggerTarget() { }

    virtual void Write(Level level, const std::string& message) = 0;
};

// 파일에 로그를 기록합니다.
class FileTarget : public DLoggerTarget { };

// TCP로 로그를 전송합니다.
class TCPTarget : public DLoggerTarget { };

class DLogger {
    std::vector<DLoggerTarget*> targets;

public:
    void AddTarget(DLoggerTarget* p) { targets.push_back(p); }

    void Write(Level level, const std::string& message)
    {
        for (auto e : targets) {
            e->Write(level, message);
        }
    }
};

#include <gtest/gtest.h>
#include <algorithm>

// Test Spy Pattern
// 의도: SUT의 함수를 호출하였을 때, 발생하는 부수효과를 관찰할 수 없어서
//      테스트 되지 않은 요구사항이 존재합니다.
// 방법: 목격한 일을 기록해두었다가 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역
//     "다른 컴포넌트로부터의 간접 출력"을 저장해두었다가, 검증에 사용합니다.

class SpyTarget : public DLoggerTarget {
    std::vector<std::string> history;

    std::string concat(Level level, const std::string& message) const
    {
        static std::string levels[] = { "I", "W", "E" };
        return levels[level] + "@" + message;
    }

public:
    void Write(Level level, const std::string& message) override
    {
        // 목격한 일을 기록합니다.
        history.push_back(concat(level, message));
    }

    // 테스트에서 활용하는 기능
    bool IsReceived(Level level, const std::string& message) const
    {
        return std::find(begin(history), end(history),
                   concat(level, message))
            != end(history);
    }
};

// DLogger에 대해서 Write하였을 때, 등록된 타겟에 Write가 제대로 전달되었는지 여부를 검증합니다.
TEST(DLoggerTest, Write)
{
    DLogger logger;
    SpyTarget spy1, spy2;
    logger.AddTarget(&spy1);
    logger.AddTarget(&spy2);
    Level test_level = INFO;
    std::string test_message = "test logging message";

    logger.Write(test_level, test_message);

    EXPECT_TRUE(spy1.IsReceived(test_level, test_message));
    EXPECT_TRUE(spy2.IsReceived(test_level, test_message));
}