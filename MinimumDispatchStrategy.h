// Name: Eugene
// Declares the strategy that prioritizes larger passenger groups and larger shuttles.

#pragma once

#include "RoutePlanningStrategy.h"

class MinimumDispatchStrategy :
    public RoutePlanningStrategy
{
public:
    std::string getName() const override;

    std::vector<schedule> generate(
        const std::vector<shuttle>& shuttles,
        std::vector<passenger>& remainingPassengers,
        std::vector<shuttle>& remainingShuttles) override;
};

