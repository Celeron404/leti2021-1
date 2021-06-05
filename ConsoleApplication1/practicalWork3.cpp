#include <iostream>
#include <string>
#include <regex>
using namespace std;


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
		cin >> input;

		if (isExpression(input))
			//remove spaces
			for (int i = 0; i < input.length(); i++)
			{
				if (input[i] == ' ')
					input.erase(i, 1);
			}
		else {
			cout << "Input contains wrong symbols. \n" <<
				"Correct symbols: + - * / ( ) \"space\" 0-9 a-z A-Z \n" <<
				"Please, repeat input\n";
			continue;
		}

		bool checkExpr = expressionIsCorrect(input, exprType);
	} while (!inputIsCorrect);
	system("pause");
}

bool isExpression(string input) {
	regex mask("[^A-Za-z0-9\s\+\-\*\/\(\)]");
	if (std::regex_search(input, mask))
		return false;
	true;
}

bool expressionIsCorrect(string input, short exprType) {
	switch (exprType) {
	case 1:
	}
}