// 12_테스트대역2.cpp
#include <string>

// Logger
//   IsValidLogFilename ---X---> FileSystem
//            |
//             ----------------> TestDouble

// Test Double(테스트 대역)
// - 목적: 테스트 환경을 통제하기 위해 사용합니다.
// - 적용: 제품 코드에 테스트 대역을 적용하기 위해서는, 제품 코드가 테스트 대역을
//        적용할 수 있는 형태로 설계되어야 합니다.
//   => 약한 결합(느슨한 결합)
//    강한 결합: 협력 객체를 이용할 때, 구체적인 타입에 의존하는 것
//    약한 결합: 협력 객체를 이용할 때, 추상 타입(추상 클래스, 인터페이스)에 의존하는 것

// 1) 인터페이스 도입
class IFileSystem {
public:
    virtual ~IFileSystem() { }

    virtual bool IsValidFilename(const std::string& filename) = 0;
};

class FileSystem : public IFileSystem {
public:
    bool IsValidFilename(const std::string& filename) override
    {
        // 현재의 파일 시스템에서 유효한 이름인지 체크합니다.
        //  : NTFS, ext3 ...
        return false;
    }
};

// 2) 협력 객체를 직접 생성하면 안됩니다.
//    외부에서 생성해서 전달받아야 합니다.
//   => DI(Dependency Injection, 의존성 주입)
//   의존성 주입
//   1) 생성자 주입
//    - 협력 객체가 필수적일 때
//   2) 메소드 주입
//    - 협력 객체가 필수적이지 않을 때

class Logger {
    IFileSystem* fs;

public:
    Logger(IFileSystem* p = nullptr)
        : fs(p)
    {
        // 기존 제품코드가 사용하던 방식과 동일한 방식으로 사용할 수 있습니다.
        if (fs == nullptr) {
            fs = new FileSystem;
        }
    }

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

        // FileSystem fs;
        // return fs.IsValidFilename(filename);

        // IFileSystem* fs = new FileSystem;
        return fs->IsValidFilename(filename);
    }
};

#include <gtest/gtest.h>

// 테스트 대역은 협력 객체의 인터페이스를 구현하는 형태로 만들 수 있습니다.
class StubFileSystem : public IFileSystem {
public:
    bool IsValidFilename(const std::string& filename) override
    {
        return true;
    }
};

TEST(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue)
{
    StubFileSystem stub;
    Logger logger(&stub);
    std::string validFilename = "valid.log";

    EXPECT_TRUE(logger.IsValidLogFilename(validFilename))
        << "확장자를 제외한 파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse)
{
    StubFileSystem stub;
    Logger logger(&stub);
    std::string invalidFilename = "bad.log";

    EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename))
        << "확장자를 제외한 파일명이 다섯글자 미만일 때";
}