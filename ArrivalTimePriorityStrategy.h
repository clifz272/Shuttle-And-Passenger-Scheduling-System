// Name: Eugene
// Declares the route planning strategy that prioritizes earlier arrival times.

#pragma once

#include "RoutePlanningStrategy.h"

class ArrivalTimePriorityStrategy : public RoutePlanningStrategy
{
public:
    std::string getName() const override;

    std::vector<schedule> generate(
        const std::vector<shuttle>& shuttles,
        std::vector<passenger>& remainingPassengers,
        std::vector<shuttle>& remainingShuttles) override;
};
