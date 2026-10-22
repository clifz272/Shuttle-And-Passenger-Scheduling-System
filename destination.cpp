// Name: Yong Jie
// Implements validation, normalization, comparison, and output for destinations.

#include "destination.h"
#include "validate.h"

using namespace std;

Destination::Destination()
{
    name = "";
}

Destination::Destination(const std::string& destinationName)
{
    LocationValidator::dest(destinationName);
    name = LocationValidator::normalizeDest(destinationName);
}

bool Destination::isValid() const
{
    return LocationValidator::destCheck(name);
}

std::string Destination::toString() const
{
    return name;
}

bool Destination::operator==(const Destination& dest) const
{
    return name == dest.name;
}

bool Destination::operator<(const Destination& dest) const
{
    return name < dest.name;
}

ostream& operator<<(ostream& out, const Destination& dest) {
    out << dest.name;
    return out;
}
