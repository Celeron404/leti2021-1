#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <chrono>
using namespace std::chrono;
using namespace std;

struct list
{
	int value;
	list * before;
	list * after;
};

// main functions
int countOfElements(ifstream * file);

// array functions
void fillArrayFromFile(ifstream * file, int * arr, int arrSize);
int getArrayElement(int * arr, int size, int input);
int * increaseArray(int * obj, int * size);
int * decreaseArray(int * obj, int * size);
void insertToArr(int * arr, int size, int value, int index);
void deleteArrElement(int * arr, int size, int index);
void printArr(int * arr, int size);

// list functions
list * createList(int size);
void fillListFromFile(ifstream * file, list * list);
void printList(list *list);
int getListElementByIndex(list *dlList, int index);
int getListElementByValue(list *dlList, int value);
list * insertToList(list *dlList, int value, unsigned index);
void deleteListElementByIndex(list * &dlList, int index);
void deleteListElementByValue(list * &dlList, int value);

//secondary functions
bool isDigit(char input);
float stopSecondsTimer(time_point<steady_clock> startTimer);
long long stopNanoSecondsTimer(time_point<steady_clock> startTimer);
bool choiseNextAction();

void practicalWork2() {
	// Timer
	srand((unsigned)time(NULL));
	time_point<steady_clock> startTimer = steady_clock::now();
	float stopDynTime = stopSecondsTimer(startTimer);
	float stopListTime = stopSecondsTimer(startTimer);
	long long stopDynNanoTime = stopNanoSecondsTimer(startTimer);
	long long stopListNanoTime = stopNanoSecondsTimer(startTimer);

	system("CLS");
	cout << "Solution of task \"Working with Dynamic Massives and Doubly Linked Lists\". \n\n" <<
		"\tReading file and creating dynamic massive and doubly linked list. \n";

	ifstream ifile;
	ofstream ofile;
	string path;
	int numberOfElements;
	int * dynArr = 0;
	list * dlList = 0;

	do { // file opening
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
			system("pause");
			continue;
		}

		// working with an array
		ifile.close();
		ifile.open(path);
		startTimer = steady_clock::now();
		dynArr = new int[numberOfElements];
		fillArrayFromFile(pifile, dynArr, numberOfElements);
		stopDynTime = stopSecondsTimer(startTimer);

		// working with a doubly linked list
		ifile.close();
		ifile.open(path);
		startTimer = steady_clock::now();
		dlList = createList(numberOfElements);
		fillListFromFile(pifile, dlList);
		stopListTime = stopSecondsTimer(startTimer);

		cout << "\nDynamic array has been initialized and filled in " << fixed << stopDynTime << " second(s).";
		cout << "\nDoubly linked list has been initialized and filled in " << fixed << stopListTime << " second(s). \n";
		system("pause");

		// uncomment to debug
		//printList(dlList);
		//printArr(dynArr, numberOfElements);

		do {
			cout << "\n\tDynamic array and doubly linked list operations. \n"
				<< "0) Printing the array\n"
				<< "1) Getting and element\n"
				<< "2) Element insertion\n"
				<< "3) Deleting an element\n"
				<< "4) Additional option: randomly increacing the elements of the dynamic array (values from 0 to 5) and adding all positive elements to the doubly linked array\n"
				<< "Enter option number... \n>> ";
			int input;
			cin >> input;
			switch (input) {
			case 0:
				cout << endl;
				printArr(dynArr, numberOfElements);
				// uncomment to debug
				//printList(dlList);
				break;
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
					if ((input < numberOfElements) && (input >= 0))
					{
						// working with an array
						startTimer = steady_clock::now();
						int dynArrResult = dynArr[input];
						stopDynNanoTime = stopNanoSecondsTimer(startTimer);

						// working with a doubly linked list
						startTimer = steady_clock::now();
						int dlListResult = getListElementByIndex(dlList, input);
						stopListNanoTime = stopNanoSecondsTimer(startTimer);

						cout << "\n" << input << " element has containing the value " << dynArrResult << ". \n";
						// uncomment to debug
						//cout << input << " element has containing the value " << dlListResult << ". \n";

						cout << "\nElement found in dynamic array for " << fixed << stopDynNanoTime << " nanosecond(s). \n";
						cout << "Element found in doubly linked list for " << fixed << stopListNanoTime << " nanosecond(s). \n";
					}
					else cout << "Error! Array has not contain that index!\n";
					break;
				case 2:
					cout << "\nEnter the value of element... \n>> ";
					cin >> input;

					// working with an array
					startTimer = steady_clock::now();
					int dynArrResult = getArrayElement(dynArr, numberOfElements, input);
					stopDynNanoTime = stopNanoSecondsTimer(startTimer);

					// working with a doubly linked list
					startTimer = steady_clock::now();
					int dlListResult = getListElementByValue(dlList, input);
					stopListNanoTime = stopNanoSecondsTimer(startTimer);

					if ((dynArrResult != -1) && (dlListResult != -1)) {
						cout << "\nThe first found element with a value of " << input << " has an index " << dynArrResult << ".\n";
						// uncomment to debug
						//cout << "\nThe first found element with a value of " << input << " has an index " << dlListResult << ".\n";
						cout << "Element found in dynamic array for " << fixed << stopDynNanoTime << " nanosecond(s). \n";
						cout << "Element found in doubly linked list for " << fixed << stopListNanoTime << " nanosecond(s). \n";
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
				if ((inputIndex >= 0) && (inputIndex <= numberOfElements))
				{
					// working with an array
					startTimer = steady_clock::now();
					dynArr = increaseArray(dynArr, &numberOfElements);
					insertToArr(dynArr, numberOfElements, input, inputIndex);
					stopDynNanoTime = stopNanoSecondsTimer(startTimer);

					// working with a doubly linked list
					startTimer = steady_clock::now();
					dlList = insertToList(dlList, input, inputIndex);
					stopListNanoTime = stopNanoSecondsTimer(startTimer);

					cout << "Element has been inserted in dynamic array for " << fixed << stopDynNanoTime << " nanosecond(s). \n";
					cout << "Element has been inserted in doubly linked list for " << fixed << stopListNanoTime << " nanosecond(s). \n";
					// uncomment to debug
					//printArr(dynArr, numberOfElements);
					//printList(dlList);
				}
				else cout << "Error! Array has not contain that index!\n"
					<< "If you need an insert after all elements, the index must be equal to the number of elements.\n";
				break;
			case 3:
				cout << "\nTypes of deleting: \n"
					<< "1) On index\n"
					<< "2) On value\n"
					<< "Enter option number... \n>> ";
				cin >> input;
				switch (input) {
				case 1:
					cout << "\nEnter the index of the element... \n>> ";
					cin >> input;
					if ((input < numberOfElements) && (input >= 0))
					{
						// working with an array
						startTimer = steady_clock::now();
						deleteArrElement(dynArr, numberOfElements, input);
						dynArr = decreaseArray(dynArr, &numberOfElements);
						stopDynNanoTime = stopNanoSecondsTimer(startTimer);

						// working with a doubly linked list
						startTimer = steady_clock::now();
						deleteListElementByIndex(dlList, input);
						stopListNanoTime = stopNanoSecondsTimer(startTimer);

						cout << "Element has been deleted from dynamic array for " << fixed << stopDynNanoTime << " nanosecond(s). \n";
						cout << "Element has been deleted from doubly linked list for " << fixed << stopListNanoTime << " nanosecond(s). \n";
						// uncomment to debug
						//printArr(dynArr, numberOfElements);
						//printList(dlList);
					}
					else cout << "Error! Array has not contain that element\n";
					break;
				case 2:
					cout << "\nEnter the value of the element... \n>> ";
					cin >> input;

					// working with an array
					startTimer = steady_clock::now();
					int index = getArrayElement(dynArr, numberOfElements, input);
					if (index != -1)
					{
						deleteArrElement(dynArr, numberOfElements, index);
						dynArr = decreaseArray(dynArr, &numberOfElements);
						stopDynNanoTime = stopNanoSecondsTimer(startTimer);

						// working with a doubly linked list
						startTimer = steady_clock::now();
						deleteListElementByValue(dlList, input);
						stopListNanoTime = stopNanoSecondsTimer(startTimer);

						cout << "Element has been deleted from dynamic array for " << fixed << stopDynNanoTime << " nanosecond(s). \n";
						cout << "Element has been deleted from doubly linked list for " << fixed << stopListNanoTime << " nanosecond(s). \n";
						// uncomment to debug
						//printArr(dynArr, numberOfElements);
						//printList(dlList);
					}
					else cout << "Error! The element has not found. \n";
					break;
				}
				break;
			case 4:
				cout << "\nFirst step in progress...\n";
				for (int i = 0; i < numberOfElements; i++)
				{
					int t = rand() % 6;
					// uncomment to debug
					//cout << t << ' ';
					dynArr[i] += t;
				}
				cout << "Array after randomly increacing the elements (values from 0 to 5):\n";
				printArr(dynArr, numberOfElements);

				startTimer = steady_clock::now();
				cout << "\nSecond step in progress...\n";
				int addPos = numberOfElements; // for the adding to the end of list
				for (int i = 0; i < numberOfElements; i++)
				{
					if (dynArr[i] > 0)
					{
						dlList = insertToList(dlList, dynArr[i], addPos);
						addPos++;
					}
				}
				stopListNanoTime = stopNanoSecondsTimer(startTimer);
				cout << "Second step has been done for " << fixed << stopDynNanoTime << " nanosecond(s). \n";

				printList(dlList);
				break;
			}
			cout << "\nEnd of dynamic array and doubly linked list operations.";
		} while (choiseNextAction());
	} while (!ifile.is_open());
	ifile.close();
}

int countOfElements(ifstream * file)
{
	string t;
	int count = 0;
	while (std::getline(*file, t)) {
		if (t.length() > 1)
			for (unsigned i = 0; i < static_cast<unsigned>(t.length() - 1); i++)
				if (((t[i] == ' ') || (t[i] == '\t'))
					&& ((isDigit(t[i + 1])) || (t[i+1] == '-')))
					count++;					// Counting the number of "spaces/tabs+digits/minuses"
		count++;								// counting the number of linebreakes
	}
	return count;
}

void fillArrayFromFile(ifstream * file, int * arr, int arrSize)
{
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

int getArrayElement(int * arr, int size, int input)
{
	int result = -1;
	for (int i = 0; i < size; i++)
		if (arr[i] == input) {
			result = i;
			break;
		}
	return result;		
}

int * increaseArray(int * obj, int * size)
{
	int * tempObj = new int[*size + 1];
	for (int i = 0; i < *size; i++) {
		tempObj[i] = obj[i];
	}
	delete[] obj;
	obj = tempObj;
	*size = *size + 1;
	return obj;
}

int * decreaseArray(int * obj, int * size)
{
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

void printArr(int * arr, int size)
{
	cout << "Printing the array...\n";
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << "\nEnd of the array.\n";
	system("pause");
}

bool isDigit(char input) {
	if (input >= 48 && input <= 57) // in Chars 48 = '0', 57 = '9'
		return true;
	else return false;
}

list * createList(int size) {
	list * current = 0, * after = 0;
	for (int i = 1; i <= size; i++)
	{
		current = new list;
		current->after = after; // adding an address of next element
		if (after)
			after->before = current; // writing an address of current element to next element
		after = current; // changing position of current element
	}
	current->before = 0;
	return current;
}

void fillListFromFile(ifstream * file, list * dlList)
{
	list * pos = dlList;
	do {
		if (file->eof())
			return;

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

			pos->value = stoi(tNum);
			pos = pos->after;
		}
	} while (pos);
}

void printList(list *dlList)
{
	cout << "Printing the list...\n";
	list *pos = dlList;
	do {
		cout << pos->value << ' ';
		pos = pos->after;
	} while (pos);
	cout << "\nEnd of the list.\n";
	system("pause");
}

int getListElementByIndex(list *dlList, int index)
{
	list *pos = dlList;
	do {
		if (index == 0)
			return pos->value;
		else
		pos = pos->after;
		index--;
	} while (pos);
	return 0;
}

int getListElementByValue(list *dlList, int value)
{
	int index = 0;
	list *pos = dlList;
	do {
		if (pos->value == value)
			return index;
		else {
			pos = pos->after;
			index++;
		}
	} while (pos);
	return -1;
}

list * insertToList(list *dlList, int value, unsigned index)
{
	list * newElement = new list;
	newElement->value = value;

	list *pos = dlList;
	do {
		if (index == 0)
		{
			if (pos->before == 0)
			{
				newElement->before = 0;
				newElement->after = pos;
				pos->before = newElement;
				return newElement;
			}
			else
			{
				newElement->before = pos->before;
				newElement->after = pos;
				pos->before->after = newElement;
				pos->before = newElement;
				return dlList;
			}
		}
		else if ((index == 1) && (pos->after == 0)) {
			newElement->after = 0;
			newElement->before = pos;
			pos->after = newElement;
			return dlList;
		}
		else
			pos = pos->after;
		index--;
	} while (pos);
	return 0;
}

// from lesson, not worked
//list * insertToList(list *dlList, int value, unsigned index)
//{
//	list * newElement = new list;
//	newElement->value = value;
//
//	if (!index || !dlList)
//	{
//		dlList->before = dlList;
//		newElement->before = 0;
//		newElement->after = dlList;
//		dlList = newElement;
//		return dlList;
//	}
//
//	list * beforePos = dlList;
//	index--;
//	while ((beforePos->after) && (index--))
//		beforePos = beforePos->after;
//
//	newElement->before = beforePos;
//	newElement->after->before = newElement;
//	newElement->after = beforePos->after;
//	beforePos->after = newElement;
//	return newElement;
//}

void deleteListElementByIndex(list * &dlList, int index)
{
	list * pos = dlList;
	do
	{
		if (index == 0)
			if (pos->before == 0)
			{
				pos = dlList->after;
				pos->before = 0;
				delete dlList;
				dlList = pos;
				return;
			}
			else if (pos->after == 0)
			{
				pos->before->after = 0;
				delete pos;
				return;
			}
			else
			{
				pos->before->after = pos->after;
				pos->after->before = pos->before;
				delete pos;
				return;
			}
		else
		{
			pos = pos->after;
			index--;
		}
	} while (pos);
}

void deleteListElementByValue(list *&dlList, int value)
{
	list * pos = dlList;
	do
	{
		if (pos->value == value)
			if (pos->before == 0)
			{
				pos = dlList->after;
				pos->before = 0;
				delete dlList;
				dlList = pos;
				return;
			}
			else if (pos->after == 0)
			{
				pos->before->after = 0;
				delete pos;
				return;
			}
			else
			{
				pos->before->after = pos->after;
				pos->after->before = pos->before;
				delete pos;
				return;
			}
		else {
			pos = pos->after;
		}
	} while (pos);
}
