# include "30.h"
# include <iostream>
using namespace std;
int main() {
	std::string input;
	while (true) {
		cout << "Открыть лутбокс? Yes/No" << endl;
		cin >> input;
		if (input == "Y" or input == "y" or input == "Yes" or input == "yes") {
			auto box = generateLootBox();
			cout << box << endl;
		}
		else if (input == "N" or input == "n" or input == "No" or input == "no")
			break;
	}
};
