#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <chrono>
using namespace std::chrono;
using namespace std;

bool isDigit(char input);
int countOfElements(ifstream * file);
void fillArrayFromFile(ifstream * file, int * arr, int arrSize);

float stopSecondsTimer(time_point<steady_clock> startTimer);
long long stopNanoSecondsTimer(time_point<steady_clock> startTimer);


void practicalWork2() {
	// Timer
	srand((unsigned)time(NULL));
	time_point<steady_clock> startTimer = steady_clock::now();
	float stopTimeInSeconds = stopSecondsTimer(startTimer);
	long long stopTimeInNanoSeconds = stopNanoSecondsTimer(startTimer);

	system("CLS");
	cout << "Solution of task \"Working with Dynamic Massives and Doubly Linked Lists\". \n\n" <<
		"Task 1. Reading file. \n";

	ifstream ifile;
	ofstream ofile;
	string path;
	int numberOfElements;
	int * dynArr = 0;
	do {
		cout << "Enter the path to the file. \n"
			<< "Only english words in the file and path! Example: C:\\anime\\arrr.txt \n>> ";
		cin.ignore(32767, '\n');
		getline(cin, path);
		ifile.open(path);
		if (!ifile.is_open()) {
			cout << "Error opening file! Please restart the program! \n";
			continue;
		}

		ifstream *pifile = &ifile;
		numberOfElements = countOfElements(pifile);
		if (numberOfElements == 0) {
			cout << "Error! No elements founds.\n";
			continue;
		}

		ifile.close();
		ifile.open(path);
		startTimer = steady_clock::now();
		dynArr = new int[numberOfElements];
		fillArrayFromFile(pifile, dynArr, numberOfElements);
		stopTimeInSeconds = stopSecondsTimer(startTimer);
		cout << "Dynamic array has been initialized and filled in " << fixed << stopTimeInSeconds << " second(s). \n";
		system("pause");
		
		/*{
			cout << "--- Debug ---\n";
			for (int i = 0; i < numberOfElements; i++)
			{
				cout << dynArr[i] << ' ';
			}
			cout << "\n--- End of Debug ---\n";
			system("pause");
		}*/


	} while (!ifile.is_open());
	ifile.close();
}

int countOfElements(ifstream * file) {
	string t;
	int count = 0;
	while (std::getline(*file, t)) {
		if (t.length() > 1)
			for (unsigned i = 0; i < static_cast<unsigned>(t.length() - 1); i++)
				if (((t[i] == ' ') || (t[i] == '\t')) && (isDigit(t[i + 1])))
					count++;					// Counting the number of "spaces/tabs+digits"
		count++;								// counting the number of linebreakes
	}
	return count;
}

void fillArrayFromFile(ifstream * file, int * arr, int arrSize) {
	int arrPos = 0;
	while ((arrPos < arrSize) && (!file->eof()))
	{ 
		// Getting a string with numbers from file
		string tStr;
		getline(*file, tStr);

		// Extracting a numbers from string to array
		for (int tStrPos = 0; tStrPos < tStr.length(); tStrPos++)
		{
			char * tNum = new char[tStr.length()];
			int tNumPos = 0;
			while (
				(tStr[tStrPos] != ' ') &&
				(tStr[tStrPos] != '\t') &&
				(tStrPos < tStr.length())
				) {
				tNum[tNumPos] = tStr[tStrPos];
				tStrPos++;
				tNumPos++;
			}

			arr[arrPos] = stoi(tNum);
			arrPos++;
		}
	}
}

bool isDigit(char input) {
	if (input >= 48 && input <= 57)
		return true;
	else return false;
}