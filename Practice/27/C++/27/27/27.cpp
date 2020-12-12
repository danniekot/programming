#include <iostream>
#include <vector>
void pushSort(std::vector<int>& arr, int element) {
	arr.push_back(element);
	int j = arr.size() - 2;
	while (j >= 0 && arr[j] < element) {
		arr[j + 1] = arr[j];
		j--;
	}
	arr[j + 1] = element;
}
template <typename T>
void printVector(std::vector<T> arr, std::string before = "", std::string delim = " ") {
	std::cout << before;
	for (auto& it : arr)
		std::cout << it << delim;
}
template <typename T>
std::vector<T> sliceVector(std::vector<T> arr, int startIndex, int endIndex)
{
	size_t len = arr.size();
	if (startIndex < 0)
		startIndex = len + startIndex;
	if (endIndex <= 0)
		endIndex = len + endIndex - 1;
	auto start = arr.begin() + startIndex;
	auto end = arr.begin() + endIndex + 1;

	std::vector<T> result(endIndex - startIndex + 1);
	copy(start, end, result.begin());
	return result;
}
int main() {
	int n;
	std::cout << "Введите число сигналов: ";
	std::cin >> n;
	int *signals = new int[n];
	std::vector<int> visible;
	int signal, i, j;
	std::cout << "Массив сигналов: ";
	for (i = 0; i < n; i++) {
		std::cin >> signal;
		signals[i] = signal;
	}
	for (i = 0; i < n; i++) {
		signal = signals[i];
		pushSort(visible, signal);
		size_t visibleLen = visible.size();

		printVector(sliceVector(visible, (visibleLen > 5 ? -5 : 0), 0));
		std::cout << std::endl;
	}
}