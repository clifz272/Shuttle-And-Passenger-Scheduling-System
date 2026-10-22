// Name: Clifton
// Declares the registry that exposes available route planning strategies.

#pragma once

#include <memory>
#include <vector>

#include "RoutePlanningStrategy.h"

class StrategyRegistry
{
public:
    static std::vector<std::unique_ptr<RoutePlanningStrategy>> getStrategies();
};
