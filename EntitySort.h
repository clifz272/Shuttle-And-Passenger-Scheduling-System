// Name: Yong Jie
// Declares reusable sorting helpers for entity lists.

#pragma once

#include <algorithm>
#include <vector>

#include "EntityList.h"

template <class T>
class EntitySorter
{
public:
    static void sortId(std::vector<T>& items, bool ascending)
    {
        std::sort(items.begin(), items.end(),
            [ascending](const T& a, const T& b)
            {
                return ascending ? a.getId() < b.getId()
                    : a.getId() > b.getId();
            });
    }

    static bool sortId(EntityList<T>& list, bool ascending)
    {
        if (list.isEmpty())
        {
            return false;
        }

        sortId(list.getItems(), ascending);
        return true;
    }

    static void sortTime(std::vector<T>& items, bool ascending)
    {
        std::sort(items.begin(), items.end(),
            [ascending](const T& a, const T& b)
            {
                return ascending ? a.getArrivalTime() < b.getArrivalTime()
                    : b.getArrivalTime() < a.getArrivalTime();
            });
    }

    static bool sortTime(EntityList<T>& list, bool ascending)
    {
        if (list.isEmpty())
        {
            return false;
        }

        sortTime(list.getItems(), ascending);
        return true;
    }

    static void sortLocation(std::vector<T>& items, bool ascending)
    {
        std::sort(items.begin(), items.end(),
            [ascending](const T& a, const T& b)
            {
                return ascending ? a.getLocation() < b.getLocation()
                    : b.getLocation() < a.getLocation();
            });
    }

    static bool sortLocation(EntityList<T>& list, bool ascending)
    {
        if (list.isEmpty())
        {
            return false;
        }

        sortLocation(list.getItems(), ascending);
        return true;
    }

    static void sortExtra(std::vector<T>& items, bool ascending)
    {
        std::sort(items.begin(), items.end(),
            [ascending](const T& a, const T& b)
            {
                return ascending ? a.getExtraSortValue() < b.getExtraSortValue()
                    : b.getExtraSortValue() < a.getExtraSortValue();
            });
    }

    static bool sortExtra(EntityList<T>& list, bool ascending)
    {
        if (list.isEmpty())
        {
            return false;
        }

        sortExtra(list.getItems(), ascending);
        return true;
    }
};
