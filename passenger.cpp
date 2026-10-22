// Name: Yong Jie
// Implements passenger construction, accessors, serialization, and display output.

using namespace std;

#include "passenger.h"

ostream& operator<<(ostream& out, const passenger& p) {
    out << p.getId() << " | " << p.getLocation().toString() << " | "
        << p.getArrivalTime().toString() << " | " << p.getPassengerSize().toString();
    return out;
}

passenger::passenger()
    : Entity(), destination(), size()
{
}

passenger::passenger(const Id& id, const Destination& destination, const Time& arrivalTime, const passengerSize& size)
    : Entity(id, arrivalTime), destination(destination), size(size)
{
}


Destination passenger::getLocation() const
{
    return destination;
}

string passenger::getExtraLabel() const
{
    return "Group Size";
}

string passenger::getExtraValue() const
{
    return getPassengerSize().toString();
}

int passenger::getExtraSortValue() const
{
    return getPassengerSize().getValue();
}

void passenger::setDestination(const Destination& destination)
{
    this->destination = destination;
}

passengerSize passenger::getPassengerSize() const {
    return size;
}

void passenger::setPassengerSize(const passengerSize& size) {
    this->size = size;
}

string passenger::toFile() const
{
    return getId().toString() + "," +
        getLocation().toString() + "," +
        getArrivalTime().toString() + "," +
        getPassengerSize().toString();
}

std::string passenger::getType() const
{
    return "Passenger";
}
