// Name: Joseph
// Declares schedule analysis helpers for summaries and strategy recommendations.

#pragma once

#include <string>
#include <vector>

#include "passenger.h"
#include "schedule.h"
#include "shuttle.h"

struct UnassignedReason
{
    passenger unassignedPassenger;
    std::string reason;
};

struct ScheduleStats
{
    std::string strategyName;
    int schedulesUsed;
    int unusedShuttles;
    int assignedPassengerGroups;
    int assignedPeople;
    int unassignedPassengerGroups;
    int unassignedPeople;
    int seatsUsed;
    int remainingSeatsInUsedShuttles;
    double seatUtilisation;
};

class ScheduleAnalyzer
{
public:
    static std::vector<UnassignedReason> getUnassignedReasons(
        const std::vector<schedule>& schedules,
        const std::vector<shuttle>& remainingShuttles,
        const std::vector<passenger>& remainingPassengers);

    static ScheduleStats getStats(
        const std::string& strategyName,
        const std::vector<schedule>& schedules,
        const std::vector<shuttle>& remainingShuttles,
        const std::vector<passenger>& remainingPassengers);

    static std::string recommendBetterStrategy(
        const ScheduleStats& first,
        const ScheduleStats& second);

    static std::string recommendBestStrategy(
        const std::vector<ScheduleStats>& stats);

private:
    static std::string findReason(
        const std::vector<schedule>& possibleSchedules,
        const passenger& currentPassenger);
};
