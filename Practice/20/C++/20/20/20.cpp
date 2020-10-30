#include <iostream>
#include <string>
using namespace std;
int main()
{
	int n,k, in;
	cin >> n >> k;
	double min = n + 1, cmax = 0;
	string *a = new string[k];
	int *b = new int[k];
	int *c = new int[k];
	for (int i = 0; i < k; i++) {
		cin >> a[i] >> b[i] >> c[i];
		if (b[i] / c[i] <= min && c[i] > cmax) { min = b[i]; in = i; }
	}
	if (min == n + 1) cout << -1;
	else cout << a[in] << " " << n / b[in] << endl << n / b[in] * c[in] << endl << n - n / b[in] * b[in] << endl;
}