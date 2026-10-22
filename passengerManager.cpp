// Name: Yong Jie
// Provides the passenger manager implementation unit.

#include "passengerManager.h"

using namespace std;

int passengerManager::menuType()
{
    return 2;
}

char passengerManager::idPrefix()
{
    return 'P';
}

string passengerManager::title()
{
    return "Passengers";
}

string passengerManager::locationLabel()
{
    return "Destination";
}

string passengerManager::extraLabel()
{
    return "Group Size";
}
