#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
    cout << "Введите три коэффициента квадратного уравнения\n";
	double a, b, c, D;
	cin >> a >> b >> c;
	D = b * b - 4 * a * c;
	if (D > 0) {
		cout << "Уравнение имеет два корня: " << (-1 * b + sqrt(D)) / (2 * a) << " и " << (-1 * b - sqrt(D)) / (2 * a) << "\n";
	}
	else if (D == 0) {
		cout << "Уравнение имеет один корень: " << (-1 * b) / (2 * a) << "\n";
	}
	else cout << "Уравнение не имеет корней\n";
}