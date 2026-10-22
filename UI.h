// Name: Bryan
// Declares console menu helpers and menu input functions.

#pragma once

#include <string>
#include <vector>

class UI
{
public:
    static int readChoice(int min, int max);
    static int showMain();
    static int lists();
    static int shuttlePassenger(int sel);
    static int scheduleMenu();
    static int strategyMenu(const std::vector<std::string>& strategyNames);
    static void sort1(const std::string& locationLabel, const std::string& extraLabel);
    static void sort2();
};
