// Name: Clifton
// Declares the shuttle package value object and package capacity rules.

#pragma once

#include <string>

class shuttlePackage
{
private:
	std::string name;
	int maxSeats;

public:
	shuttlePackage();
	shuttlePackage(const std::string& name);

	std::string toString() const;
	int getMaxSeats() const;

	bool operator==(const shuttlePackage& other) const;
	bool operator<(const shuttlePackage& other) const;
};

