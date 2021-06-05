#include <iostream>
using namespace std;


void practicalWork3() {
	system("CLS");
	cout << "Solution of task \"Working with stacks and queues, learning direct and reverse polish notation.\n";
	bool inputIsCorrect = false;
	do {
		cout << "\nEnter the type of expression:\n"
			<< "1) Simple notation\n"
			<< "2) Direct polish notation\n"
			<< "3) Reverse polish notation\n>> ";
		int exprType;
		cin >> exprType;
		if (exprType == 1 || exprType == 2 || exprType == 3) {
			inputIsCorrect = true;
			break;
		}
		cout << "Error: wrong input. Please repeat menu selection.\n";
	} while (!inputIsCorrect);
	system("pause");
}