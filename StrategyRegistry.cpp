// Name: Clifton
// Registers the route planning strategies available to the program.

#include "StrategyRegistry.h"

#include "ArrivalTimePriorityStrategy.h"
#include "MinimumDispatchStrategy.h"

std::vector<std::unique_ptr<RoutePlanningStrategy>> StrategyRegistry::getStrategies()
{
    std::vector<std::unique_ptr<RoutePlanningStrategy>> strategies;

    strategies.push_back(std::make_unique<MinimumDispatchStrategy>());
    strategies.push_back(std::make_unique<ArrivalTimePriorityStrategy>());

    return strategies;
}
