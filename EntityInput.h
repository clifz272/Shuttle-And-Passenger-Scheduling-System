// Name: Clifton
// Declares console input helpers for creating and updating entity data.

#pragma once

#include <string>

struct EntityInputData
{
    std::string id;
    std::string location;
    std::string arrivalTime;
    std::string extra;
};

class EntityInput
{
public:
    static std::string readId(const std::string& prompt);
    static EntityInputData readItem(const std::string& locationLabel, const std::string& extraLabel);
    static EntityInputData readUpdatedItem(const std::string& locationLabel, const std::string& extraLabel);
};
