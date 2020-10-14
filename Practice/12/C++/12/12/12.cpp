#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int n, a = 1;
	cout << "Здравствуйте! Введите число.\n";
	cin >> n;
	for (int i = 1; i <= n; i++) {
		a *= i;
	}
	cout << n << "! = " << a;
}