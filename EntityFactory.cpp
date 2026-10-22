// Name: Bryan
// Converts parsed text fields into validated passenger and shuttle objects.

#include "EntityFactory.h"

#include <stdexcept>

#include "Id.h"
#include "destination.h"
#include "passengerSize.h"
#include "shuttlePackage.h"
#include "time.h"
#include "validate.h"

passenger EntityFactory<passenger>::create(const std::vector<std::string>& fields)
{
    if (fields.size() != 4)
    {
        throw std::invalid_argument("Passenger row must have 4 fields");
    }

    Id id(fields[0], 'P');
    Destination destination(fields[1]);
    Time arrivalTime(fields[2]);
    CapacityValidator::passengerSizeText(fields[3]);
    passengerSize size(std::stoi(fields[3]));

    return passenger(id, destination, arrivalTime, size);
}

shuttle EntityFactory<shuttle>::create(const std::vector<std::string>& fields)
{
    if (fields.size() != 4)
    {
        throw std::invalid_argument("Shuttle row must have 4 fields");
    }

    Id id(fields[0], 'S');
    Destination chargingPoint(fields[1]);
    Time arrivalTime(fields[2]);
    shuttlePackage package(fields[3]);

    return shuttle(id, chargingPoint, arrivalTime, package);
}
