// Name: Bryan
// Implements console output for schedules, leftovers, summaries, and comparisons.

#include "ScheduleShow.h"

#include <iomanip>
#include <iostream>
#include <string>

#include "EntityShow.h"

namespace
{
    const int metricWidth = 38;
    const int columnWidth = 24;

    void showIntComparisonRow(
        const std::string& label,
        const std::vector<ScheduleStats>& stats,
        int ScheduleStats::* value)
    {
        std::cout << std::setw(metricWidth) << label;

        for (const ScheduleStats& currentStats : stats)
        {
            std::cout << std::setw(columnWidth) << (currentStats.*value);
        }

        std::cout << std::endl;
    }

    void showDoubleComparisonRow(
        const std::string& label,
        const std::vector<ScheduleStats>& stats,
        double ScheduleStats::* value)
    {
        std::cout << std::setw(metricWidth) << label;

        for (const ScheduleStats& currentStats : stats)
        {
            std::cout << std::setw(columnWidth) << (currentStats.*value);
        }

        std::cout << std::endl;
    }
}

void ScheduleShow::showSchedules(const std::vector<schedule>& schedules)
{
    if (schedules.empty())
    {
        std::cout << "No schedules found." << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "----Schedule----" << std::endl;

    for (int i = 0; i < static_cast<int>(schedules.size()); i++)
    {
        std::cout << std::endl;
        std::cout << "----------------" << std::endl;
        std::cout << i + 1 << ". ";
        EntityShow<shuttle>::showDetails(schedules[i].getAssignedShuttle(), "Charging Point");
        std::cout << "   Used Seats: " << schedules[i].getUsedSeats()
            << " | Remaining Seats: " << schedules[i].getRemainingSeats() << std::endl;

        const std::vector<passenger>& assignedPassengers = schedules[i].getAssignedPassengers();

        for (int k = 0; k < static_cast<int>(assignedPassengers.size()); k++)
        {
            std::cout << "   Passenger " << k + 1 << ". ";
            EntityShow<passenger>::showDetails(assignedPassengers[k], "Destination");
        }
    }
}

void ScheduleShow::showSummary(
    const std::vector<schedule>& schedules,
    const std::vector<shuttle>& remainingShuttles,
    const std::vector<passenger>& remainingPassengers)
{
    ScheduleStats stats = ScheduleAnalyzer::getStats(
        "Current Schedule",
        schedules,
        remainingShuttles,
        remainingPassengers);

    std::cout << std::endl;
    std::cout << "---- Schedule Summary ----" << std::endl;
    std::cout << "Schedules created: " << stats.schedulesUsed << std::endl;
    std::cout << "Assigned passenger groups: " << stats.assignedPassengerGroups << std::endl;
    std::cout << "Seats used: " << stats.seatsUsed << std::endl;
    std::cout << "Remaining seats in used shuttles: " << stats.remainingSeatsInUsedShuttles << std::endl;
    std::cout << "Unused shuttles: " << stats.unusedShuttles << std::endl;
    std::cout << "Unassigned passenger groups: " << stats.unassignedPassengerGroups << std::endl;
    std::cout << "Unassigned people: " << stats.unassignedPeople << std::endl;
}

void ScheduleShow::showLeftoversWithReasons(
    const std::vector<shuttle>& remainingShuttles,
    const std::vector<UnassignedReason>& reasons)
{
    std::cout << std::endl;
    std::cout << "---- Leftover Shuttles and Passengers ----" << std::endl;

    EntityShow<shuttle>::showAll(
        remainingShuttles,
        "Remaining Shuttles",
        "Charging Point",
        "Package");

    showUnassignedReasons(reasons);
}

void ScheduleShow::showUnassignedReasons(const std::vector<UnassignedReason>& reasons)
{
    if (reasons.empty())
    {
        std::cout << "No unassigned passengers found." << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "---- Unassigned Passenger Reasons ----" << std::endl;
    std::cout << std::left
        << std::setw(6) << "ID"
        << std::setw(20) << "Destination"
        << std::setw(14) << "Arrival Time"
        << std::setw(12) << "Group Size"
        << "Reason" << std::endl;

    for (const UnassignedReason& currentReason : reasons)
    {
        const passenger& currentPassenger = currentReason.unassignedPassenger;

        std::cout << std::left
            << std::setw(6) << currentPassenger.getId().toString()
            << std::setw(20) << currentPassenger.getLocation().toString()
            << std::setw(14) << currentPassenger.getArrivalTime().toString()
            << std::setw(12) << currentPassenger.getPassengerSize().toString()
            << currentReason.reason << std::endl;
    }
}

void ScheduleShow::showStrategyComparison(
    const std::vector<ScheduleStats>& stats,
    const std::string& recommendation)
{
    if (stats.empty())
    {
        std::cout << "No strategy comparison data found." << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "---- Strategy Comparison ----" << std::endl;
    std::cout << std::left << std::setw(metricWidth) << "Metric";

    for (const ScheduleStats& currentStats : stats)
    {
        std::cout << std::setw(columnWidth) << currentStats.strategyName;
    }

    std::cout << std::endl;

    showIntComparisonRow("Schedules used", stats, &ScheduleStats::schedulesUsed);
    showIntComparisonRow("Unused shuttles", stats, &ScheduleStats::unusedShuttles);
    showIntComparisonRow("Assigned passenger groups", stats, &ScheduleStats::assignedPassengerGroups);
    showIntComparisonRow("Assigned people", stats, &ScheduleStats::assignedPeople);
    showIntComparisonRow("Unassigned passenger groups", stats, &ScheduleStats::unassignedPassengerGroups);
    showIntComparisonRow("Unassigned people", stats, &ScheduleStats::unassignedPeople);
    showIntComparisonRow("Seats used", stats, &ScheduleStats::seatsUsed);
    showIntComparisonRow("Remaining seats in used shuttles", stats, &ScheduleStats::remainingSeatsInUsedShuttles);

    std::cout << std::fixed << std::setprecision(2);
    showDoubleComparisonRow("Seat utilisation", stats, &ScheduleStats::seatUtilisation);
    std::cout.unsetf(std::ios::floatfield);

    std::cout << std::endl;
    std::cout << "Recommended: " << recommendation << std::endl;
}
