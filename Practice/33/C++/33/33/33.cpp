#include <iostream>
using namespace std;
int *create(int n, int a0, int step) {
	int *a = new int[n];
	for (int i = 0; i < n; i++)
		a[i] = a0 + step * i;
	return a;
}
int *sort(int *a, int n) {
	int temp, k;
	for (int i = 1; i < n; i++) {
		temp = a[i];
		k = i - 1;
		while (k >= 0 && a[k] > temp) {
			a[k + 1] = a[k];
			a[k] = temp;
			k--;
		}
	}
	return a;
}
int *print(int *a, int n) {
	cout << "[";
	for (int i = 0; i < n - 1; ++i)
		cout << a[i] << ", ";
	cout << a[n - 1] << "]";
	return a;
}
int main() {
	int n, a0, step;
	cin >> n >> a0 >> step;
	int *a = create(n, a0, step);
	print(sort(a, n), n);
	delete[]a;
}