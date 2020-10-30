#include <iostream>
using namespace std;
int main() {
	long long yes[37], no[37], r = 0, b = 0, n = 0;
	for (int i = 0; i < 37; i++) {
		no[i] = 1;
		yes[i] = 0;
	}
	while (1) {
		cin >> n;
		if (n < 0) break;
		if (n == 1 || n == 3 || n == 5 || n == 7 || n == 9 || n == 12 || n == 14 || n == 16 || n == 18 || n == 19 || n == 21 || n == 23 || n == 25 || n == 27 || n == 30 || n == 32 || n == 34 || n == 36)
			r++;
		else if (n != 0)
			b++;
		yes[n]++;
		no[n] = 0;
		int maxi = yes[0];
		for (int i = 0; i < 37; i++)
			if (yes[i] > maxi)
				maxi = yes[i];
		for (int i = 0; i < 37; i++)
			if (yes[i] == maxi)
				cout << i << " ";
		cout << "\n";
		for (int i = 0; i < 37; i++)
			if (no[i] == 1)
				cout << i << " ";
		cout << "\n" << r << " " << b << "\n\n";
		no[n] = 0;
	}
}