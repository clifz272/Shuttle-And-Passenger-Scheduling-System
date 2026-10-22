// Name: Bryan
// Declares display helpers for schedules, leftovers, and strategy comparison results.

#pragma once

#include <string>
#include <vector>

#include "ScheduleAnalyzer.h"
#include "schedule.h"

class ScheduleShow
{
public:
    static void showSchedules(const std::vector<schedule>& schedules);
    static void showSummary(
        const std::vector<schedule>& schedules,
        const std::vector<shuttle>& remainingShuttles,
        const std::vector<passenger>& remainingPassengers);
    static void showLeftoversWithReasons(
        const std::vector<shuttle>& remainingShuttles,
        const std::vector<UnassignedReason>& reasons);
    static void showUnassignedReasons(const std::vector<UnassignedReason>& reasons);
    static void showStrategyComparison(
        const std::vector<ScheduleStats>& stats,
        const std::string& recommendation);
};
