#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Введите целое число, затем начальную и конечную точку первого и второго диапазона.\n";
	int s, l1, r1, l2, r2, x1;
	cin >> s >> l1 >> r1 >> l2 >> r2;
	x1 = l1 < r1 ? l1 : r1;
	if (x1 + l2 == s)
		cout << x1 << " " << l2;
	else if (x1 + r2 == s)
		cout << x1 << " " << r2;
	else {
		if (x1 + l2 == s)
			cout << x1 << " " << l2;
		else if (x1 + r2 == s)
			cout << x1 << " " << r2;
		else
			cout << -1;
	}
}