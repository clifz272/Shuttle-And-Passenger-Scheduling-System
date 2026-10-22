// Name: Eugene
// Implements the minimum-dispatch scheduling algorithm.

#include "MinimumDispatchStrategy.h"

#include <algorithm>

std::string MinimumDispatchStrategy::getName() const
{
    return "Minimum Dispatch";
}

std::vector<schedule> MinimumDispatchStrategy::generate(
    const std::vector<shuttle>& shuttles,
    std::vector<passenger>& remainingPassengers,
    std::vector<shuttle>& remainingShuttles)
{
    std::vector<schedule> schedules;
    std::vector<shuttle> sortedShuttles = shuttles;
    std::vector<passenger> sortedPassengers = remainingPassengers;

    remainingPassengers.clear();
    remainingShuttles.clear();

    std::sort(sortedShuttles.begin(), sortedShuttles.end(),
        [](const shuttle& first, const shuttle& second)
        {
            return first.getMaxSeats() > second.getMaxSeats();
        });

    std::sort(sortedPassengers.begin(), sortedPassengers.end(),
        [](const passenger& first, const passenger& second)
        {
            return first.getPassengerSize().getValue() > second.getPassengerSize().getValue();
        });

    for (const shuttle& currentShuttle : sortedShuttles)
    {
        schedule temp(currentShuttle);

        for (int k = 0; k < static_cast<int>(sortedPassengers.size()); )
        {
            if (temp.addPassenger(sortedPassengers[k]))
            {
                sortedPassengers.erase(sortedPassengers.begin() + k);
            }
            else
            {
                k++;
            }

            if (temp.getRemainingSeats() == 0)
            {
                break;
            }
        }

        if (temp.getUsedSeats() > 0)
        {
            schedules.push_back(temp);
        }
        else
        {
            remainingShuttles.push_back(currentShuttle);
        }
    }

    remainingPassengers = sortedPassengers;

    return schedules;
}
