// Name: Eugene
// Declares the shared base class for passenger and shuttle models.

#pragma once

#include <string>
#include "Id.h"
#include "time.h"
#include "destination.h"

class Entity
{
private:
    Id id;
    Time arrivalTime;

public:
    Entity();
    Entity(const Id& id, const Time& arrivalTime);

    virtual ~Entity() = default;

    Id getId() const;
    Time getArrivalTime() const;

    void setId(const Id& id);
    void setArrivalTime(const Time& arrivalTime);

    virtual Destination getLocation() const = 0;
    virtual std::string getExtraLabel() const = 0;
    virtual std::string getExtraValue() const = 0;
    virtual int getExtraSortValue() const = 0;
    virtual std::string toFile() const = 0;
    virtual std::string getType() const = 0;
};
