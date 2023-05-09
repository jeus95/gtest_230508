// 11_테스트리스너
// - 구글 테스트가 제공하는 기능입니다.
// => 모든 테스트의 과정에 수행해야 하는 작업을 정의할 수 있습니다.

#include <gtest/gtest.h>

TEST(SampleTest, foo) { }
TEST(SampleTest, goo) { }

// 1. testing::TestEventListener의 인터페이스를 구현해야 합니다.
// => testing::EmptyTestEventListener

// class MyTestEventListener : public testing::TestEventListener { };

using namespace testing;

class MyTestEventListener : public testing::EmptyTestEventListener {
public:
    void OnTestProgramStart(const UnitTest& /*unit_test*/) override { }
    void OnTestIterationStart(const UnitTest& /*unit_test*/,
        int /*iteration*/) override { }
    void OnEnvironmentsSetUpStart(const UnitTest& /*unit_test*/) override { }
    void OnEnvironmentsSetUpEnd(const UnitTest& /*unit_test*/) override { }
    void OnTestSuiteStart(const TestSuite& /*test_suite*/) override { }

    void OnTestStart(const TestInfo& /*test_info*/) override
    {
    }
    void OnTestDisabled(const TestInfo& /*test_info*/) override { }
    void OnTestPartResult(const TestPartResult& /*test_part_result*/) override { }
    void OnTestEnd(const TestInfo& /*test_info*/) override { }
    void OnTestSuiteEnd(const TestSuite& /*test_suite*/) override { }

    void OnEnvironmentsTearDownStart(const UnitTest& /*unit_test*/) override
    {
    }
    void OnEnvironmentsTearDownEnd(const UnitTest& /*unit_test*/) override { }
    void OnTestIterationEnd(const UnitTest& /*unit_test*/,
        int /*iteration*/) override { }
    void OnTestProgramEnd(const UnitTest& /*unit_test*/) override { }
};

// 2. 이벤트 리스너를 등록하는 방법
// > main 함수를 통해서 등록하면 됩니다.
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::TestEventListeners& listenerns = UnitTest::GetInstance()->listeners();
    listenerns.Append(new MyTestEventListener);

    return RUN_ALL_TESTS();
}