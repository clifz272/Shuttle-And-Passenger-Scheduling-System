// Name: Bryan
// Declares controller helpers that connect list menu actions to services.

#pragma once

#include "EntityCrudService.h"
#include "EntityInput.h"
#include "EntityList.h"
#include "EntityShow.h"
#include "EntitySort.h"
#include "FileManager.h"
#include "UI.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

template <class T>
class EntityListController
{
public:
    static void addItem(
        EntityList<T>& list,
        char idPrefix,
        const std::string& locationLabel,
        const std::string& extraLabel)
    {
        EntityInputData input = EntityInput::readItem(locationLabel, extraLabel);
        OperationResult result = EntityCrudService<T>::add(list, idPrefix, input);
        std::cout << result.message << std::endl;
    }

    static void deleteItem(EntityList<T>& list, char idPrefix)
    {
        std::string id = EntityInput::readId("Enter ID to delete: ");
        OperationResult result = EntityCrudService<T>::remove(list, idPrefix, id);
        std::cout << result.message << std::endl;
    }

    static void editItem(
        EntityList<T>& list,
        char idPrefix,
        const std::string& locationLabel,
        const std::string& extraLabel)
    {
        std::string currentId = EntityInput::readId("Enter ID to edit: ");
        EntityInputData input = EntityInput::readUpdatedItem(locationLabel, extraLabel);
        OperationResult result = EntityCrudService<T>::update(list, idPrefix, currentId, input);
        std::cout << result.message << std::endl;
    }

    static void sortItems(
        EntityList<T>& list,
        const std::string& locationLabel,
        const std::string& extraLabel)
    {
        if (list.isEmpty())
        {
            std::cout << "No records to sort." << std::endl;
            return;
        }

        UI::sort1(locationLabel, extraLabel);
        int field = UI::readChoice(1, 5);

        if (field == 5)
        {
            return;
        }

        UI::sort2();
        int order = UI::readChoice(1, 3);

        if (order == 3)
        {
            return;
        }

        bool ascending = order == 1;

        switch (field)
        {
        case 1:
            EntitySorter<T>::sortId(list, ascending);
            break;
        case 2:
            EntitySorter<T>::sortLocation(list, ascending);
            break;
        case 3:
            EntitySorter<T>::sortTime(list, ascending);
            break;
        case 4:
            EntitySorter<T>::sortExtra(list, ascending);
            break;
        }

        std::cout << "Records sorted." << std::endl;
    }

    static void saveItems(const std::string& folderPath, const EntityList<T>& list)
    {
        std::string fileName;
        std::string message;

        std::cout << "Enter new file name to save: ";
        std::cin >> fileName;

        try
        {
            FileValidator::txt(fileName);
        }
        catch (const std::exception& error)
        {
            std::cout << error.what() << std::endl;
            return;
        }

        if (FileManager<T>::saveFile(folderPath, fileName, list, message))
        {
            std::cout << "File saved." << std::endl;
        }
        else
        {
            std::cout << message << std::endl;
        }
    }

    static void searchItem(
        const EntityList<T>& list,
        char idPrefix,
        const std::string& locationLabel,
        const std::string& extraLabel)
    {
        std::string id = EntityInput::readId("Enter ID to search: ");

        try
        {
            IdValidator::id(id, idPrefix);

            const T* item = list.findById(id);

            if (item == nullptr)
            {
                std::cout << "ID not found." << std::endl;
                return;
            }

            EntityShow<T>::showAll(
                std::vector<T>{ *item },
                "Search Result",
                locationLabel,
                extraLabel);
        }
        catch (const std::exception& error)
        {
            std::cout << error.what() << std::endl;
        }
    }

    static bool handleAction(
        EntityList<T>& list,
        int listType,
        char idPrefix,
        const std::string& title,
        const std::string& locationLabel,
        const std::string& extraLabel,
        const std::string& folderPath)
    {
        int action = UI::shuttlePassenger(listType);

        switch (action)
        {
        case 1:
            addItem(list, idPrefix, locationLabel, extraLabel);
            return true;
        case 2:
            deleteItem(list, idPrefix);
            return true;
        case 3:
            editItem(list, idPrefix, locationLabel, extraLabel);
            return true;
        case 4:
            sortItems(list, locationLabel, extraLabel);
            return true;
        case 5:
            EntityShow<T>::showAll(list, title, locationLabel, extraLabel);
            return true;
        case 6:
            searchItem(list, idPrefix, locationLabel, extraLabel);
            return true;
        case 7:
            saveItems(folderPath, list);
            return true;
        case 8:
            return false;
        }

        return true;
    }
};
