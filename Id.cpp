// Name: Joseph
// Implements ID validation, comparison, and output formatting.

#include "Id.h"
#include "validate.h"

Id::Id()
{
    value = "";
}

Id::Id(const std::string& inputValue, char prefix)
{
    IdValidator::id(inputValue, prefix);
    value = inputValue;
}

bool Id::isValid() const
{
    return IdValidator::idFormatCheck(value);
}

std::string Id::toString() const
{
    return value;
}

bool Id::operator==(const Id& other) const
{
    return value == other.value;
}

bool Id::operator<(const Id& other) const
{
    return value < other.value;
}

bool Id::operator>(const Id& other) const
{
    return value > other.value;
}

std::ostream& operator<<(std::ostream& out, const Id& id)
{
    out << id.value;
    return out;
}
