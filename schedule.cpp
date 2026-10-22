// Name: Clifton
// Implements passenger-to-shuttle matching, schedule assignment, and serialization.

#include <string>

#include "MatchRule.h"
#include "schedule.h"

using namespace std;

schedule::schedule()
    : usedSeats(0), remainingSeats(0)
{
}

schedule::schedule(const shuttle& sh)
    : assignedShuttle(sh), usedSeats(0), remainingSeats(sh.getMaxSeats())
{
}

bool schedule::canAddPassenger(const passenger& p) const {
    return MatchRule::canAssign(assignedShuttle, remainingSeats, p);
}

bool schedule::addPassenger(const passenger& p)
{
    if (!canAddPassenger(p))
    {
        return false;
    }

    assignedPassengers.push_back(p);
    usedSeats += p.getPassengerSize().getValue();
    remainingSeats -= p.getPassengerSize().getValue();

    return true;
}


std::string schedule::toFile() const
{
    string output = assignedShuttle.toFile() + "," +
        to_string(usedSeats) + "," +
        to_string(remainingSeats);

    for (const passenger& assignedPassenger : assignedPassengers)
    {
        output += "," +
            assignedPassenger.getId().toString() + "|" +
            assignedPassenger.getLocation().toString() + "|" +
            assignedPassenger.getArrivalTime().toString() + "|" +
            assignedPassenger.getPassengerSize().toString();
    }

    return output;
}

const shuttle& schedule::getAssignedShuttle() const
{
    return assignedShuttle;
}

const vector<passenger>& schedule::getAssignedPassengers() const
{
    return assignedPassengers;
}

int schedule::getRemainingSeats() const {
    return remainingSeats;
}

int schedule::getUsedSeats() const {
    return usedSeats;
}
