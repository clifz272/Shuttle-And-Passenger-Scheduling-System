// Name: Eugene
// Declares the shuttle model used by lists, schedules, and route planning.

#pragma once

#include <ostream>
#include <string>
#include "Entity.h"
#include "destination.h"
#include "shuttlePackage.h"

class shuttle : public Entity
{
    friend std::ostream& operator<<(std::ostream& out, const shuttle& s);
private:
    Destination chargingPoint;
    shuttlePackage package;

public:
    shuttle();
    shuttle(const Id& id, const Destination& chargingPoint, const Time& arrivalTime, const shuttlePackage& package);

    Destination getLocation() const override;
    std::string getExtraLabel() const override;
    std::string getExtraValue() const override;
    int getExtraSortValue() const override;
    void setChargingPoint(const Destination& chargingPoint);
    std::string toFile() const override;
    shuttlePackage getPackage() const;
    int getMaxSeats() const;
    void setPackage(const shuttlePackage& package);

    std::string getType() const override;
};
