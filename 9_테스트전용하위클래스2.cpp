// 9_테스트전용하위클래스2.cpp

#include <iostream>

class Engine {
public:
    virtual ~Engine() { }

    virtual void Start()
    {
        // ...
        std::cout << "Engine Start" << std::endl;
        // ...
    }
};

class Car {
    Engine* engine;

public:
    Car(Engine* p)
        : engine(p)
    {
    }

    void Go() const
    {
        // ...
        engine->Start();
        // ...
    }
};

//--
#include <gtest/gtest.h>

// Car의 Go가 호출되었을 때, Engine의 Start가 제대로 호출되었는지 여부를 검증하고 싶다.
// 문제점: Engine의 Start가 호출되었는지 여부를 확인할 수 있는 기능을
//       SUT가 제공하지 않아서, 단언문을 작성할 수 없습니다.
// 해결방법: 테스트 전용 하위 클래스 패턴
//       => 가상 함수

class TestEngine : public Engine {
    bool isStart = false;

public:
    void Start() override
    {
        std::cout << "-----" << std::endl;
        // 부모 기능을 호출합니다.
        Engine::Start();
        isStart = true;
        std::cout << "-----" << std::endl;
    }

    // 테스트에서 확인할 수 있는 상태를 제공합니다.
    bool IsStart() const { return isStart; }
};

TEST(CarTest, Go)
{
    TestEngine engine;
    Car car(&engine);

    car.Go();

    EXPECT_TRUE(engine.IsStart()) << "Car가 Go 하였을 때";
}