#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Введите основание и показатель степени.\n";
	int a, b, s;
	cin >> a >> b;
	s = a;
	for (int i = 1; i < b; i++) {
		s *= a;
	}
	cout << a << " в степени " << b << " даёт " << s << "\n";
}