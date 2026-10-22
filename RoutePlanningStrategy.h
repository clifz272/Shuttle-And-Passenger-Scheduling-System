// Name: Joseph
// Declares the strategy interface for interchangeable route planning algorithms.

#pragma once

#include <string>
#include <vector>

#include "schedule.h"
#include "shuttle.h"
#include "passenger.h"

class RoutePlanningStrategy
{
public:
    virtual ~RoutePlanningStrategy() = default;

    virtual std::string getName() const = 0;

    virtual std::vector<schedule> generate(
        const std::vector<shuttle>& shuttles,
        std::vector<passenger>& remainingPassengers,
        std::vector<shuttle>& remainingShuttles) = 0;
};
