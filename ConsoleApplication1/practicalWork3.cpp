#include <iostream>
#include <string>
#include <regex>
using namespace std;

void expressionCheck(string input);
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
			cout << "(x + 3) * y";
			break;
		case 2:
			cout << "* + x 3 y";
			break;
		case 3:
			cout << "x 3 + y *";
		}
		cout << "\n>> ";
		string input;
		//cin >> input;
		
		getline(cin, input);

		try {
			expressionCheck(input);
				
			//remove spaces
				for (int i = 0; i < input.length(); i++)
				{
					if (input[i] == ' ')
						input.erase(i, 1);
				}
		}
		catch (const char* msg) {
			cout << msg;
			continue;
		}

		/*else {
			cout << "input contains wrong symbols. \n" <<
				"correct symbols: + - * / ( ) \"space\" 0-9 a-z a-z \n" <<
				"please, repeat input\n";
			continue;
		}*/

		
		cout << "-- Debugging --\n"
			<< input << endl;
		system("pause");

	} while (!inputIsCorrect);
	system("pause");
}

void expressionCheck(string input) {
	//searching incorrect symbols
	regex mask1("[^A-Za-z0-9\\s\\+\\-\\*\\/\\(\\)]"); 
	if (std::regex_search(input, mask1))
		/*
		Error! Input contains wrong symbols.
		Correct symbols: + - * / ( ) \"space\" 0-9 a-z a-z
		Please, repeat input
		*/
		throw "Error! Input contains wrong symbols. \nCorrect symbols: + - * / ( ) \"space\" 0-9 a-z a-z \nPlease, repeat input.\n";

	//searching incorrect sequence of characters
	mask1 = "[A-Za-z\\+\\-\\*\\/]{2}"; // "+--*/++--**// xx yy" sequences
	if (std::regex_search(input, mask1))
		/*
		Error! Input contains wrong sequence of characters.
		Correct example: (x + 3) * Y
		Incorrect sequences example: +--* /++--** // xx yy
		Please, repeat input.
		*/
		throw "Error! Input contains wrong sequence of characters. \nCorrect example: (x + 3) * Y\nIncorrect sequences example: +--*/++--**// xx yy \nPlease, repeat input.\n";

	mask1 = "([A-Za-z0-9]\\()|(\\)[A-Za-z0-9])|(\\(\\))"; // "() 5( )5 x( )x Y( )Y" sequences
	if (std::regex_search(input, mask1))
		/*
		Error! Input contains wrong sequence of characters.
		Correct example: (x + 3) * Y
		Incorrect sequences example: () 5( )5 x( )x Y( )Y
		Please, repeat input.
		*/
		throw "Error! Input contains wrong sequence of characters. \nCorrect example: (x + 3) * Y\nIncorrect sequences example: () 5( )5 x( )x Y( )Y \nPlease, repeat input.\n";
	
	//counting opened and closed brackets
	if (!bracketCheck(input))
		/*
		Error! The number of opening brackets does not match the number of closing brackets.
		Correct example: (x + (3 - 1)) * Y
		Incorrect example: (x + (3 - q) * Y
		Please, repeat input.
		*/
		throw "Error! The number of opening brackets does not match the number of closing brackets. \nCorrect example: (x + (3 - 1)) * Y\nIncorrect example: (x + (3 - q) * Y \nPlease, repeat input.\n";
}

bool bracketCheck(string input) {
	int openedBracket = 0;
	int closedBracket = 0;
	for (int i = 0; i < input.length(); i++)
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