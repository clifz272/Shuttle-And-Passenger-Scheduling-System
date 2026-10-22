// Name: Eugene
// Declares the manager type and metadata for shuttle records.

#pragma once
#include <string>
#include "EntityList.h"
#include "shuttle.h"

class shuttleManager : public EntityList<shuttle>
{
public:
    static int menuType();
    static char idPrefix();
    static std::string title();
    static std::string locationLabel();
    static std::string extraLabel();
};
