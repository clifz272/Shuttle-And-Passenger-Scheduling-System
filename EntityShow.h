// Name: Eugene
// Declares reusable console display helpers for entity records.

#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Entity.h"
#include "EntityList.h"

template <class T>
class EntityShow
{
public:
    static void showOne(const T& item)
    {
        std::cout << std::left
            << std::setw(6) << item.getId().toString()
            << std::setw(20) << item.getLocation().toString()
            << std::setw(14) << item.getArrivalTime().toString()
            << item.getExtraValue()
            << std::endl;
    }

    static void showDetails(const Entity& item, const std::string& locationLabel)
    {
        std::cout << std::left
            << std::setw(12) << (item.getType() + " ID:")
            << std::setw(6) << item.getId().toString()
            << std::setw(18) << (locationLabel + ":")
            << std::setw(20) << item.getLocation().toString()
            << std::setw(14) << "Arrival Time:"
            << item.getArrivalTime().toString() << std::endl;
    }

    static void showAll(
        const std::vector<T>& items,
        const std::string& title,
        const std::string& locationLabel,
        const std::string& extraLabel = "")
    {
        if (items.empty())
        {
            std::cout << "No records found." << std::endl;
            return;
        }

        std::string displayExtraLabel = extraLabel.empty()
            ? items[0].getExtraLabel()
            : extraLabel;

        std::cout << "--" << title << "--" << std::endl;
        std::cout << std::left
            << std::setw(6) << "ID"
            << std::setw(20) << locationLabel
            << std::setw(14) << "Arrival Time";

        if (!displayExtraLabel.empty())
        {
            std::cout << displayExtraLabel;
        }

        std::cout << std::endl;

        for (const T& item : items)
        {
            showOne(item);
        }

        std::cout << std::endl;
    }

    static void showAll(
        const EntityList<T>& list,
        const std::string& title,
        const std::string& locationLabel,
        const std::string& extraLabel = "")
    {
        showAll(list.getItems(), title, locationLabel, extraLabel);
    }

    static bool showById(const EntityList<T>& list, const std::string& id)
    {
        const T* item = list.findById(id);

        if (item == nullptr)
        {
            return false;
        }

        showOne(*item);
        return true;
    }
};
