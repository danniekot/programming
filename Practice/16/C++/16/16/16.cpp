#include <iostream>
#include <string>
using namespace std;
int main() {
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Введите число\n";
	int n;
	cin >> n;
	cout << "Введите " << n << " № билетов в таком виде: аа0000000\n";
	string s = "";
	for (int i = 0; i < n; i++) {
		string a;
		cin >> a;
		if (a[0] == 'a' && a[4] == '5' && a[5] == '5' && a[6] == '6' && a[7] == '6' && a[8] == '1')
			s += a + " ";
	}
	if (s == "")
		cout << "-1\n";
	else
		cout << s << "\n";
}