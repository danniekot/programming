#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
	int n;
	cout << "Введите число: ";
	cin >> n;
	vector <pair<int, int>> ans;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0) {
			ans.push_back(make_pair(i, 0));
			while (n % i == 0) {
				n /= i;
				ans[ans.size() - 1].second++;
			}
		}
	if (n > 1)
		ans.push_back(make_pair(n, 1));
	sort(ans.begin(), ans.end(), [](auto a, auto b) { return a.first < b.first; });
	for (int i = 0; i < ans.size(); i++) {
		auto divider = ans[i];
		if (divider.second > 1) {
			string format = (i == 0 ? "%d^%d" : "*%d^%d ");
			cout << format.c_str(), ans[i].first, ans[i].second;
		}
		else {
			string format = (i == 0 ? "%d" : "*%d");
			cout << format.c_str(), ans[i].first;
		}
	}
	cout << "\n";
}