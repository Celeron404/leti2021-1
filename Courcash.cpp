#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

const int numOfStudentFields = 7;
struct student {
	string fullName;
	int group;
	int id;
	char sex;
	string educationForm;
	short grades[8];
	date changedOn;
};

struct date {
	string dayOfWeek;
	string month;
	int dayOfMonth;
	timeHM time;
	int year;
};

struct timeHM {
	int hour;
	int minute;
	int second;
};

void practicalWork1();

int countOfRecords(ifstream *);
student readStudentFromFile(ifstream *);
student readStudentFromKeyboard();
bool addStudentToFile(ofstream*, student);
bool isFullName(string);
bool isLetter(char);
bool isDay(string);
void printDate(date);

bool choiseNextAction();

int main() {
	while (true) {
		cout << "Practical works: \n"
			<< "\t1) \"Structures\" \n"
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

	system("CLS");
	ifstream file;
	string path;
	int numberOfRecords;
	struct student * students;
	do {
		cout << "\nEnter the path to the file. \n"
			<< "Only english words in the file and path! Example: C:\\anime\\students.txt \n>> ";
		cin.ignore(32767, '\n');
		getline(cin, path);
		file.open(path);
		if (!file.is_open()) {
			cout << "Error opening file! Please restart the program! \n";
			continue;
		}

		ifstream *pfile = &file;
		numberOfRecords = countOfRecords(pfile);
		if (!(numberOfRecords % numOfStudentFields == 0)) {
			cout << "Error! Invalid number of lines in the file. Must be a multiple " << numOfStudentFields << ".\n";
			continue;
		}
		numberOfRecords /= numOfStudentFields;

		file.close();
		file.open(path);
		students = new student[numberOfRecords];
		try {
			for (int i = 0; i < numberOfRecords; i++) {
				students[i] = readStudentFromFile(pfile);
			}
			cout << "Successfully reading file! \n";
		}
		catch (const char* msg) {
			cout << msg;
			continue;
		}
	} while (!file.is_open());

	do {
		cout << "Operations. \n"
			<< "1) Add student \n"
			<< "2) Change exist student \n"
			<< "3) Display all students \n"
			<< "4) Display all students from the group \n"
			<< "5) Display rating \n"
			<< "6) Display number of male and female students \n"
			<< "7) Display the number of students who will receive the scholarship \n"
			<< "8) Display the number of students who will not recieve the scholarship; have good and excellent grades; have only excellent grades \n"
			<< "9) Display all students with the entered number in the group \n"
			<< "10) Display all students from the entered date \n>> ";
		int input;
		cin >> input;
		switch (input) {
		case 1:
			do {
				cout << "";

			} while (choiseNextAction());

			break;
		case 2:

			break;
		case 3:
			for (int i = 0; i < numberOfRecords; i++) {
				cout << students[i].fullName << endl;
				cout << students[i].group << endl;
				cout << students[i].id << endl;
				cout << students[i].sex << endl;
				cout << students[i].educationForm << endl;
				cout << students[i].grades << endl;
				printDate(students[i].changedOn);
			}

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		case 7:

			break;
		case 8:

			break;
		case 9:

			break;
		case 10:
			do {
				cout << "10. Displaying all students from the entered date. Options: \n"
					<< "1) All day \n"
					<< "2) Only before noon \n"
					<< "3) Only after noon \n>> ";
				int input1;
				cin >> input;
				cout << endl;
				switch (input1) {
				case 1:

					break;
				case 2:

					break;
				case 3:

					break;
				default:
					cout << "Error! Invalid input. \n";
					break;
				}

			} while (choiseNextAction());
			break;
		default:
			cout << "Error! Invalid input. \n";
			break;
		}
	} while (choiseNextAction());

	file.close();
}

int countOfRecords(ifstream * file) {
	string t;
	int count = 0;
	while (getline(*file, t)) {
		count++;
	}
	return count;
}

student readStudentFromFile(ifstream * file) {
	struct student newStudent;
	string input;

	getline(*file, input);
	if (isFullName(input)) // first option of check
		newStudent.fullName = input;
	else
		throw "Error! Invalid students FullName. Format example: \"Ivanov Ivan Ivanovich\", only letters and only 3 words. \n";

	getline(*file, input);
	regex mask("^[0-9]*$"); // second option of check
	if (regex_search(input, mask))
		newStudent.group = stoi(input);
	else
		throw "Error! Invalid number of group format. Example: \"2284\", only numbers. \n";

	getline(*file, input);
	if (regex_search(input, mask))
		newStudent.id = stoi(input);
	else
		throw "Error! Invalid student id format. Example: \"12\", only numbers. \n";

	getline(*file, input);
	regex mask("^[MF|mf]{1}$");
	if (regex_search(input, mask))
		newStudent.sex = input[0];
	else
		throw "Error! Invalid student sex format. Example: only \"M\" or \"F\". \n";

	getline(*file, input);
	regex mask("^[A-Za-z]*$");
	if (regex_search(input, mask))
		newStudent.educationForm = input;
	else
		throw "Error! Invalid form of education format. Example: \"distance\", without numbers and another characters. \n";

	getline(*file, input);
	regex mask("^[0-5]{1} {1}[0-5]{1} {1}[0-5]{1} {1}[0-5]{1} {1}[0-5]{1} {1}[0-5]{1} {1}[0-5]{1} {1}[0-5]{1}");
	if (regex_search(input, mask))
		for (int i = 0; i <= 14; i += 2)
			newStudent.grades[i] = (int)input[i] - 48;
	else
		throw "Error! Invalid grades format. Example: \"3 4 2 5 5 3 4 0 \", grade can be only 0-5, where \"0\" is empty grade. \n";

	getline(*file, input);
	regex mask("^[A-Za-z]{3} {1}[A-Za-z]{3} {1}[0-9]{2} {1}[0-9]{2}:{1}[0-9]{2}:{1}[0-9]{2} {1}[0-9]{4}$");
	if (!regex_search(input, mask))
		throw "Error! Invalid date format. Example: \"Mon Feb 22 12:00:01 2021\". \n";

	string sub = input.substr(0, 3); // Here and below individual cases of incorrect date are checked 
	if (isDay(sub))
		newStudent.changedOn.dayOfWeek = sub;
	else
		throw "Error! Invalid day format. Example: \"Mon\" \"Tue\", \"Wed\" etc. \n";
	
	sub = input.substr(4, 3);
	if (isWeek(sub))
		newStudent.changedOn.month = sub;
	else
		throw "Error! Invalid day format. Example: \"Jan\" \"Feb\", \"Mar\" etc. \n";

	sub = input.substr(8, 2);
	int intForCheck = stoi(sub);
	if (intForCheck >= 1 && intForCheck <= 31)
		newStudent.changedOn.dayOfMonth = intForCheck;
	else
		throw "Error! Invalud day of month format. Example: \"18\", 1-31. \n";
	
	sub = input.substr(11, 2);
	intForCheck = stoi(sub);
	if (intForCheck >= 0 && intForCheck <= 24)
		newStudent.changedOn.time.hour = intForCheck;
	else
		throw "Error! Invalud hour format. Example: \"13\", 00-23. \n";

	sub = input.substr(14, 2);
	intForCheck = stoi(sub);
	if (intForCheck >= 0 && intForCheck <= 59)
		newStudent.changedOn.time.minute = intForCheck;
	else
		throw "Error! Invalud minute format. Example: \"29\", 00-59. \n";

	sub = input.substr(17, 2);
	intForCheck = stoi(sub);
	if (intForCheck >= 0 && intForCheck <= 59)
		newStudent.changedOn.time.second = intForCheck;
	else
		throw "Error! Invalud second format. Example: \"29\", 00-59. \n";

	newStudent.changedOn.year = stoi(input.substr(20, 4));

	return newStudent;
}

student readStudentFromKeyboard() {
	struct student newStudent;
	string input;

	bool inputIsCorrect = false;
	do {
		cout << "Enter full fame. Format example: \"Ivanov Ivan Ivanovich\", only letters and only 3 words. \n>> ";
		getline(cin, input);
		if (isFullName(input)) { // first option of check
			newStudent.fullName = input;
			inputIsCorrect = true;
		}
		else {
			inputIsCorrect = false;
			cout << "Error! Invalid students full fame. Format example: \"Ivanov Ivan Ivanovich\", only letters and only 3 words. \n";
		}
	} while (!inputIsCorrect);

	do {
		cout << "Enter number of group. Format example: \"2284\", only numbers. \n>> ";
		getline(cin, input);
		regex mask("^[0-9]*$"); // second option of check
		if (regex_search(input, mask)) {
			newStudent.group = stoi(input);
			inputIsCorrect = true;
		}
		else
			cout << "Error! Invalid number of group format. Example: \"2284\", only numbers. \n";
	} while (!inputIsCorrect);

	do {
		cout << "Enter student id. Format example: \"12\", only numbers. \n>> ";
		getline(cin, input);
		regex mask("^[0-9]*$");
		if (regex_search(input, mask)) {
			newStudent.id = stoi(input);
			inputIsCorrect = true;
		}
		else
			cout << "Error! Invalid student id format. Example: \"12\", only numbers. \n";
	} while (!inputIsCorrect);

	do {
		cout << "Enter student sex. Format example: only \"M\" or \"F\". \n>> ";
		getline(cin, input);
		regex mask("^[MF|mf]{1}$");
		if (regex_search(input, mask)) {
			newStudent.sex = input[0];
			inputIsCorrect = true;
		}
		else
			cout << "Error! Invalid student sex format. Example: only \"M\" or \"F\". \n";
	} while (!inputIsCorrect);

	do {
		cout << "Enter form of education. Format example: \"distance\", without numbers and another characters. \n>> ";
		getline(cin, input);
		regex mask("^[A-Za-z]*$");
		if (regex_search(input, mask)) {
			newStudent.educationForm = input;
			inputIsCorrect = true;
		}
		else
			cout << "Error! Invalid form of education format. Example: \"distance\", without numbers and another characters. \n";
	} while (!inputIsCorrect);

	do {
		cout << "Enter grades. Format example: \"3 4 2 5 5 3 4 0 \", only 8 grades, grade can be only 0-5, where \"0\" is empty grade. \n>> ";
		getline(cin, input);
		regex mask("^[0-5]{1} {1}[0-5]{1} {1}[0-5]{1} {1}[0-5]{1} {1}[0-5]{1} {1}[0-5]{1} {1}[0-5]{1} {1}[0-5]{1}");
		if (regex_search(input, mask)) {
			for (int i = 0; i <= 14; i += 2)
				newStudent.grades[i] = (int)input[i] - 48;
			inputIsCorrect = true;
		}
		else
			cout << "Error! Invalid grades format. Example: \"3 4 2 5 5 3 4 0 \", only 8 grades, grade can be only 0-5, where \"0\" is empty grade. \n";
	} while (!inputIsCorrect);

	do {
		try {
			cout << "Enter date. Format example: \"Mon Feb 22 12:00:01 2021\". Be careful, strict compliance with the format is required! \n>> ";
			getline(cin, input);
			regex mask("^[A-Za-z]{3} {1}[A-Za-z]{3} {1}[0-9]{2} {1}[0-9]{2}:{1}[0-9]{2}:{1}[0-9]{2} {1}[0-9]{4}$");
			if (!regex_search(input, mask))
				throw "Error! Invalid date format. Example: \"Mon Feb 22 12:00:01 2021\". \n";

			string sub = input.substr(0, 3); // Here and below individual cases of incorrect date are checked 
			if (isDay(sub))
				newStudent.changedOn.dayOfWeek = sub;
			else
				throw "Error! Invalid day format. Example: \"Mon\" \"Tue\", \"Wed\" etc. \n";


			sub = input.substr(4, 3);
			if (isWeek(sub))
				newStudent.changedOn.month = sub;
			else
				throw "Error! Invalid day format. Example: \"Jan\" \"Feb\", \"Mar\" etc. \n";

			sub = input.substr(8, 2);
			int intForCheck = stoi(sub);
			if (intForCheck >= 1 && intForCheck <= 31)
				newStudent.changedOn.dayOfMonth = intForCheck;
			else
				throw "Error! Invalud day of month format. Example: \"18\", 1-31. \n";

			sub = input.substr(11, 2);
			intForCheck = stoi(sub);
			if (intForCheck >= 0 && intForCheck <= 24)
				newStudent.changedOn.time.hour = intForCheck;
			else
				throw "Error! Invalud hour format. Example: \"13\", 00-23. \n";

			sub = input.substr(14, 2);
			intForCheck = stoi(sub);
			if (intForCheck >= 0 && intForCheck <= 59)
				newStudent.changedOn.time.minute = intForCheck;
			else
				throw "Error! Invalud minute format. Example: \"29\", 00-59. \n";

			sub = input.substr(17, 2);
			intForCheck = stoi(sub);
			if (intForCheck >= 0 && intForCheck <= 59)
				newStudent.changedOn.time.second = intForCheck;
			else
				throw "Error! Invalud second format. Example: \"29\", 00-59. \n";

			newStudent.changedOn.year = stoi(input.substr(20, 4));
			inputIsCorrect = true;
		}
		catch (const char* msg) {
			cout << msg;
			continue;
		}
	} while (!inputIsCorrect);

	return newStudent;
}

/*bool addStudentToFile(ofstream * file, student input) {
		
}*/

bool isFullName(string str) {
	int countOfSpaces = 0;
	for (int i = 0; i < str.length(); i++) {
		if (isLetter(str[i]))
			continue;
		else if ((str[i] == ' ') && (countOfSpaces < 2))
				countOfSpaces++;
		else {
			return false;
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

bool isDay(string str) {
	if (str == "Mon" || "mon" || "Tue" || "tue"|| "Wed" || "wed"|| "Thu" || "thu"|| "Fri" || "fri"|| "Sat" || "sat"|| "Sun" || "sun"
		)
		return true;
	else
		return false;
}

void printDate(date input) {
	cout << input.dayOfWeek << ' ' << input.month << ' ' << input.dayOfMonth << ' ' << input.time.hour << ':' << input.time.minute << ':' << input.time.second << ' ' << input.year << endl;
}

/*bool isDay(string str) {
	if (str == "Mon" || str == "mon"
		|| str == "Tue" || str == "tue"
		|| str == "Wed" || str == "wed"
		|| str == "Thu" || str == "thu"
		|| str == "Fri" || str == "fri"
		|| str == "Sat" || str == "sat"
		|| str == "Sun" || str == "sun"
		)
		return true;
	else
		return false;
}*/

/*bool isWeek(string str) {
	if (str == "Jan" || str == "jan"
		|| str == "Feb" || str == "feb"
		|| str == "Mar" || str == "mar"
		|| str == "Apr" || str == "apr"
		|| str == "May" || str == "may"
		|| str == "Jun" || str == "jun"
		|| str == "Jul" || str == "jul"
		|| str == "Aug" || str == "aug"
		|| str == "Sep" || str == "sep"
		|| str == "Oct" || str == "oct"
		|| str == "Nov" || str == "nov"
		|| str == "Dec" || str == "dec"
		)
		return true;
	else
		return false;
}*/


bool isWeek(string str) {
	if (str ==
		"Jan" || "jan" || "Feb" || "feb" || "Mar" || "mar" || "Apr" || "apr" || "May" || "may" || "Jun" || "jun" || "Jul" || "jul" || "Aug" || "aug" || "Sep" || "sep" || "Oct" || "oct" || "Nov" || "nov" || "Dec" || "dec"
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