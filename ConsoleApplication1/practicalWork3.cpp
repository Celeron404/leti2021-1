#include <iostream>
#include <string>
#include <regex>
using namespace std;

void removeSpacesFromString(string &input);
void expressionPrimaryCheck(string input);
void expressionSecondaryCheck(string input);
bool bracketCheck(string input);

void practicalWork3() {
	system("CLS");
	cout << "Solution of task \"Working with stacks and queues, learning direct and reverse polish notation.\n";
	bool inputIsCorrect = false;
	short exprType;
	do {
		cout << "\nEnter the type of expression:\n"
			<< "1) Simple notation\n"
			<< "2) Direct polish notation\n"
			<< "3) Reverse polish notation\n>> ";
		cin >> exprType;
		if (exprType == 1 || exprType == 2 || exprType == 3) {
			inputIsCorrect = true;
			break;
		}
		cout << "Error: wrong input. Please repeat menu selection.\n";
	} while (!inputIsCorrect);

	// enter and checking
	inputIsCorrect = false;
	cin.ignore(32767, '\n');
	do {
		cout << "\nEnter the expression. Example: ";
		switch (exprType) {
		case 1:
			cout << "(1 + 3) * 4";
			break;
		case 2:
			cout << "* + 1 3 4";
			break;
		case 3:
			cout << "1 3 + 4 *";
		}
		cout << "\n>> ";
		string input;
		//cin >> input;
		

		getline(cin, input);

		try {
			expressionPrimaryCheck(input);
			removeSpacesFromString(input);
			expressionSecondaryCheck(input);
		}
		catch (const char* msg) {
			cout << msg;
			continue;
		}

		/*else {
			cout << "input contains wrong symbols. \n" <<
				"correct symbols: + - * / ( ) \"space\" 0-9 \n" <<
				"please, repeat input\n";
			continue;
		}*/

		
		cout << "-- Debugging --\n"
			<< input << endl;
		system("pause");

	} while (!inputIsCorrect);
	system("pause");
}

void removeSpacesFromString(string &input) {
	bool isRemoved;
	do {
		isRemoved = false;
		for (unsigned i = 0; i < input.length(); i++)
		{
			if (input[i] == ' ') {
				input.erase(i, 1);
				isRemoved = true;
			}
		}
	} while (isRemoved);
}

void expressionPrimaryCheck(string input) {
	//searching incorrect symbols
	regex mask("[^0-9\\s\\+\\-\\*\\/\\(\\)]");
	if (std::regex_search(input, mask))
		/*
		Error! Input contains wrong symbols.
		Correct symbols: + - * / ( ) \"space\" 0-9
		Please, repeat input
		*/
		throw "Error! Input contains wrong symbols. \nCorrect symbols: + - * / ( ) \"space\" 0-9 \nPlease, repeat input.\n";

	//searching incorrect sequence of characters
	mask = "[0-9]\\s+[0-9]"; // "11 4" sequences
	if (std::regex_search(input, mask))
		/*
		Error! Input contains wrong sequence of characters.
		Correct example: (1 * 4 + 3 * 4) * 4
		Incorrect sequences example: (1 4 + 3 4) * 4
		Please, repeat input.
		*/
		throw "Error! Input contains wrong sequence of characters. \nCorrect example: (1 + 3) * 4\nIncorrect sequences example: +--*/++--**// 11 4 (space between numbers and characters)\nPlease, repeat input.\n";
}

void expressionSecondaryCheck(string input) {
	//searching incorrect sequence of characters
	regex mask("[\\+\\-\\*\\/]{2}"); // "+--*/++--**//" sequences
	if (std::regex_search(input, mask))
		/*
		Error! Input contains wrong sequence of characters.
		Correct example: (1 + 3) * 4
		Incorrect sequences example: +--* /++--** //
		Please, repeat input.
		*/
		throw "Error! Input contains wrong sequence of characters. \nCorrect example: (x + 3) * y\nIncorrect sequences example: +--*/++--**// \nPlease, repeat input.\n";

	mask = "([0-9]\\()|(\\)[0-9])|(\\(\\))"; // "() 5( )5" sequences
	if (std::regex_search(input, mask))
		/*
		Error! Input contains wrong sequence of characters.
		Correct example: (1 + 3) * 4
		Incorrect sequences example: () 5( )5
		Please, repeat input.
		*/
		throw "Error! Input contains wrong sequence of characters. \nCorrect example: (1 + 3) * 4\nIncorrect sequences example: () 5( )5 \nPlease, repeat input.\n";
	
	//searching the operators in begin and end of the expression
	mask = "^[\\+\\*\\/]|[\\+\\-\\*\\/]$";
	if (std::regex_search(input, mask))
		/*
		Error! Input contains operators in begin or end of the expression.
		Correct example: 1 + 3 * 4
		Incorrect example: *1 + 3 * 4-
		Please, repeat input.
		*/
		throw "Error! Input contains operators in begin or end of the expression. \nCorrect example: 1 + 3 * 4\nIncorrect example: *1 + 3 * 4- \nPlease, repeat input.\n";

	//counting opened and closed brackets
	if (!bracketCheck(input))
		/*
		Error! The number of opening brackets does not match the number of closing brackets.
		Correct example: (1 + (3 - 1)) * 4
		Incorrect example: (1 + (3 - 4) * 4
		Please, repeat input.
		*/
		throw "Error! The number of opening brackets does not match the number of closing brackets. \nCorrect example: (1 + (3 - 1)) * 4\nIncorrect example: (1 + (3 - 4) * 4 \nPlease, repeat input.\n";
}

bool bracketCheck(string input) {
	int openedBracket = 0;
	int closedBracket = 0;
	for (unsigned i = 0; i < input.length(); i++)
	{
		if (input[i] == '(')
			openedBracket++;
		else if (input[i] == ')')
			closedBracket++;
	}
	if (openedBracket == closedBracket)
		return true;
	else
		return false;
}