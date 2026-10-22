// Name: Clifton
// Declares the schedule model that links one shuttle with assigned passengers.

#pragma once

#include <string>
#include <vector>

#include "Entity.h"
#include "passenger.h"
#include "shuttle.h"

class schedule
{
private:
	shuttle assignedShuttle;
	std::vector<passenger> assignedPassengers;
	int usedSeats;
	int remainingSeats;

public:
	schedule();
	schedule(const shuttle& sh);
	bool canAddPassenger(const passenger& p) const;
	bool addPassenger(const passenger& p);

	std::string toFile() const;
	const shuttle& getAssignedShuttle() const;
	const std::vector<passenger>& getAssignedPassengers() const;
	int getUsedSeats() const;
	int getRemainingSeats() const;
};
