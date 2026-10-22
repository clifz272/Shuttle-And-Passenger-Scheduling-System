// Name: Joseph
// Declares the generic collection used by passenger and shuttle managers.

#pragma once

#include <string>
#include <vector>

template <class T>
class EntityList
{
protected:
    std::vector<T> items;

public:
    bool add(const T& item)
    {
        for (const T& existingItem : items)
        {
            if (existingItem.getId().toString() == item.getId().toString())
            {
                return false;
            }
        }

        items.push_back(item);
        return true;
    }

    bool removeById(const std::string& id)
    {
        for (int i = 0; i < static_cast<int>(items.size()); i++)
        {
            if (items[i].getId().toString() == id)
            {
                items.erase(items.begin() + i);
                return true;
            }
        }

        return false;
    }

    bool updateById(const std::string& id, const T& updatedItem)
    {
        for (int i = 0; i < static_cast<int>(items.size()); i++)
        {
            if (items[i].getId().toString() == id)
            {
                items[i] = updatedItem;
                return true;
            }
        }

        return false;
    }

    T* findById(const std::string& id)
    {
        for (T& item : items)
        {
            if (item.getId().toString() == id)
            {
                return &item;
            }
        }

        return nullptr;
    }

    const T* findById(const std::string& id) const
    {
        for (const T& item : items)
        {
            if (item.getId().toString() == id)
            {
                return &item;
            }
        }

        return nullptr;
    }

    std::vector<T>& getItems()
    {
        return items;
    }

    const std::vector<T>& getItems() const
    {
        return items;
    }

    bool isEmpty() const
    {
        return items.empty();
    }

    void clear()
    {
        items.clear();
    }
};
