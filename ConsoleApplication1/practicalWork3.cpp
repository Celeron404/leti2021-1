#include <iostream>
#include <string>
#include <fstream>
#include <regex>
using namespace std;

typedef struct Stack* pStack;
struct Stack {
	char data;
	pStack next;
};

void push(pStack* stackp, char data);
void pop(pStack* stackp);
int sizeOfStack(const pStack * stackp);

void removeSpacesFromString(string &input);
void expressionPrimaryCheck(string input);
void expressionSecondaryCheck(string input);
bool bracketCheck(string input);
string simpleToRevertPolish(string input);
short operatorPriority(char input);
bool isOperator(char input);



void practicalWork3() {
	system("CLS");
	cout << "Solution of task \"Working with stacks and queues, learning direct and reverse polish notation.\n";

	bool inputIsCorrect = false;
	short exprType;
	string userEntered;
	string input;
	do {
		// selecting the type of expression
		do {
			cout << "\nSelect the type of expression:\n"
				<< "1) Simple notation\n"
				<< "2) Direct polish notation\n"
				<< "3) Reverse polish notation\n>> ";
			cin >> exprType;
			if (exprType == 1 || exprType == 2 || exprType == 3) {
				inputIsCorrect = true;
				break;
			}
			else
				cout << "Error: wrong input. Please repeat menu selection.\n";
		} while (!inputIsCorrect);

		// selecting an input method
		inputIsCorrect = false;
		short inputMethod;
		do {
			cout << "\nSelect an input method:\n"
				<< "1) File\n"
				<< "2) Keyboard\n";
			cin >> inputMethod;
			if (inputMethod == 1) {
				inputIsCorrect = true;
				break;
			}
			else if (inputMethod == 2) {
				inputIsCorrect = true;
				break;
			}
			else
				cout << "Error: wrong input. Please repeat menu selection.\n";
		} while (!inputIsCorrect);

		// entering the expression (or reading file)
		inputIsCorrect = false;
		if (inputMethod == 1) {
			ifstream ifile;
			string path;
			cout << "Enter the path to the file. \n"
				<< "Only english words in the file and path! Example: C:\\anime\\students.txt \n>> ";
			cin.ignore(32767, '\n');
			getline(cin, path);
			ifile.open(path);
			if (!ifile.is_open()) {
				cout << "Error opening file! Please restart the program! \n";
				throw - 1;
			}
			else
				getline(ifile, userEntered);
		}
		else {
			cin.ignore(32767, '\n');
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
				break;
			}
			cout << "\n>> ";

			getline(cin, userEntered);
		}

		// checking the expression
		input = userEntered;
		try {
			switch (exprType) {
			case 1:
				expressionPrimaryCheck(input);
				removeSpacesFromString(input);
				expressionSecondaryCheck(input);
				cout << simpleToRevertPolish(input) << endl;
				break;
			case 2:

				break;
			case 3:

				break;
			}
		}
		catch (const char* msg) {
			cout << msg;
			continue;
		}
		inputIsCorrect = true;
		if (inputIsCorrect) {
			cout << "Input is correct.\n";
			system("pause");
		}
	} while (!inputIsCorrect);
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

string simpleToRevertPolish(string input) {
	string result;
	pStack stackP = NULL;

	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '(') {
			push(&stackP, input[i]);
			continue;
		}

		if (!isOperator(input[i])) {
			result += input[i];
			result += ' ';
			continue;
		}

		if (input[i] == ')') {
			char pos = ' ';
			while (pos != '(') {
				pos = stackP->data;
				pop(&stackP);
				if (pos != '(') {
					result += pos;
					result += ' ';
				}
			}
			continue;
		}

		if (sizeOfStack(&stackP) != 0)
			while (operatorPriority(stackP->data) >= operatorPriority(input[i])) {
				result += stackP->data;
				result += ' ';
				pop(&stackP);
				if (sizeOfStack(&stackP) == 0)
					break;
			}

		if (sizeOfStack(&stackP) == 0) {
			push(&stackP, input[i]);
			continue;
		}

		if (operatorPriority(stackP->data) < operatorPriority(input[i])) {
			push(&stackP, input[i]);
			continue;
		}
	}

	while (sizeOfStack(&stackP) != 0) {
		result += stackP->data;
		result += ' ';
		pop(&stackP);
	}

	// delete last ' ' symbol
	result.erase(result.length() - 1);

	return result;
}

short operatorPriority(char input) {
	switch (input) {
	case '(':
		return 1;
	case '+': case '-':
		return 2;
	case '*': case '/':
		return 3;
	default:
		return 0;
	}
}

bool isOperator(char input) {
	if (input == '+'
		|| input == '-'
		|| input == '*'
		|| input == '/'
		|| input == ')'
		|| input == '(')
		return true;
	else
		return false;
}

