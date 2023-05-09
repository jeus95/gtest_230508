// 13_Stub2.cpp
#include <iostream>
#include <string>

class Time {
public:
    virtual ~Time() { }

    virtual std::string GetCurrentTime() const = 0;
};

class Clock : public Time {
public:
    std::string GetCurrentTime() const
    {
        time_t rawTime;
        tm* timeInfo;
        char buffer[80];

        time(&rawTime);
        timeInfo = localtime(&rawTime);

        strftime(buffer, 80, "%H:%M", timeInfo);

        return std::string(buffer);
    }
};

class User {
    Time* time;

public:
    User(Time* t)
        : time(t)
    {
    }

    int Alarm()
    {
        std::string current = time->GetCurrentTime();
        if (current == "00:00") {
            return 42;
        }

        if (current == "10:00") {
            return 100;
        }

        return 0;
    }
};

#include <gtest/gtest.h>

// 00:00
TEST(UserTest, Alarm)
{
    Clock clock;
    User user(&clock);

    EXPECT_EQ(user.Alarm(), 42);
}

// 10:00
TEST(UserTest, Alarm2)
{
    Clock clock;
    User user(&clock);

    EXPECT_EQ(user.Alarm(), 100);
}
