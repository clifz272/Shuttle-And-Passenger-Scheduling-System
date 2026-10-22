// Name: Yong Jie
// Declares the Destination value object for valid locations.

#pragma once
#include <string>
#include <ostream>

class Destination
{
    friend std::ostream& operator<<(std::ostream& out, const Destination& dest);
private:
    std::string name;

public:
    Destination();
    Destination(const std::string& name);

    bool isValid() const;
    std::string toString() const;

    bool operator==(const Destination& dest) const;
    bool operator<(const Destination& dest) const;
};

