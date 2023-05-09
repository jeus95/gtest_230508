// 14_Fake.cpp
#include <string>

class User {
private:
    std::string name;
    int age;

public:
    User(const std::string s, int n)
        : name(s)
        , age(n)
    {
    }

    std::string GetName() const { return name; }
    int GetAge() const { return age; }
};

class IDatabase {
public:
    virtual ~IDatabase() { }

    virtual void SaveUser(const std::string& name, User* user) = 0;
    virtual User* LoadUser(const std::string& name) = 0;
};

class UserRepository {
    IDatabase* database;

public:
    UserRepository(IDatabase* p)
        : database(p)
    {
    }

    void Save(User* user)
    {
        // ...
        database->SaveUser(user->GetName(), user);
    }

    User* Load(const std::string& name)
    {
        // ...
        return database->LoadUser(name);
    }
};

// Fake Object Pattern
//  의도: 아직 준비되지 않은 협력 객체로 인해서, 테스트 되지 않은 요구사항이 존재합니다.
//  방법: 동일한 기능을 제공하는 가벼운 테스트 대역을 만들어서,
//       테스트 되지 않은 요구사항을 검증할 수 있습니다.
//  1) 협력 객체가 준비되지 않았을 때
//  2) 협력 객체를 사용하기 어려울 때
//  3) 협력 객체가 너무 느려서, 느린 테스트의 문제가 발생할 때

#include <gtest/gtest.h>
#include <map>

class FakeDatabase : public IDatabase {
private:
    std::map<std::string, User*> data;

public:
    void SaveUser(const std::string& name, User* user) override
    {
        data[name] = user;
    }

    User* LoadUser(const std::string& name) override
    {
        return data[name];
    }
};

// * 구글 테스트에서 사용자 정의 타입에 대해서 단언문을 사용할 경우,
//   연산에 해당하는 연산자 오버로딩이 제공되어야 합니다.
bool operator==(const User& lhs, const User& rhs)
{
    return false;
  // return lhs.GetName() == rhs.GetName() &&    lhs.GetAge() == rhs.GetAge();
}

// * 사용자 정의 객체를 구글 테스트에서 제대로 표시하기 위해서는
//   연산자 재정의가 필요합니다.
std::ostream& operator<<(std::ostream& os, const User& user)
{
    return os << "(" << user.GetName() << ", " << user.GetAge() << ")";
}

TEST(UserRepositoryTest, Save)
{
    FakeDatabase fake;
    UserRepository repo(&fake);
    std::string test_name = "test_name";
    int test_age = 42;
    User expected(test_name, test_age);

    repo.Save(&expected);
    User* actual = repo.Load(test_name);

    EXPECT_EQ(*actual, expected);
}