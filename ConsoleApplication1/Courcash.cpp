#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

const int numOfStudentFields = 7;
struct student {
	string fullname;
	int group;
	int id;
	char sex;
	string formOfEducation;
	int grades[8];
	struct changedOn;
};

struct changedOn {
	string dayOfWeek;
	string month;
	int dayOfMonth;
	struct time;
	int year;
};

struct time {
	int hour;
	int minute;
	int second;
};

void practicalWork1();

int countOfRecords(ifstream *);
student readStudentFromFile(ifstream *);
bool checkFullname(string);
bool isLetter(char);

bool choiseNextAction();

int main() {
	while (true) {
		system("CLS");
		cout << "Practical works: \n"
			<< "\t1)  \n"
			<< "Enter the number of practical work or enter 0 for close the program... \n>> ";
		int input;
		cin >> input;
		switch (input) {
		case 1:
			system("CLS");
			practicalWork1();
			break;
		default:
			goto Exit;
		}
	}
Exit:
	cout << "\nClosing the program... \n";
	system("pause");
	return 0;
}

void practicalWork1() {
	cout << "Solution of task \"Working with structures\". \n\n"
		<< "Task 0. Reading text file. \n";

	do {
		ifstream file;
		do {
			cout << "\nEnter the path to the file. \n"
				<< "Only english words in the file and path! Example: C:\\anime\\students.txt \n>> ";
			string path;
			cin.ignore(32767, '\n');
			getline(cin, path);
			file.open(path);
			if (!file.is_open()) {
				cout << "Error opening file! Please restart the program! \n";
				continue;
			}

			ifstream *pfile = &file;
			int numberOfRecords = countOfRecords(pfile);
			if (!(numberOfRecords % numOfStudentFields == 0)) {
				cout << "Error! Invalid number of lines in the file. Must be a multiple " << numOfStudentFields << ".\n";
				continue;
			}
			numberOfRecords /= numOfStudentFields;

			file.close();
			file.open(path);
			struct student * students = new student[numberOfRecords];
			try {
				for (int i = 0; i < numberOfRecords; i++) {
					students[i] = readStudentFromFile(pfile);
				}
			}
			catch (const char* msg) {
				cout << msg;
				continue;
			}
		} while (!file.is_open());

		file.close();
	} while (choiseNextAction());
}

int countOfRecords(ifstream * file) {
	string t;
	int count = 0;
	while (getline(*file, t)) {
		count++;
	}
	return count;
}

struct student readStudentFromFile(ifstream * file) {
	struct student newStudent;
	string input;

	getline(*file, input);
	if (checkFullname) // first option of check
		newStudent.fullname = input;

	getline(*file, input);
	regex mask("^[0-9]*$"); // second option of check
	if (!(regex_search(input, mask)))
		throw "Error! Invalid number of group. Format example: \"2284\". \n";

}

bool checkFullname(string str) {
	int countOfSpaces = 0;
	for (int i = 0; i < str.length(); i++) {
		if (isLetter(str[i]))
			continue;
		else if ((str[i] == ' ') && (countOfSpaces < 2))
				countOfSpaces++;
		else {
			return false;
			throw "Error! Invalid students Fullname. Format example: \"Ivanov Ivan Ivanovich\". \n";
		}
	}
	return true;
}

bool isLetter(char c) {
	if (
		((c >= 65) && (c <= 90))
		|| ((c >= 97) && (c <= 122))
		)
		return true;
	else
		return false;
}

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