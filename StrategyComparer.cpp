// Name: Yong Jie
// Implements side-by-side strategy comparison using copied planning data.

#include "StrategyComparer.h"

#include "StrategyRegistry.h"
#include "routePlanner.h"

StrategyComparisonResult StrategyComparer::compare(
    shuttleManager& shuttles,
    passengerManager& passengers)
{
    StrategyComparisonResult result;
    std::vector<std::unique_ptr<RoutePlanningStrategy>> strategies = StrategyRegistry::getStrategies();

    for (const std::unique_ptr<RoutePlanningStrategy>& currentStrategy : strategies)
    {
        routePlanner planner;
        planner.generate(shuttles, passengers, *currentStrategy);

        result.strategyStats.push_back(ScheduleAnalyzer::getStats(
            currentStrategy->getName(),
            planner.getSchedules(),
            planner.getRemainingShuttles(),
            planner.getRemainingPassengers()));
    }

    result.recommendation = ScheduleAnalyzer::recommendBestStrategy(result.strategyStats);

    return result;
}
