// Name: Eugene
// Implements the arrival-time-priority scheduling algorithm.

#include "ArrivalTimePriorityStrategy.h"

#include <algorithm>
#include <vector>

std::string ArrivalTimePriorityStrategy::getName() const
{
    return "Arrival Time Priority";
}

std::vector<schedule> ArrivalTimePriorityStrategy::generate(
    const std::vector<shuttle>& shuttles,
    std::vector<passenger>& remainingPassengers,
    std::vector<shuttle>& remainingShuttles)
{
    std::vector<schedule> plannedSchedules;
    std::vector<schedule> shuttleSchedules;
    std::vector<shuttle> sortedShuttles = shuttles;

    remainingShuttles.clear();

    std::sort(sortedShuttles.begin(), sortedShuttles.end(),
        [](const shuttle& first, const shuttle& second)
        {
            return first.getArrivalTime() < second.getArrivalTime();
        });

    std::sort(remainingPassengers.begin(), remainingPassengers.end(),
        [](const passenger& first, const passenger& second)
        {
            return first.getArrivalTime() < second.getArrivalTime();
        });

    for (const shuttle& currentShuttle : sortedShuttles)
    {
        shuttleSchedules.push_back(schedule(currentShuttle));
    }

    for (int passengerIndex = 0; passengerIndex < static_cast<int>(remainingPassengers.size()); )
    {
        bool assigned = false;

        for (schedule& currentSchedule : shuttleSchedules)
        {
            if (currentSchedule.addPassenger(remainingPassengers[passengerIndex]))
            {
                remainingPassengers.erase(remainingPassengers.begin() + passengerIndex);
                assigned = true;
                break;
            }
        }

        if (!assigned)
        {
            passengerIndex++;
        }
    }

    for (const schedule& currentSchedule : shuttleSchedules)
    {
        if (currentSchedule.getUsedSeats() > 0)
        {
            plannedSchedules.push_back(currentSchedule);
        }
        else
        {
            remainingShuttles.push_back(currentSchedule.getAssignedShuttle());
        }
    }

    return plannedSchedules;
}
