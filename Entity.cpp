// Name: Eugene
// Implements shared ID and arrival-time behavior for entity models.

#include "Entity.h"

using namespace std;

Entity::Entity()
{
    id = Id();
    arrivalTime = Time();
}

Entity::Entity(const Id& id, const Time& arrivalTime)
{
    this->id = id;
    this->arrivalTime = arrivalTime;
}

Id Entity::getId() const
{
    return id;
}

Time Entity::getArrivalTime() const
{
    return arrivalTime;
}

void Entity::setId(const Id& id)
{
    this->id = id;
}

void Entity::setArrivalTime(const Time& arrivalTime)
{
    this->arrivalTime = arrivalTime;
}
