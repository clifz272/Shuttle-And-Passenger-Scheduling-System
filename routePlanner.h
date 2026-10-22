// Name: Yong Jie
// Declares the service that runs a selected route planning strategy.

#pragma once
#include "schedule.h"
#include "shuttleManager.h"
#include "passengerManager.h"
#include "RoutePlanningStrategy.h"

#include <vector>

class routePlanner
{
private:
    std::vector<schedule> schedules;
    std::vector<shuttle> workShuttles;
    std::vector<passenger> workPassengers;

public:
    std::vector<schedule> generate(shuttleManager&, passengerManager&, RoutePlanningStrategy& strategy);
    const std::vector<schedule>& getSchedules() const;
    const std::vector<shuttle>& getRemainingShuttles() const;
    const std::vector<passenger>& getRemainingPassengers() const;
};
