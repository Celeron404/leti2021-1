#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <Windows.h> // Ќужно дл€ получени€ координат консоли и их изменени€
using namespace std;

typedef struct charStack* pCharStack;
struct charStack {
	char data;
	pCharStack next;
};

typedef struct stringStack* pStringStack;
struct stringStack {
	string data;
	pStringStack next;
};

typedef struct intStack* pIntStack;
struct intStack {
	int data;
	pIntStack next;
};

void push(pCharStack * stackp, char data);
void pop(pCharStack * stackp);
int sizeOfStack(const pCharStack * stackp);
void push(pStringStack * stackp, string data);
void pop(pStringStack * stackp);
int sizeOfStack(const pStringStack * stackp);
void push(pIntStack * stackp, int data);
void pop(pIntStack * stackp);
int sizeOfStack(const pIntStack * stackp);

void removeSpacesFromString(string &input);
void expressionPrimaryCheck(string input);
void expressionSecondaryCheck(string input);
bool bracketCheck(string input);
bool polishExpressionCheck(string input);

// polish notations
string simpleToRevert(string input);
string simpleToDirect(string input);
int calculate(string input);
short operatorPriority(char input);
bool isOperator(char input);
bool isDigit(char input);

bool choiseNextAction();

void practicalWork3() {
	do {
		system("CLS");
		cout << "Solution of task \"Working with stacks and queues, learning direct and reverse polish notation.\n";

		bool inputIsCorrect = false;
		short exprType;
		string userEntered, input;
		do {
			// selecting the type of expression
			do {
				/*cout << "\nSelect the type of expression:\n"
					<< "1) Simple notation\n"
					<< "2) Direct polish notation\n"
					<< "3) Reverse polish notation\n>> ";*/
				cout << "\nSelect the type of expression:\n"
					<< "1) Simple notation (checking, converting and calculating)\n"
					<< "2) Direct polish notation (checking and calculating)\n"
					<< "3) Reverse polish notation (checking and calculating)\n>> ";
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
					<< "1) Keyboard\n"
					<< "2) File\n>> ";
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
			if (inputMethod == 2) {
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
				else {
					getline(ifile, userEntered);
					ifile.close();
				}
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
					break;
				case 2:
					polishExpressionCheck(input);
					break;
				case 3:
					polishExpressionCheck(input);
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

			// conversion the expression into other types of notation
			string convertedExpression;
			switch (exprType) {
			case 1:
				cout << "Entered expression in the Direct Polish Notation: \n\t"
					<< simpleToDirect(input) << endl;
				convertedExpression = simpleToRevert(input);
				cout << "Entered expression in the Reverse Polish Notation: \n\t"
					<< convertedExpression << endl;
				system("pause");
				break;
			case 2:
				/*cout << "Entered expression in the Simple Notation: \n\t"
					<< endl;
				cout << "Entered expression in the Reverse Polish Notation: \n\t"
					<< simpleToRevert(input) << endl;*/
				break;
			case 3:
				/*cout << "Entered expression in the Simple Notation: \n\t"
					<< endl;
				cout << "Entered expression in the Direct Polish Notation: \n\t"
					<< endl;*/
				break;
			}

			cout << "Calculating entered expression: \n";
			int result;
			try {
				switch (exprType) {
				case 1:
					result = calculate(convertedExpression);
					break;
				case 2:

					break;
				case 3:
					calculate(input);
					break;
				}
			}
			catch (const char* msg) {
				inputIsCorrect = false;
				cout << msg;
				continue;
			}
			cout << "Result is ";
			//// setting a console pointer
			//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			//CONSOLE_SCREEN_BUFFER_INFO bi;
			//GetConsoleScreenBufferInfo(hConsole, &bi);
			//bi.dwCursorPosition.X += 10;
			//SetConsoleCursorPosition(hConsole, bi.dwCursorPosition);			
			cout << result << endl;
		} while (!inputIsCorrect);

	} while (choiseNextAction());
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
	int openedBracket = 0, closedBracket = 0;
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

bool polishExpressionCheck(string input) {
	//searching incorrect symbols
	regex mask("[^0-9\\s\\+\\-\\*\\/]");
	if (std::regex_search(input, mask))
		/*
		Error! Input contains wrong symbols.
		Correct symbols: + - * / \"space\" 0-9
		Brackets are incorrect!
		Please, repeat input
		*/
		throw "Error! Input contains wrong symbols. \nCorrect symbols: + - * / \"space\" 0-9 \nBrackets are incorrect! \nPlease, repeat input.\n";

	//counting operators and operands
	int operators = 0, operands = 0, digits = 0;
	for (int i = 0; i < input.size(); i++) {
		if (isDigit(input[i])) {
			digits++;
			continue;
		}

		if (input[i] == ' ')
			if (digits > 0) {
				operands++;
				digits = 0;
			}

		if (isOperator(input[i])) {
			//if (input[i] != '-')
			operators++;

			//counting operands
			if (digits > 0) {
				operands++;
				digits = 0;
			}
			continue;
		}
	}
	if (operators > operands)
		/*
		Error! Input contains operators more than operands!
		This program not working correctly with negative numbers and operators besause i don't get paid for this job.
		*/
		throw "Error! Input contains operators more than operands! \nThis program not working correctly with negative numbers and operators besause i don't get paid for this job.";
}

string simpleToRevert(string input) {
	string result;
	pCharStack stackP = NULL;

	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '(') {
			push(&stackP, input[i]);
			continue;
		}

		while (!isOperator(input[i])) {
			result += input[i];
			i++;
			if (i >= input.length()) {
				result += ' ';
				break;
			}

			if (isOperator(input[i])) {
				result += ' ';
				//i--;
				break;
			}
		}
		if (i >= input.length()) break;

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

string simpleToDirect(string input) {
	string result = input;
	int size = input.size();
	//flip the string
	char * temp = new char[size + 1];
	for (int i = 0, j = size-1; i < size; i++, j--) {
		temp[i] = input[j];
	}
	temp[size] = '\0';
	result = temp;

	//brackets flipping
	for (int i = 0; i < size; i++) {
		if (result[i] == '(' || result[i] == ')') {
			if (result[i] == '(')
				result[i] = ')';
			else
				result[i] = '(';
			i++;
		}
	}

	result = simpleToRevert(result);
	size = result.size();
	delete temp;
	temp = new char[size + 1];
	//flip the string again
	for (int i = 0, j = size - 1; i < size; i++, j--) {
		temp[i] = result[j];
	}
	temp[size] = '\0';

	result = temp;
	delete temp;
	
	return result;
}

int calculate(string input) {
	pIntStack stackP = NULL;

	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ' ') continue;

		if (isDigit(input[i])) {
			//parsing the number to tmp and then converting to int
			string tmp;
			do {
				tmp += input[i];
				i++;
				if (i >= input.length()) break; // need to debug
				if (input[i] == ' ') break;
			} while (isDigit(input[i]));
			int number = stoi(tmp);
			push(&stackP, number);
		}
		else {
			int secondNumber = stackP->data;
			pop(&stackP);

			//checking to existing next number
			if (!(stackP->data)) throw "Error! Excess number in the expression.";

			int firstNumber = stackP->data;
			pop(&stackP);

			//calculating and printing
			int operationResult;
			switch (input[i]) {
			case '+':
				operationResult = firstNumber + secondNumber;
				cout << "Sum of ";
				break;

			case '-':
				operationResult = firstNumber - secondNumber;
				cout << "Subtraction of ";
				break;

			case '*':
				operationResult = firstNumber * secondNumber;
				cout << "Multiplication of ";
				break;

			case '/':
				operationResult = firstNumber / secondNumber;
				cout << "Divide of ";
				break;
			}
			push(&stackP, operationResult);
			cout << firstNumber << " and " << secondNumber << " is " << stackP->data << endl;

		}

	}

	return stackP->data;
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