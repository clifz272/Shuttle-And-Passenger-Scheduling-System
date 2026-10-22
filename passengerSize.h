// Name: Joseph
// Declares the passenger size value object.

#pragma once
#include <string>

class passengerSize
{
private:
	int value;

public:
	passengerSize();
	passengerSize(int value);

	int getValue() const;
	std::string toString() const;

	bool operator<(const passengerSize& other) const;
};

