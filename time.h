// Name: Joseph
// Declares the Time value object used for validated arrival times.

#pragma once

#include<ostream>
#include <string>

class Time
{
    friend std::ostream& operator<<(std::ostream& out, const Time& time);
private:
    int hour;
    int minute;

public:
    Time();
    Time(int hour, int minute);
    Time(const std::string& timeText);

    bool isValid() const;
    int toMinutes() const;
    std::string toString() const;

    bool operator==(const Time& other) const;
    bool operator<(const Time& other) const;
};
