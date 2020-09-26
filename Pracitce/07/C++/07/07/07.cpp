#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int n;
	cout << "Введите число 1, если требуется найти площадь треугольника по длинам сторон.\nНажмите 2, если требуется найти площадь треугольника по его координатам\n";
	cin >> n;
	if (n == 1) {
		cout << "Введите длины сторон треугольника\n";
		double a, b, c, p;
		cin >> a >> b >> c;
		p = (a + b + c) / 2;
		cout << "Площадь данного треугольника составляет " << sqrt(p*(p - a)*(p - b)*(p - c));
	}
	else if (n == 2) {
		cout << "Введите координаты вершин треугольника\n";
		double a, b, c, d, e, f, A, B, C, p;
		cin >> a >> b >> c >> d >> e >> f;
		A = sqrt((a - c)*(a - c)+(b - d)*(b - d));
		B = sqrt((a - e)*(a - e)+(b - f)*(b - f));
		C = sqrt((e - c)*(e - c)+(f - d)*(f - d));
		p = (A + B + C) / 2;
		cout << "Площадь данного треугольника составляет " << sqrt(p*(p - A)*(p - B)*(p - C));
	}
	else cout << "Ошибочный ввод";
}