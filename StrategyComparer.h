// Name: Yong Jie
// Declares tools for comparing route planning strategies safely.

#pragma once

#include <string>
#include <vector>

#include "ScheduleAnalyzer.h"
#include "passengerManager.h"
#include "shuttleManager.h"

struct StrategyComparisonResult
{
    std::vector<ScheduleStats> strategyStats;
    std::string recommendation;
};

class StrategyComparer
{
public:
    static StrategyComparisonResult compare(
        shuttleManager& shuttles,
        passengerManager& passengers);
};
