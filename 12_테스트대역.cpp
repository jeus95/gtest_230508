// 12_테스트대역.cpp
#include <string>

class FileSystem {
public:
    bool IsValidFilename(const std::string& filename)
    {
        // 현재의 파일 시스템에서 유효한 이름인지 체크합니다.
        //  : NTFS, ext3 ...
        return false;
    }
};

// Logger
//   IsValidLogFilename ---X---> FileSystem
//            |
//             ----------------> TestDouble

// Test Double(테스트 대역)
// - 목적: 테스트 환경을 통제하기 위해 사용합니다.
// - 적용: 제품 코드에 테스트 대역을 적용하기 위해서는, 제품 코드가 테스트 대역을
//        적용할 수 있는 형태로 설계되어야 합니다.

class Logger {
public:
    // 확장자를 제외한 파일명이 5글자 이상이어야 한다.
    // ex)
    // file.log  ---> file   => X
    // hello.log ---> hello  => OK
    bool IsValidLogFilename(const std::string& filename)
    {
        //----- 테스트 대상 코드 -----
        size_t index = filename.find_last_of(".");
        std::string name = filename.substr(0, index);
        if (name.size() < 5)
            return false;
        //----- 테스트 대상 코드 -----

        FileSystem fs;
        return fs.IsValidFilename(filename);
    }
};

#include <gtest/gtest.h>

TEST(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue)
{
    Logger logger;
    std::string validFilename = "valid.log";

    EXPECT_TRUE(logger.IsValidLogFilename(validFilename))
        << "확장자를 제외한 파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse)
{
    Logger logger;
    std::string invalidFilename = "bad.log";

    EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename))
        << "확장자를 제외한 파일명이 다섯글자 미만일 때";
}