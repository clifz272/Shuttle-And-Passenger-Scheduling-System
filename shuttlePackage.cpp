// Name: Clifton
// Implements shuttle package validation, normalization, and capacity lookup.

#include "shuttlePackage.h"
#include "validate.h"

using namespace std;

shuttlePackage::shuttlePackage(){
	name = "Small";
	maxSeats = 2;
}

shuttlePackage::shuttlePackage(const string& name) {
	CapacityValidator::shuttlePackage(name);

	this->name = CapacityValidator::normalizePackage(name);

	if (this->name == "Small")
		maxSeats = 2;
	else if (this->name == "Family")
		maxSeats = 5;
	else
		maxSeats = 12;
}

string shuttlePackage::toString() const {
	return name;
}

int shuttlePackage::getMaxSeats() const {
	return maxSeats;
}

bool shuttlePackage::operator==(const shuttlePackage& other) const {
	return name == other.name;
}

bool shuttlePackage::operator<(const shuttlePackage& other) const {
	return maxSeats < other.maxSeats;
}
