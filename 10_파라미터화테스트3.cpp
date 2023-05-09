// 10_파라미터화테스트3.cpp

#include <string>

bool Process(int age, const std::string& name)
{
    // ...
    return true;
}

#include <gtest/gtest.h>

#if 0
using InputType = std::tuple<int, std::string>;

class ProcessTest : public testing::TestWithParam<InputType> { };

INSTANTIATE_TEST_SUITE_P(ProcessValues, ProcessTest,
    testing::Values(
        InputType { 10, "Tom" },
        InputType { 11, "Alice" },
        InputType { 12, "Bob" },
        InputType { 13, "David" }));

TEST_P(ProcessTest, Process)
{
    const InputType& data = GetParam();
    EXPECT_FALSE(Process(std::get<0>(data), std::get<1>(data)));
}
#endif

struct InputType {
    int age;
    std::string name;
};

// 사용자 정의 타입을 Google Test에서 출력할 때
std::ostream& operator<<(std::ostream& os, const InputType& data)
{
    return os << "(age=" << data.age << ", name=" << data.name << ")";
}

class ProcessTest : public testing::TestWithParam<InputType> { };

INSTANTIATE_TEST_SUITE_P(ProcessValues, ProcessTest,
    testing::Values(
        InputType { 10, "Tom" },
        InputType { 11, "Alice" },
        InputType { 12, "Bob" },
        InputType { 13, "David" }));

TEST_P(ProcessTest, Process)
{
    const InputType& data = GetParam();
    EXPECT_FALSE(Process(data.age, data.name));
}