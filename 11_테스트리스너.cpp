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
    void OnTestProgramStart(const UnitTest& /*unit_test*/) override
    {
        std::cout << __func__ << std::endl;
    }
    void OnTestIterationStart(const UnitTest& /*unit_test*/,
        int /*iteration*/) override
    {
        std::cout << __func__ << std::endl;
    }
    void OnEnvironmentsSetUpStart(const UnitTest& /*unit_test*/) override
    {
        std::cout << __func__ << std::endl;
    }
    void OnEnvironmentsSetUpEnd(const UnitTest& /*unit_test*/) override
    {
        std::cout << __func__ << std::endl;
    }
    void OnTestSuiteStart(const TestSuite& /*test_suite*/) override
    {
        std::cout << __func__ << std::endl;
    }

    void OnTestStart(const TestInfo& /*test_info*/) override
    {
        std::cout << __func__ << std::endl;
    }
    void OnTestDisabled(const TestInfo& /*test_info*/) override
    {
        std::cout << __func__ << std::endl;
    }
    void OnTestPartResult(const TestPartResult& /*test_part_result*/) override
    {
        std::cout << __func__ << std::endl;
    }

    void OnTestEnd(const TestInfo& test_info) override
    {
        std::cout << __func__ << std::endl;
        std::cout
            << test_info.test_suite_name() << "." << test_info.name() << " --> "
            << (test_info.result()->Passed() ? "PASS" : "FAIL")
            << std::endl;
    }

    void OnTestSuiteEnd(const TestSuite& /*test_suite*/) override
    {
        std::cout << __func__ << std::endl;
    }

    void OnEnvironmentsTearDownStart(const UnitTest& /*unit_test*/) override
    {
        std::cout << __func__ << std::endl;
    }
    void OnEnvironmentsTearDownEnd(const UnitTest& /*unit_test*/) override
    {
        std::cout << __func__ << std::endl;
    }
    void OnTestIterationEnd(const UnitTest& /*unit_test*/,
        int /*iteration*/) override
    {
        std::cout << __func__ << std::endl;
    }
    void OnTestProgramEnd(const UnitTest& /*unit_test*/) override
    {
        std::cout << __func__ << std::endl;
    }
};

// 2. 이벤트 리스너를 등록하는 방법
// > main 함수를 통해서 등록하면 됩니다.
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::TestEventListeners& listenerns = UnitTest::GetInstance()->listeners();
    // 기본 프린터를 제거할 수 있습니다.
    // delete listenerns.Release(listenerns.default_result_printer());

    listenerns.Append(new MyTestEventListener);

    return RUN_ALL_TESTS();
}