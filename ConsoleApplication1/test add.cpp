#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

bool isDigit(char input) {
	if (input >= 48 && input <= 57)
		return true;
	else return false;
}

int countOfElements(ifstream * file) {
	string t;
	int count = 0;
	while (std::getline(*file, t)) {
		if (t.length() > 1)
			for (unsigned i = 0; i < static_cast<unsigned>(t.length() - 1); i++)
				if (((t[i] == ' ') || (t[i] == '\t')) && (isDigit(t[i + 1])))
					count++;					// Count the number of "spaces/tabs+digits"
		count++;								// count the number of linebreakes
	}
	return count;
}