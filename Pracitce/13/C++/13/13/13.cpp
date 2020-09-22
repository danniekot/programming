#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int n;
	bool b = 0;
	cout << "Введите натуральное число\n";
	cin >> n;
	for (int i = 2; i < n; i++) {
		if (n % i == 0)
			b = 1;
	}
	if (n <= 1)
		cout << "Ни простое, ни составное";
	else if (b == 1)
		cout << "Составное";
	else
		cout << "Простое";
}