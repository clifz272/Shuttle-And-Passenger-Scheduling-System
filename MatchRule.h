// Name: Bryan
// Declares shared passenger-to-shuttle matching rules.

#pragma once

class passenger;
class shuttle;

class MatchRule
{
public:
    static bool locationMatch(const shuttle& currentShuttle, const passenger& currentPassenger);
    static bool timeMatch(const shuttle& currentShuttle, const passenger& currentPassenger);
    static bool seatMatch(int remainingSeats, const passenger& currentPassenger);
    static bool shuttleOperatingTimeMatch(const shuttle& currentShuttle);
    static bool canAssign(const shuttle& currentShuttle, int remainingSeats, const passenger& currentPassenger);
};
