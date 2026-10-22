// Name: Yong Jie
// Implements route planning coordination for the selected strategy.

#include "routePlanner.h"

using namespace std;

vector<schedule> routePlanner::generate(
    shuttleManager& sList,
    passengerManager& pList,
    RoutePlanningStrategy& strategy)
{
	schedules.clear();
    workShuttles.clear();
    workPassengers = pList.getItems();

    if (sList.isEmpty())
    {
        return schedules;
    }

    schedules = strategy.generate(sList.getItems(), workPassengers, workShuttles);

	return schedules;
}

const vector<schedule>& routePlanner::getSchedules() const
{
    return schedules;
}

const vector<shuttle>& routePlanner::getRemainingShuttles() const
{
    return workShuttles;
}

const vector<passenger>& routePlanner::getRemainingPassengers() const
{
    return workPassengers;
}
