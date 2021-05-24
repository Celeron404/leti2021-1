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
int getArrayElement(int * arr, int size, int input);
int * increaseArray(int * obj, int * size);
int * decreaseArray(int * obj, int * size);
void insertToArr(int * arr, int size, int value, int index);
void deleteArrElement(int * arr, int size, int index);

float stopSecondsTimer(time_point<steady_clock> startTimer);
long long stopNanoSecondsTimer(time_point<steady_clock> startTimer);

bool choiseNextAction();

void practicalWork2() {
	// Timer
	srand((unsigned)time(NULL));
	time_point<steady_clock> startTimer = steady_clock::now();
	float stopTimeInSeconds = stopSecondsTimer(startTimer);
	long long stopTimeInNanoSeconds = stopNanoSecondsTimer(startTimer);

	system("CLS");
	cout << "Solution of task \"Working with Dynamic Massives and Doubly Linked Lists\". \n\n" <<
		"\tTask 1. Reading file and creating dynamic massive and doubly linked list. \n";

	ifstream ifile;
	ofstream ofile;
	string path;
	int numberOfElements;
	int * dynArr = 0;
	do {
		cout << "\nEnter the path to the file. \n"
			<< "Only english words in the file and path! Example: C:\\anime\\pr2testFile.txt \n>> ";
		cin.ignore(32767, '\n');
		getline(cin, path);
		ifile.open(path);
		if (!ifile.is_open()) {
			cout << "Error opening file! Please restart the program! \n";
			throw - 1;
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
		cout << "\nDynamic array has been initialized and filled in " << fixed << stopTimeInSeconds << " second(s). \n";
		system("pause");

		do {
			cout << "\n\tTask 2. Dynamic array and doubly linked list operations. \n"
				<< "1) Getting and element\n"
				<< "2) Element insertion\n"
				<< "3) Deleting an element\n"
				<< "Enter option number... \n>> ";
			int input;
			cin >> input;
			switch (input) {
			case 1:
				cout << "\nTypes of getting: \n"
					<< "1) On index\n"
					<< "2) On value\n"
					<< "Enter option number... \n>> ";
				cin >> input;
				switch (input) {
				case 1:
					cout << "\nEnter the index of element... \n>> ";
					cin >> input;
					if ((input < numberOfElements) && (input >= 0)) {
						startTimer = steady_clock::now();
						int result = dynArr[input];
						stopTimeInSeconds = stopSecondsTimer(startTimer);
						// here would be a double linked list operation
						cout << "\n" << input << " element has containing the value " << result << ". \n";
						cout << "Element found in dynamic array for " << fixed << stopTimeInSeconds << " second(s). \n";
					}
					else cout << "Error! Array has not contain that element\n";
					break;
				case 2:
					cout << "\nEnter the value of element... \n>> ";
					cin >> input;
					startTimer = steady_clock::now();
					int result = getArrayElement(dynArr, numberOfElements, input);
					stopTimeInSeconds = stopSecondsTimer(startTimer);
					// here would be a double linked list operation
					if (result != -1) {
						cout << "\nThe first found element with a value of " << input << " has an index " << result << " .\n";
						cout << "Element found in dynamic array for " << fixed << stopTimeInSeconds << " second(s). \n";
					}
					else cout << "Error! The element has not found. \n";
					break;
				}
				break;
			case 2:
				cout << "\nEnter the insertion value... \n>> ";
				cin >> input;
				int inputIndex;
				cout << "\nEnter the index of insertion... \n>> ";
				cin >> inputIndex;
				if ((inputIndex >= 0) && (inputIndex < numberOfElements))
				{
					startTimer = steady_clock::now();
					dynArr = increaseArray(dynArr, &numberOfElements);
					insertToArr(dynArr, numberOfElements, input, inputIndex);
					stopTimeInSeconds = stopSecondsTimer(startTimer);
					cout << "Element has been inserted in dynamic array for " << fixed << stopTimeInSeconds << " second(s). \n";
				}
				break;
			case 3:
				cout << "\nTypes of deleting: \n"
					<< "1) On index\n"
					<< "2) On value\n"
					<< "Enter option number... \n>> ";
				cin >> input;
				switch (input) {
				case 1:
					cout << "\nEnter the index of element... \n>> ";
					cin >> input;
					if ((input < numberOfElements) && (input >= 0)) {
						startTimer = steady_clock::now();
						deleteArrElement(dynArr, numberOfElements, input);
						dynArr = decreaseArray(dynArr, &numberOfElements);
						stopTimeInSeconds = stopSecondsTimer(startTimer);
						// here would be a double linked list operation
						cout << "Element has been deleted from dynamic array for " << fixed << stopTimeInSeconds << " second(s). \n";
					}
					else cout << "Error! Array has not contain that element\n";
					break;
				case 2:
					cout << "\nEnter the value of element... \n>> ";
					cin >> input;
					startTimer = steady_clock::now();
					int index = getArrayElement(dynArr, numberOfElements, input);
					if (index != -1)
					{
						deleteArrElement(dynArr, numberOfElements, index);
						dynArr = decreaseArray(dynArr, &numberOfElements);
						stopTimeInSeconds = stopSecondsTimer(startTimer);
						// here would be a double linked list operation
						cout << "Element has been deleted from dynamic array for " << fixed << stopTimeInSeconds << " second(s). \n";
						/*{
							cout << "--- Debug ---\n";
							for (int i = 0; i < numberOfElements; i++)
							{
								cout << dynArr[i] << ' ';
							}
							cout << "\n--- End of Debug ---\n";
							system("pause");
						}*/
					}
					else cout << "Error! The element has not found. \n";
					break;
				}


				break;
			}
			cout << "End of the Task 2. \n";
		} while (choiseNextAction());
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
		for (int unsigned tStrPos = 0; tStrPos < tStr.length(); tStrPos++)
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

int getArrayElement(int * arr, int size, int input) {
	int result = -1;
	for (int i = 0; i < size; i++)
		if (arr[i] == input) {
			result = i;
			break;
		}
	return result;		
}

int * increaseArray(int * obj, int * size) {
	int * tempObj = new int[*size + 1];
	for (int i = 0; i < *size; i++) {
		tempObj[i] = obj[i];
	}
	delete[] obj;
	obj = tempObj;
	*size = *size + 1;
	return obj;
}

int * decreaseArray(int * obj, int * size) {
	int * tempObj = new int[*size - 1];
	for (int i = 0; i < *size - 1; i++) {
		tempObj[i] = obj[i];
	}
	delete[] obj;
	obj = tempObj;
	*size = *size - 1;
	return obj;
}

void insertToArr(int * arr, int size, int value, int index)
{
	if (!arr[index])
	{
		arr[index] = value;
		return;
	}	
	for (int i = size - 1; i > index; i--)
		arr[i] = arr[i - 1];
	arr[index] = value;
}

void deleteArrElement(int * arr, int size, int index)
{
	if (index == (size - 1))
		return;

	for (int i = index; i < size; i++)
		arr[i] = arr[i + 1];
}

bool isDigit(char input) {
	if (input >= 48 && input <= 57)
		return true;
	else return false;
}