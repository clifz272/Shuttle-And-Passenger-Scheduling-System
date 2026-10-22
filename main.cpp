// Name: Yong Jie
// Starts the console program, loads data files, and coordinates the main workflow.

/*
Group 4
Team Members:
Bryan Chow      2500935
Eugene Siew     2502012
Joseph Tang     2501627
Clifton Ng      2503193
Tan Yong Jie    2500413
*/

#include "EntityListController.h"
#include "EntityShow.h"
#include "FileManager.h"
#include "ScheduleAnalyzer.h"
#include "ScheduleShow.h"
#include "StrategyComparer.h"
#include "StrategyRegistry.h"
#include "passengerManager.h"
#include "shuttleManager.h"
#include "routePlanner.h"
#include "UI.h"
#include "validate.h"

#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

int main()
{
    passengerManager passengers;
    shuttleManager shuttles;
    routePlanner planner;

    string folderPath;
    string passengerFile;
    string shuttleFile;
    string message;

    while (true)
    {
        cout << "Enter folder path containing the data files: ";
        cin >> folderPath;
        cout << endl;

        try
        {
            FileValidator::folder(folderPath);
            break;
        }
        catch (const exception& error)
        {
            cout << error.what() << endl;
            cout << endl;
        }
    }

    do
    {
        cout << "Enter passenger file name: ";
        cin >> passengerFile;
        cout << endl;

        message = "";
        if (!FileManager<passenger>::readFile(folderPath, passengerFile, passengers, message))
        {
            cout << message << endl;
        }
        else if (!message.empty())
        {
            cout << message << endl;
        }
    } while (passengers.isEmpty());

    do
    {
        cout << "Enter shuttle file name: ";
        cin >> shuttleFile;
        cout << endl;

        message = "";
        if (!FileManager<shuttle>::readFile(folderPath, shuttleFile, shuttles, message))
        {
            cout << message << endl;
        }
        else if (!message.empty())
        {
            cout << message << endl;
        }
    } while (shuttles.isEmpty());

    bool running = true;
    bool scheduleGenerated = false;

    while (running)
    {
        switch (UI::showMain())
        {
        case 1:
        {
            bool inLists = true;

            while (inLists)
            {
                int listChoice = UI::lists();

                switch (listChoice)
                {
                case 1:
                {
                    bool inShuttle = true;

                    while (inShuttle)
                    {
                        inShuttle = EntityListController<shuttle>::handleAction(
                            shuttles,
                            shuttleManager::menuType(),
                            shuttleManager::idPrefix(),
                            shuttleManager::title(),
                            shuttleManager::locationLabel(),
                            shuttleManager::extraLabel(),
                            folderPath);
                    }

                    break;
                }
                case 2:
                {
                    bool inPassenger = true;

                    while (inPassenger)
                    {
                        inPassenger = EntityListController<passenger>::handleAction(
                            passengers,
                            passengerManager::menuType(),
                            passengerManager::idPrefix(),
                            passengerManager::title(),
                            passengerManager::locationLabel(),
                            passengerManager::extraLabel(),
                            folderPath);
                    }

                    break;
                }
                case 3:
                    inLists = false;
                    break;
                }
            }

            break;
        }

        case 2:
        {
            bool inSchedule = true;

            while (inSchedule)
            {
                int scheduleChoice = UI::scheduleMenu();

                switch (scheduleChoice)
                {
                case 1:
                {
                    vector<unique_ptr<RoutePlanningStrategy>> strategies = StrategyRegistry::getStrategies();

                    if (strategies.empty())
                    {
                        cout << "No route planning strategies available." << endl;
                        break;
                    }

                    vector<string> strategyNames;

                    for (const unique_ptr<RoutePlanningStrategy>& currentStrategy : strategies)
                    {
                        strategyNames.push_back(currentStrategy->getName());
                    }

                    int strategyChoice = UI::strategyMenu(strategyNames);

                    if (strategyChoice == static_cast<int>(strategies.size()) + 1)
                    {
                        break;
                    }

                    planner.generate(shuttles, passengers, *strategies[strategyChoice - 1]);
                    scheduleGenerated = true;

                    if (planner.getSchedules().empty())
                    {
                        cout << "No schedules created." << endl;
                    }
                    else
                    {
                        cout << "Schedule created successfully." << endl;
                    }

                    ScheduleShow::showSummary(
                        planner.getSchedules(),
                        planner.getRemainingShuttles(),
                        planner.getRemainingPassengers());

                    break;
                }
                case 2:
                    ScheduleShow::showSchedules(planner.getSchedules());
                    if (!planner.getSchedules().empty())
                    {
                        ScheduleShow::showSummary(
                            planner.getSchedules(),
                            planner.getRemainingShuttles(),
                            planner.getRemainingPassengers());
                    }
                    break;
                case 3:
                {
                    try
                    {
                        ScheduleValidator::scheduleGenerated(scheduleGenerated);

                        std::vector<UnassignedReason> reasons = ScheduleAnalyzer::getUnassignedReasons(
                            planner.getSchedules(),
                            planner.getRemainingShuttles(),
                            planner.getRemainingPassengers());

                        ScheduleShow::showLeftoversWithReasons(
                            planner.getRemainingShuttles(),
                            reasons);
                    }
                    catch (const exception& error)
                    {
                        cout << error.what() << endl;
                    }

                    break;
                }
                case 4:
                {
                    StrategyComparisonResult comparison = StrategyComparer::compare(shuttles, passengers);

                    ScheduleShow::showStrategyComparison(
                        comparison.strategyStats,
                        comparison.recommendation);

                    break;
                }
                case 5:
                {
                    string scheduleFile;

                    cout << "Enter schedule file name: ";
                    cin >> scheduleFile;

                    message = "";
                    if (FileManager<schedule>::saveFile(folderPath, scheduleFile, planner.getSchedules(), message))
                    {
                        cout << "Schedule file saved." << endl;
                    }
                    else
                    {
                        cout << message << endl;
                    }

                    break;
                }
                case 6:
                    inSchedule = false;
                    break;
                }
            }

            break;
        }

        case 3:
            running = false;
            break;
        }
    }

    return 0;
}
