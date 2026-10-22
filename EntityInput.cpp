// Name: Clifton
// Implements console prompts that collect raw entity input fields.

#include "EntityInput.h"

#include <iostream>

std::string EntityInput::readId(const std::string& prompt)
{
    std::string id;

    std::cout << prompt;
    std::cin >> id;

    return id;
}

EntityInputData EntityInput::readItem(const std::string& locationLabel, const std::string& extraLabel)
{
    EntityInputData input;

    std::cout << "Enter ID: ";
    std::cin >> input.id;
    std::cout << "Enter " << locationLabel << ": ";
    std::cin >> input.location;
    std::cout << "Enter arrival time: ";
    std::cin >> input.arrivalTime;
    std::cout << "Enter " << extraLabel << ": ";
    std::cin >> input.extra;

    return input;
}

EntityInputData EntityInput::readUpdatedItem(const std::string& locationLabel, const std::string& extraLabel)
{
    EntityInputData input;

    std::cout << "Enter new ID: ";
    std::cin >> input.id;
    std::cout << "Enter new " << locationLabel << ": ";
    std::cin >> input.location;
    std::cout << "Enter new arrival time: ";
    std::cin >> input.arrivalTime;
    std::cout << "Enter new " << extraLabel << ": ";
    std::cin >> input.extra;

    return input;
}
