#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int n, a = 1, b = 0;
	cout << "Введите число.\n";
	cin >> n;
	for (int i = 1; i <= n; i++) {
		if (i == a) {
			b++;
			a *= 2;
		}
	}
	cout << "Степеней двойки: " << b;
}