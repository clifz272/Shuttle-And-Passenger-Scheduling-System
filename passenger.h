// Name: Yong Jie
// Declares the passenger model used by lists, schedules, and route planning.

#pragma once

#include <string>
#include <ostream>
#include "Entity.h"
#include "destination.h"
#include "passengerSize.h"

class passenger : public Entity
{
    friend std::ostream& operator<<(std::ostream& out, const passenger& p);
private:
    Destination destination;
    passengerSize size;

public:
    passenger();
    passenger(const Id& id, const Destination& destination, const Time& arrivalTime, const passengerSize& size);


    Destination getLocation() const override;
    std::string getExtraLabel() const override;
    std::string getExtraValue() const override;
    int getExtraSortValue() const override;
    void setDestination(const Destination& destination);
    passengerSize getPassengerSize() const;
    void setPassengerSize(const passengerSize& passengerSize);

    std::string toFile() const override;
    std::string getType() const override;
};
