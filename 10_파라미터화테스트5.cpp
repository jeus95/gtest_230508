// 10_파라미터화테스트5.cpp
#include <gtest/gtest.h>

enum Color {
    RED,
    WHITE,
    BLACK
};

std::vector<std::string> cars = {
    "Sonata",
    "Avante",
    "Genesis",
};

int years[] = { 2022, 2023, 2024 };

// Combine을 사용할 때 데이터 타입을 정의하는 방법
using CarType = std::tuple<std::string, Color, int>;

class CarTest : public testing::TestWithParam<CarType> { };

using testing::Combine;
using testing::Values;
using testing::ValuesIn;

INSTANTIATE_TEST_SUITE_P(CarValues, CarTest,
    Combine(
        ValuesIn(cars),
        Values(RED, WHITE, BLACK),
        ValuesIn(years)));

TEST_P(CarTest, Sample)
{
    const CarType& data = GetParam();
    std::cout
        << std::get<0>(data) << ", "
        << std::get<1>(data) << ", "
        << std::get<2>(data) << std::endl;
    FAIL();
}