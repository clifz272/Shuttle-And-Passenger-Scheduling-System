// Name: Bryan
// Implements console menus and validated menu selection input.

#include "UI.h"

#include <iostream>
#include <string>

#include "validate.h"

using namespace std;

int UI::readChoice(int min, int max)
{
	string input;

	while (true)
	{
		cin >> input;

		if (!MenuValidator::choiceTextCheck(input, min, max))
		{
			cout << "\nPlease select a valid number: ";
		}
		else
		{
			cout << endl;
			return stoi(input);
		}
	}
}

int UI::showMain()
{
	cout << endl;
	cout << "======= Main Menu ========" << endl;
	cout << "1. Lists" << endl;
	cout << "2. Schedule" << endl;
	cout << "3. Exit" << endl;
	cout << "Select a number: ";

	return readChoice(1, 3);
}

int UI::lists()
{
	cout << endl;
	cout << "======= Lists ========" << endl;
	cout << "1. Shuttle" << endl;
	cout << "2. Passenger" << endl;
	cout << "3. Back" << endl;
	cout << "Select a number: ";

	return readChoice(1, 3);
}

int UI::shuttlePassenger(int sel)
{
	cout << endl;

	if (sel == 1)
	{
		cout << "======= Shuttle ========" << endl;
	}
	else if (sel == 2)
	{
		cout << "======= Passenger ========" << endl;
	}

	cout << "1. Add" << endl;
	cout << "2. Delete" << endl;
	cout << "3. Edit" << endl;
	cout << "4. Sort" << endl;
	cout << "5. Show list" << endl;
	cout << "6. Search" << endl;
	cout << "7. Save" << endl;
	cout << "8. Back" << endl;
	cout << "Select a number: ";

	return readChoice(1, 8);
}

int UI::scheduleMenu()
{
	cout << endl;
	cout << "======= Schedule ========" << endl;
	cout << "1. Generate Schedule" << endl;
	cout << "2. Show Schedule" << endl;
	cout << "3. Show leftovers and unassigned reasons" << endl;
	cout << "4. Compare strategies" << endl;
	cout << "5. Save" << endl;
	cout << "6. Back" << endl;
	cout << "Select a number: ";

	return readChoice(1, 6);
}

int UI::strategyMenu(const vector<string>& strategyNames)
{
	cout << endl;
	cout << "======= Route Planning Strategy ========" << endl;

	for (int i = 0; i < static_cast<int>(strategyNames.size()); i++)
	{
		cout << i + 1 << ". " << strategyNames[i] << endl;
	}

	int backChoice = static_cast<int>(strategyNames.size()) + 1;
	cout << backChoice << ". Back" << endl;
	cout << "Select a number: ";

	return readChoice(1, backChoice);
}

void UI::sort1(const string& locationLabel, const string& extraLabel)
{
	cout << endl;
	cout << "---- Sort ----" << endl;
	cout << "1. ID" << endl;
	cout << "2. " << locationLabel << endl;
	cout << "3. Arrival Time" << endl;
	cout << "4. " << extraLabel << endl;
	cout << "5. Back" << endl;
	cout << "Select field: ";
}

void UI::sort2()
{
	cout << endl;
	cout << "---- Sort Order ----" << endl;
	cout << "1. Ascending" << endl;
	cout << "2. Descending" << endl;
	cout << "3. Back" << endl;
	cout << "Select order: ";
}
