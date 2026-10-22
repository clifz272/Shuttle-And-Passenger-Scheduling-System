// Name: Joseph
// Implements passenger size validation, formatting, and comparison.

#include "passengerSize.h"
#include "validate.h"

using namespace std;

passengerSize::passengerSize()
{
	value = 1;
}

passengerSize::passengerSize(int value) {
	CapacityValidator::passengerSize(value);
	this->value = value;
}

int passengerSize::getValue() const
{
	return value;
}

string passengerSize::toString() const {
	return to_string(value);
}

bool passengerSize::operator<(const passengerSize& other) const {
	return value < other.value;
}
