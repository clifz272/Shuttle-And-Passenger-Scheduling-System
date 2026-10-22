// Name: Joseph
// Implements schedule metrics, unassigned-passenger reasons, and strategy recommendations.

#include "ScheduleAnalyzer.h"

#include "MatchRule.h"

using namespace std;

namespace
{
    int compareStats(const ScheduleStats& first, const ScheduleStats& second)
    {
        if (first.assignedPeople != second.assignedPeople)
        {
            return first.assignedPeople > second.assignedPeople ? 1 : -1;
        }

        if (first.schedulesUsed != second.schedulesUsed)
        {
            return first.schedulesUsed < second.schedulesUsed ? 1 : -1;
        }

        if (first.seatUtilisation != second.seatUtilisation)
        {
            return first.seatUtilisation > second.seatUtilisation ? 1 : -1;
        }

        return 0;
    }
}

vector<UnassignedReason> ScheduleAnalyzer::getUnassignedReasons(
    const vector<schedule>& schedules,
    const vector<shuttle>& remainingShuttles,
    const vector<passenger>& remainingPassengers)
{
    vector<UnassignedReason> reasons;
    vector<schedule> possibleSchedules = schedules;

    for (const shuttle& currentShuttle : remainingShuttles)
    {
        possibleSchedules.push_back(schedule(currentShuttle));
    }

    for (const passenger& currentPassenger : remainingPassengers)
    {
        reasons.push_back({ currentPassenger, findReason(possibleSchedules, currentPassenger) });
    }

    return reasons;
}

ScheduleStats ScheduleAnalyzer::getStats(
    const string& strategyName,
    const vector<schedule>& schedules,
    const vector<shuttle>& remainingShuttles,
    const vector<passenger>& remainingPassengers)
{
    ScheduleStats stats = {};
    stats.strategyName = strategyName;
    stats.schedulesUsed = static_cast<int>(schedules.size());
    stats.unusedShuttles = static_cast<int>(remainingShuttles.size());
    stats.unassignedPassengerGroups = static_cast<int>(remainingPassengers.size());

    for (const schedule& currentSchedule : schedules)
    {
        stats.assignedPassengerGroups += static_cast<int>(currentSchedule.getAssignedPassengers().size());
        stats.assignedPeople += currentSchedule.getUsedSeats();
        stats.seatsUsed += currentSchedule.getUsedSeats();
        stats.remainingSeatsInUsedShuttles += currentSchedule.getRemainingSeats();
    }

    for (const passenger& currentPassenger : remainingPassengers)
    {
        stats.unassignedPeople += currentPassenger.getPassengerSize().getValue();
    }

    int totalSeatsInUsedShuttles = stats.seatsUsed + stats.remainingSeatsInUsedShuttles;

    if (totalSeatsInUsedShuttles > 0)
    {
        stats.seatUtilisation = (static_cast<double>(stats.seatsUsed) / totalSeatsInUsedShuttles) * 100;
    }

    return stats;
}

string ScheduleAnalyzer::recommendBetterStrategy(
    const ScheduleStats& first,
    const ScheduleStats& second)
{
    if (first.assignedPeople > second.assignedPeople)
    {
        return first.strategyName + " is recommended because it assigns more people.";
    }

    if (second.assignedPeople > first.assignedPeople)
    {
        return second.strategyName + " is recommended because it assigns more people.";
    }

    if (first.schedulesUsed < second.schedulesUsed)
    {
        return first.strategyName + " is recommended because it uses fewer shuttles.";
    }

    if (second.schedulesUsed < first.schedulesUsed)
    {
        return second.strategyName + " is recommended because it uses fewer shuttles.";
    }

    if (first.seatUtilisation > second.seatUtilisation)
    {
        return first.strategyName + " is recommended because it has better seat utilisation.";
    }

    if (second.seatUtilisation > first.seatUtilisation)
    {
        return second.strategyName + " is recommended because it has better seat utilisation.";
    }

    return "Both strategies are tied based on assigned people, shuttles used, and seat utilisation.";
}

string ScheduleAnalyzer::recommendBestStrategy(const vector<ScheduleStats>& stats)
{
    if (stats.empty())
    {
        return "No strategies available to compare.";
    }

    const ScheduleStats* best = &stats[0];
    bool hasTieForBest = false;

    for (int i = 1; i < static_cast<int>(stats.size()); i++)
    {
        int comparison = compareStats(stats[i], *best);

        if (comparison > 0)
        {
            best = &stats[i];
            hasTieForBest = false;
        }
        else if (comparison == 0)
        {
            hasTieForBest = true;
        }
    }

    if (hasTieForBest)
    {
        return "Strategies are tied based on assigned people, shuttles used, and seat utilisation.";
    }

    return best->strategyName + " is recommended because it has the best balance of assigned people, shuttles used, and seat utilisation.";
}

string ScheduleAnalyzer::findReason(
    const vector<schedule>& possibleSchedules,
    const passenger& currentPassenger)
{
    bool hasLocation = false;
    bool hasTimeWindow = false;
    bool hasSeats = false;

    for (const schedule& currentSchedule : possibleSchedules)
    {
        const shuttle& currentShuttle = currentSchedule.getAssignedShuttle();

        if (!MatchRule::locationMatch(currentShuttle, currentPassenger))
        {
            continue;
        }

        hasLocation = true;

        if (!MatchRule::timeMatch(currentShuttle, currentPassenger))
        {
            continue;
        }

        hasTimeWindow = true;

        if (!MatchRule::seatMatch(currentSchedule.getRemainingSeats(), currentPassenger))
        {
            continue;
        }

        hasSeats = true;

        if (currentSchedule.canAddPassenger(currentPassenger))
        {
            return "Passenger could fit, but was not selected by the current strategy.";
        }
    }

    if (!hasLocation)
    {
        return "No shuttle goes to this destination.";
    }

    if (!hasTimeWindow)
    {
        return "No shuttle arrives within the 10-minute matching window.";
    }

    if (!hasSeats)
    {
        return "Matching shuttle has insufficient remaining seats.";
    }

    return "Matching shuttle is outside operating hours.";
}
