// 16_Mock.cpp
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

// Mock Object Pattern
// 의도: SUT의 함수를 호출하였을 때, 발생하는 부수효과를 관찰할 수 없어서
//      테스트 되지 않은 요구사항이 존재합니다.
// 방법: 행위 기반 검증을 수행합니다.
//   => 모의 객체(행위를 검증하기 위한 테스트 대역)
//      Mock Framework을 이용해야 합니다.
//   C++: Google Mock
//  Java: jMock, EasyMock, Mockito, Spock ...

// 상태 검증
// > 객체에 작용을 가한 후, 단언 함수를 통해 내부 상태값의 변화를 통해 검증을 수행합니다.

// 동작 검증
// > 객체에 작용을 가한 후, 내부적으로 발생하는 함수의 호출 여부, 호출 횟수, 호출 인자, 호출 순서 등을
//   통해 정상 동작 여부를 검증합니다.