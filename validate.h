// Name: Clifton
// Declares focused validation checks used by input, parsing, and saving.

#pragma once
#include <string>
#include <vector>

#include "EntityList.h"

class IdValidator
{
public:
    static bool idFormatCheck(const std::string& value);
    static bool idCheck(const std::string& value, char prefix);
    static void id(const std::string& value, char prefix);

    template <class T>
    static bool idUniqueCheck(const std::vector<T>& items, const std::string& id)
    {
        for (const T& item : items)
        {
            if (item.getId().toString() == id)
            {
                return false;
            }
        }

        return true;
    }

    template <class T>
    static bool idUniqueCheck(const EntityList<T>& list, const std::string& id)
    {
        return list.findById(id) == nullptr;
    }
};

class LocationValidator
{
public:
    static bool destCheck(const std::string& value);
    static void dest(const std::string& value);

    static std::string normalizeDest(const std::string& value);
    static void locFile(const std::string& folderPath);
};

class TimeValidator
{
public:
    static bool timeCheck(int hour, int minute);
    static void time(int hour, int minute);
    static bool shuttleOperatingTimeCheck(int minutes);
    static void shuttleOperatingTime(int minutes);
    static bool timeTextCheck(const std::string& value);
    static void timeText(const std::string& value);
};

class FileValidator
{
public:
    static bool txtCheck(const std::string& fileName);
    static void txt(const std::string& fileName);
    static bool fileUniqueCheck(const std::string& folderPath, const std::string& fileName);
    static void fileUnique(const std::string& folderPath, const std::string& fileName);
    static bool folderCheck(const std::string& folderPath);
    static void folder(const std::string& folderPath);
    static bool rowCheck(const std::string& line);
    static void row(const std::string& line);
    static bool recordCountCheck(int count);
    static void recordCount(int count);
};

class ScheduleValidator
{
public:
    static bool scheduleGeneratedCheck(bool generated);
    static void scheduleGenerated(bool generated);
};

class MenuValidator
{
public:
    static bool choiceCheck(int value, int min, int max);
    static void choice(int value, int min, int max);
    static bool choiceTextCheck(const std::string& value, int min, int max);
    static void choiceText(const std::string& value, int min, int max);
};

class CapacityValidator
{
public:
    static bool passengerSizeCheck(int value);
    static void passengerSize(int value);
    static bool passengerSizeTextCheck(const std::string& value);
    static void passengerSizeText(const std::string& value);
    static bool shuttlePackageCheck(const std::string& value);
    static void shuttlePackage(const std::string& value);
    static std::string normalizePackage(const std::string& value);
};
