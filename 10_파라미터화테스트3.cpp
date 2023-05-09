// 10_파라미터화테스트3.cpp

#include <string>

bool Process(int age, const std::string& name)
{
    // ...
    return true;
}

#include <gtest/gtest.h>

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