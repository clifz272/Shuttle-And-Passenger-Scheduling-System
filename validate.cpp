// Name: Clifton
// Implements focused validation, normalization, and file/path checks.

#include "validate.h"

#include <cctype>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

namespace
{
    vector<string> validLocations;

    string lowerText(const string& value)
    {
        string lowered = value;

        for (char& ch : lowered)
        {
            ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        }

        return lowered;
    }

    bool digitTextCheck(const string& value)
    {
        if (value.empty())
        {
            return false;
        }

        for (char ch : value)
        {
            if (!isdigit(static_cast<unsigned char>(ch)))
            {
                return false;
            }
        }

        return true;
    }

    bool destTextCheck(const string& value)
    {
        if (value == "")
        {
            return false;
        }

        for (char ch : value)
        {
            if (!isalnum(static_cast<unsigned char>(ch)) && ch != '_')
            {
                return false;
            }
        }

        return true;
    }
}

bool IdValidator::idFormatCheck(const string& value)
{
    return value.length() == 3 &&
        isalpha(static_cast<unsigned char>(value[0])) &&
        isdigit(static_cast<unsigned char>(value[1])) &&
        isdigit(static_cast<unsigned char>(value[2]));
}

bool IdValidator::idCheck(const string& value, char prefix)
{
    return idFormatCheck(value) && value[0] == prefix;
}

void IdValidator::id(const string& value, char prefix)
{
    if (!idCheck(value, prefix))
    {
        throw invalid_argument("Invalid ID format");
    }
}

bool LocationValidator::destCheck(const string& value)
{
    return normalizeDest(value) != "";
}

void LocationValidator::dest(const string& value)
{
    if (!destCheck(value))
    {
        throw invalid_argument("Invalid destination");
    }
}

string LocationValidator::normalizeDest(const string& value)
{
    if (!destTextCheck(value))
    {
        return "";
    }

    string inputLocation = lowerText(value);

    for (const string& location : validLocations)
    {
        if (lowerText(location) == inputLocation)
        {
            return location;
        }
    }

    return "";
}

void LocationValidator::locFile(const string& folderPath)
{
    FileValidator::folder(folderPath);

    filesystem::path fullPath = filesystem::path(folderPath) / "Location.txt";
    ifstream file(fullPath);

    if (!file.is_open())
    {
        throw invalid_argument("Unable to open Location.txt");
    }

    vector<string> loadedLocations;

    string location;

    while (getline(file, location))
    {
        if (location == "")
        {
            continue;
        }

        if (!destTextCheck(location))
        {
            throw invalid_argument("Invalid location in Location.txt");
        }

        for (const string& existingLocation : loadedLocations)
        {
            if (lowerText(existingLocation) == lowerText(location))
            {
                throw invalid_argument("Duplicate location in Location.txt");
            }
        }

        loadedLocations.push_back(location);
    }

    if (loadedLocations.empty())
    {
        throw invalid_argument("Location.txt has no valid locations");
    }

    validLocations = loadedLocations;
}

bool TimeValidator::timeCheck(int hour, int minute)
{
    return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59;
}

void TimeValidator::time(int hour, int minute)
{
    if (!timeCheck(hour, minute))
    {
        throw invalid_argument("Invalid time");
    }
}

bool TimeValidator::shuttleOperatingTimeCheck(int minutes)
{
    const int startTime = 6 * 60;
    const int endTime = 24 * 60;

    return minutes == 0 || (minutes >= startTime && minutes < endTime);
}

void TimeValidator::shuttleOperatingTime(int minutes)
{
    if (!shuttleOperatingTimeCheck(minutes))
    {
        throw invalid_argument("Shuttle operating time must be from 6:00am to 12:00am");
    }
}

bool TimeValidator::timeTextCheck(const string& value)
{
    size_t colon = value.find(':');

    if (colon == string::npos)
    {
        return false;
    }

    if ((colon != 1 && colon != 2) || value.find(':', colon + 1) != string::npos)
    {
        return false;
    }

    string hourText = value.substr(0, colon);
    string remainingText = value.substr(colon + 1);

    if (remainingText.length() != 2 && remainingText.length() != 4)
    {
        return false;
    }

    string minuteText = remainingText.substr(0, 2);
    string period = "";
    
    if (remainingText.length() == 4)
    {
        period = lowerText(remainingText.substr(2));
    }

    if (!digitTextCheck(hourText) || !digitTextCheck(minuteText))
    {
        return false;
    }

    int hour = stoi(hourText);
    int minute = stoi(minuteText);

    if (minute < 0 || minute > 59)
    {
        return false;
    }

    if (period == "")
    {
        return hour >= 0 && hour <= 23;
    }

    if (period != "am" && period != "pm")
    {
        return false;
    }

    return hour >= 1 && hour <= 12;
}

void TimeValidator::timeText(const string& value)
{
    if (!timeTextCheck(value))
    {
        throw invalid_argument("Invalid time format");
    }
}

bool FileValidator::txtCheck(const string& fileName)
{
    return fileName.length() >= 4 &&
        fileName.substr(fileName.length() - 4) == ".txt";
}

void FileValidator::txt(const string& fileName)
{
    if (!txtCheck(fileName))
    {
        throw invalid_argument("File must end with .txt");
    }
}

bool FileValidator::fileUniqueCheck(const string& folderPath, const string& fileName)
{
    filesystem::path fullPath = filesystem::path(folderPath) / fileName;
    return !filesystem::exists(fullPath);
}

void FileValidator::fileUnique(const string& folderPath, const string& fileName)
{
    if (!fileUniqueCheck(folderPath, fileName))
    {
        throw invalid_argument("File already exists. Please use a new file name.");
    }
}

bool FileValidator::folderCheck(const string& folderPath)
{
    return filesystem::exists(folderPath) &&
        filesystem::is_directory(folderPath);
}

void FileValidator::folder(const string& folderPath)
{
    if (!folderCheck(folderPath))
    {
        throw invalid_argument("Invalid folder path");
    }
}

bool FileValidator::rowCheck(const string& line)
{
    stringstream ss(line);

    vector<string> fields;
    string field;

    while (getline(ss, field, ','))
    {
        if (field == "")
        {
            return false;
        }

        fields.push_back(field);
    }

    if (fields.size() != 4)
    {
        return false;
    }

    return true;
}

void FileValidator::row(const string& line)
{
    if (!rowCheck(line))
    {
        throw invalid_argument("Invalid file row");
    }
}

bool FileValidator::recordCountCheck(int count)
{
    return count > 0;
}

void FileValidator::recordCount(int count)
{
    if (!recordCountCheck(count))
    {
        throw invalid_argument("File has no valid records");
    }
}

bool ScheduleValidator::scheduleGeneratedCheck(bool generated)
{
    return generated;
}

void ScheduleValidator::scheduleGenerated(bool generated)
{
    if (!scheduleGeneratedCheck(generated))
    {
        throw invalid_argument("Please generate a schedule first.");
    }
}

bool MenuValidator::choiceCheck(int value, int min, int max)
{
    return value >= min && value <= max;
}

void MenuValidator::choice(int value, int min, int max)
{
    if (!choiceCheck(value, min, max))
    {
        throw invalid_argument("Invalid menu choice");
    }
}

bool MenuValidator::choiceTextCheck(const string& value, int min, int max)
{
    if (value.empty())
    {
        return false;
    }

    if (!digitTextCheck(value))
    {
        return false;
    }

    try
    {
        return choiceCheck(stoi(value), min, max);
    }
    catch (const exception&)
    {
        return false;
    }
}

void MenuValidator::choiceText(const string& value, int min, int max)
{
    if (!choiceTextCheck(value, min, max))
    {
        throw invalid_argument("Invalid menu choice");
    }
}

bool CapacityValidator::passengerSizeCheck(int value) {
    return value >= 1 && value <= 15;
}

void CapacityValidator::passengerSize(int value) {
    if (!passengerSizeCheck(value)) {
        throw invalid_argument("Invalid size");
    }
}

bool CapacityValidator::passengerSizeTextCheck(const string& value)
{
    if (value.empty())
    {
        return false;
    }

    if (!digitTextCheck(value))
    {
        return false;
    }

    try
    {
        return passengerSizeCheck(stoi(value));
    }
    catch (const exception&)
    {
        return false;
    }
}

void CapacityValidator::passengerSizeText(const string& value)
{
    if (!passengerSizeTextCheck(value))
    {
        throw invalid_argument("Invalid size");
    }
}

string CapacityValidator::normalizePackage(const string& value)
{
    string package = lowerText(value);

    if (package == "small")
    {
        return "Small";
    }

    if (package == "family")
    {
        return "Family";
    }

    if (package == "premium")
    {
        return "Premium";
    }

    return "";
}

bool CapacityValidator::shuttlePackageCheck(const string& value) {
    return normalizePackage(value) != "";
}

void CapacityValidator::shuttlePackage(const string& value) {
    if (!shuttlePackageCheck(value)) {
        throw invalid_argument("Invalid Package");
    }
}
