#include <iostream>
using namespace std;

bool choiseNextAction() {
	cout << "\nDo you want to repeat (y/n)?" << "\n>> ";
	char input;
	while (true) {
		cin >> input;
		if (input == 'y' || input == 'Y')
			return true;
		else if (input == 'n' || input == 'N')
			return false;
		else
			cout << "Wrong input! Try again...\n>> ";
	}
}