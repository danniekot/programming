#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Введите время прихода первого человека и время прихода второго человека через двоеточие.\n";
	double a, b, c, d;
	char s, t;
	cin >> a >> s >> b >> c >> t >> d;
	if (s == ':' && t == ':')
		if (a == c && abs(b - d) <= 15 || abs(a - c) == 1 && abs(b - d - 60) <= 15) {
			cout << "Встреча состоится!";
		}
		else
			cout << "Встреча не состоится!";
	else
		cout << "Ошибка. Введите корректное значение.";
}