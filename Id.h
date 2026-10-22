// Name: Joseph
// Declares the ID value object used by passengers and shuttles.

#pragma once

#include <ostream>
#include <string>

class Id
{
    friend std::ostream& operator<<(std::ostream& out, const Id& id);

private:
    std::string value;

public:
    Id();
    Id(const std::string& value, char prefix);

    bool isValid() const;
    std::string toString() const;

    bool operator==(const Id& other) const;
    bool operator<(const Id& other) const;
    bool operator>(const Id& other) const;
};
