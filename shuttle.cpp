// Name: Eugene
// Implements shuttle construction, accessors, serialization, and display output.

using namespace std;

#include "shuttle.h"
#include "validate.h"

ostream& operator<<(ostream& out, const shuttle& s) {
    out << s.getId() << " | " << s.getLocation().toString() << " | "
        << s.getArrivalTime().toString() << " | " << s.getPackage().toString();
    return out;
}

shuttle::shuttle()
    : Entity(), chargingPoint(), package()
{
}

shuttle::shuttle(const Id& id, const Destination& chargingPoint, const Time& arrivalTime, const shuttlePackage& package)
    : Entity(id, arrivalTime), chargingPoint(chargingPoint), package(package)
{
    TimeValidator::shuttleOperatingTime(arrivalTime.toMinutes());
}

Destination shuttle::getLocation() const
{
    return chargingPoint;
}

string shuttle::getExtraLabel() const
{
    return "Package";
}

string shuttle::getExtraValue() const
{
    return getPackage().toString();
}

int shuttle::getExtraSortValue() const
{
    return getPackage().getMaxSeats();
}

void shuttle::setChargingPoint(const Destination& chargingPoint)
{
    this->chargingPoint = chargingPoint;
}

shuttlePackage shuttle::getPackage() const {
    return package;
}

int shuttle::getMaxSeats() const {
    return package.getMaxSeats();
}

void shuttle::setPackage(const shuttlePackage& package) {
    this->package = package;
}

string shuttle::toFile() const
{
    return getId().toString() + "," +
        getLocation().toString() + "," +
        getArrivalTime().toString() + "," +
        getPackage().toString();
}

string shuttle::getType() const
{
    return "Shuttle";
}
