// Name: Yong Jie
// Declares the manager type and metadata for passenger records.

#pragma once
#include <string>
#include "EntityList.h"
#include "passenger.h"

class passengerManager : public EntityList<passenger>
{
public:
    static int menuType();
    static char idPrefix();
    static std::string title();
    static std::string locationLabel();
    static std::string extraLabel();
};
