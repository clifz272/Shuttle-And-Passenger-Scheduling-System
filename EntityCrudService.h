// Name: Bryan
// Declares reusable add, delete, and update operations for entity lists.

#pragma once

#include "EntityFactory.h"
#include "EntityInput.h"
#include "EntityList.h"
#include "OperationResult.h"
#include "validate.h"

#include <exception>
#include <string>

template <class T>
class EntityCrudService
{
public:
    static OperationResult add(EntityList<T>& list, char idPrefix, const EntityInputData& input)
    {
        try
        {
            IdValidator::id(input.id, idPrefix);

            if (!IdValidator::idUniqueCheck(list, input.id))
            {
                return { false, "ID already exists." };
            }

            T item = EntityFactory<T>::create({ input.id, input.location, input.arrivalTime, input.extra });

            if (!list.add(item))
            {
                return { false, "ID already exists." };
            }

            return { true, "Record added." };
        }
        catch (const std::exception& error)
        {
            return { false, error.what() };
        }
    }

    static OperationResult remove(EntityList<T>& list, char idPrefix, const std::string& id)
    {
        try
        {
            IdValidator::id(id, idPrefix);

            if (!list.removeById(id))
            {
                return { false, "ID not found." };
            }

            return { true, "Record deleted." };
        }
        catch (const std::exception& error)
        {
            return { false, error.what() };
        }
    }

    static OperationResult update(
        EntityList<T>& list,
        char idPrefix,
        const std::string& currentId,
        const EntityInputData& input)
    {
        try
        {
            IdValidator::id(currentId, idPrefix);

            if (list.findById(currentId) == nullptr)
            {
                return { false, "ID not found." };
            }

            IdValidator::id(input.id, idPrefix);

            if (input.id != currentId && !IdValidator::idUniqueCheck(list, input.id))
            {
                return { false, "ID already exists." };
            }

            T updatedItem = EntityFactory<T>::create({ input.id, input.location, input.arrivalTime, input.extra });

            if (!list.updateById(currentId, updatedItem))
            {
                return { false, "ID not found." };
            }

            return { true, "Record updated." };
        }
        catch (const std::exception& error)
        {
            return { false, error.what() };
        }
    }
};
