#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Введите два числа, а между ними знак нужного действия.\n";
	double a, b;
	char s;
	cin >> a >> s >> b;
	if (s == '+') {
		cout << "Cумма чисел составляет " << a + b;
	}
	else if (s == '-') {
		cout << "Разность чисел составляет " << a - b;
	}
	else if (s == '*') {
		cout << "Произведение чисел составляет " << a * b;
	}
	else if (s == '/') {
		cout << "Частное чисел составляет " << a + b;
	}
	else cout << "Вы ввели неверный знак.";
}