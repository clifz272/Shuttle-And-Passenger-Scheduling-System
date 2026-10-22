// Name: Bryan
// Declares factories that convert text fields into validated domain objects.

#pragma once

#include <string>
#include <vector>

#include "passenger.h"
#include "shuttle.h"

template <class T>
class EntityFactory;

template <>
class EntityFactory<passenger>
{
public:
    static passenger create(const std::vector<std::string>& fields);
};

template <>
class EntityFactory<shuttle>
{
public:
    static shuttle create(const std::vector<std::string>& fields);
};
