// Name: Eugene
// Provides the shuttle manager implementation unit.

#include "shuttleManager.h"

int shuttleManager::menuType()
{
    return 1;
}

char shuttleManager::idPrefix()
{
    return 'S';
}

std::string shuttleManager::title()
{
    return "Shuttle";
}

std::string shuttleManager::locationLabel()
{
    return "Charging Point";
}

std::string shuttleManager::extraLabel()
{
    return "Package";
}
