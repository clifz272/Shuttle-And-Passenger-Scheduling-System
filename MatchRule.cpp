// Name: Bryan
// Implements shared passenger-to-shuttle matching rules.

#include "MatchRule.h"

#include "passenger.h"
#include "shuttle.h"
#include "validate.h"

bool MatchRule::locationMatch(const shuttle& currentShuttle, const passenger& currentPassenger)
{
    return currentShuttle.getLocation() == currentPassenger.getLocation();
}

bool MatchRule::timeMatch(const shuttle& currentShuttle, const passenger& currentPassenger)
{
    int shuttleTime = currentShuttle.getArrivalTime().toMinutes();
    int passengerTime = currentPassenger.getArrivalTime().toMinutes();
    int timeDifference = passengerTime - shuttleTime;

    if (timeDifference < 0)
    {
        timeDifference += 24 * 60;
    }

    return timeDifference <= 10;
}

bool MatchRule::seatMatch(int remainingSeats, const passenger& currentPassenger)
{
    return currentPassenger.getPassengerSize().getValue() <= remainingSeats;
}

bool MatchRule::shuttleOperatingTimeMatch(const shuttle& currentShuttle)
{
    return TimeValidator::shuttleOperatingTimeCheck(currentShuttle.getArrivalTime().toMinutes());
}

bool MatchRule::canAssign(const shuttle& currentShuttle, int remainingSeats, const passenger& currentPassenger)
{
    return shuttleOperatingTimeMatch(currentShuttle) &&
        locationMatch(currentShuttle, currentPassenger) &&
        timeMatch(currentShuttle, currentPassenger) &&
        seatMatch(remainingSeats, currentPassenger);
}
