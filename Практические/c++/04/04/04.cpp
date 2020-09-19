#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Введите два целых числа\n";
	int a, b, temp;
	cin >> a >> b;
	temp = a; a = b; b = temp;
	cout << "После замены первое число равно " << a << ", а второе " << b << "\n";
	cout << "Введите два целых числа\n";
	cin >> a >> b;
	a += b; b = a - b; a -= b;
	cout << "После замены первое число равно " << a << ", а второе " << b << "\n";
}