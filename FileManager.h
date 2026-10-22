// Name: Clifton
// Declares generic file loading and saving helpers for project records.

#pragma once

#include <exception>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "EntityFactory.h"
#include "EntityList.h"
#include "validate.h"

template <class T>
class FileManager
{
public:
    static bool readFile(const std::string& folderPath, const std::string& fileName, EntityList<T>& list)
    {
        std::string message;
        return readFile(folderPath, fileName, list, message);
    }

    static bool readFile(
        const std::string& folderPath,
        const std::string& fileName,
        EntityList<T>& list,
        std::string& message)
    {
        std::filesystem::path fullPath = std::filesystem::path(folderPath) / fileName;
        message = "";

        if (!FileValidator::folderCheck(folderPath))
        {
            message = "Invalid folder path";
            return false;
        }

        if (!FileValidator::txtCheck(fileName))
        {
            message = "File must end with .txt";
            return false;
        }

        try
        {
            LocationValidator::locFile(folderPath);
        }
        catch (const std::exception& error)
        {
            message = error.what();
            return false;
        }

        std::ifstream file(fullPath);

        if (!file.is_open())
        {
            message = "Unable to open file: " + fullPath.string();
            return false;
        }

        list.clear();

        std::string line;
        int recordCount = 0;

        while (std::getline(file, line))
        {
            if (!FileValidator::rowCheck(line))
            {
                addMessage(message, "Skipping invalid line: " + line);
                continue;
            }

            std::vector<std::string> fields = splitLine(line);
            std::string id = fields[0];

            if (!IdValidator::idUniqueCheck(list, id))
            {
                addMessage(message, "Skipping duplicate ID: " + id);
                continue;
            }

            try
            {
                T item = EntityFactory<T>::create(fields);
                if (list.add(item))
                {
                    recordCount++;
                }
            }
            catch (const std::exception& error)
            {
                addMessage(message, "Skipping invalid data: " + line + " (" + error.what() + ")");
            }
        }

        if (!FileValidator::recordCountCheck(recordCount))
        {
            addMessage(message, "File has no valid records");
            return false;
        }

        return true;
    }

    static bool saveFile(const std::string& folderPath, const std::string& fileName, const EntityList<T>& list)
    {
        std::string message;
        return saveFile(folderPath, fileName, list, message);
    }

    static bool saveFile(
        const std::string& folderPath,
        const std::string& fileName,
        const EntityList<T>& list,
        std::string& message)
    {
        if (list.isEmpty())
        {
            message = "No records to save.";
            return false;
        }

        return saveFile(folderPath, fileName, list.getItems(), message);
    }

    static bool saveFile(const std::string& folderPath, const std::string& fileName, const std::vector<T>& items)
    {
        std::string message;
        return saveFile(folderPath, fileName, items, message);
    }

    static bool saveFile(
        const std::string& folderPath,
        const std::string& fileName,
        const std::vector<T>& items,
        std::string& message)
    {
        std::filesystem::path fullPath = std::filesystem::path(folderPath) / fileName;
        message = "";

        if (!FileValidator::folderCheck(folderPath))
        {
            message = "Invalid folder path";
            return false;
        }

        if (!FileValidator::txtCheck(fileName))
        {
            message = "File must end with .txt";
            return false;
        }

        if (!FileValidator::fileUniqueCheck(folderPath, fileName))
        {
            message = "File already exists. Please use a new file name.";
            return false;
        }

        if (!FileValidator::recordCountCheck(static_cast<int>(items.size())))
        {
            message = "No records to save.";
            return false;
        }

        std::ofstream file(fullPath);

        if (!file.is_open())
        {
            message = "Unable to open file: " + fullPath.string();
            return false;
        }

        for (const T& item : items)
        {
            file << item.toFile() << std::endl;
        }

        file.close();

        return true;
    }

private:
    static std::vector<std::string> splitLine(const std::string& line)
    {
        std::vector<std::string> fields;
        std::string field;
        std::stringstream ss(line);

        while (std::getline(ss, field, ','))
        {
            fields.push_back(field);
        }

        return fields;
    }

    static void addMessage(std::string& message, const std::string& line)
    {
        if (!message.empty())
        {
            message += "\n";
        }

        message += line;
    }
};
