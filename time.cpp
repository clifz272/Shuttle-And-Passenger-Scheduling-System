// Name: Joseph
// Implements time parsing, validation, comparison, and display formatting.

#include "time.h"
#include "validate.h"

#include <cctype>
#include <iomanip>
#include <sstream>

using namespace std;

Time::Time()
{
    hour = 0;
    minute = 0;
}

Time::Time(int h, int m)
{
    TimeValidator::time(h, m);

    hour = h;
    minute = m;
}

Time::Time(const std::string& timeText)
{
    TimeValidator::timeText(timeText);

    size_t colon = timeText.find(':');
    std::string hourText = timeText.substr(0, colon);
    std::string remainingText = timeText.substr(colon + 1);
    std::string minuteText = remainingText.substr(0, 2);
    std::string period = "";

    int inputHour = std::stoi(hourText);
    int inputMinute = std::stoi(minuteText);

    if (remainingText.length() == 4)
    {
        period = remainingText.substr(2);

        for (char& ch : period)
        {
            ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        }
    }

    if (period == "am" || period == "AM")
    {
        if (inputHour == 12)
            inputHour = 0;
    }
    else if (period == "pm" || period == "PM")
    {
        if (inputHour != 12)
            inputHour += 12;
    }

    TimeValidator::time(inputHour, inputMinute);

    hour = inputHour;
    minute = inputMinute;
}

bool Time::isValid() const
{
    return TimeValidator::timeCheck(hour, minute);
}

int Time::toMinutes() const
{
    return hour * 60 + minute;
}

std::string Time::toString() const
{
    int displayHour = hour;
    std::string period = "am";

    if (hour >= 12)
    {
        period = "pm";
    }

    if (displayHour == 0)
    {
        displayHour = 12;
    }
    else if (displayHour > 12)
    {
        displayHour -= 12;
    }

    std::ostringstream output;
    output << displayHour << ":" << std::setw(2) << std::setfill('0') << minute << period;

    return output.str();
}

bool Time::operator==(const Time& other) const
{
    return hour == other.hour && minute == other.minute;
}

bool Time::operator<(const Time& other) const
{
    return toMinutes() < other.toMinutes();
}

ostream& operator<<(ostream& out, const Time& time) {
    out << time.toString();
    return out;
}
