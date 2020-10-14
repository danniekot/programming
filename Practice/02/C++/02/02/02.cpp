#include <iostream>
#include <locale>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int a = 3, b = 3.14;
	double c = 3, d = 3.14;
	cout << a << ", " << b << endl << c << ", " << d << endl;
}