#include <iostream>
#include <iomanip>
#include "factorial.h"
#include "sinus.h"
#include "sochetaniya.h"
using namespace std;
const double pi = 3.141592, tl_step = pi / 180, tl_lim = pi / 4;
const int comb_n = 10;

int main() {
	/* ~ factorials ~ */
	cout << "n" << "\t" << "n!" << endl;
	for (int i = 1; i <= 10; i++)
		cout << i << "\t" << factor(i) << endl;
	cout << endl;

	/* ~ Taylor series ~ */
	cout << "x" << "\t" << "sin(x)" << endl;
	for (double i = 0; i <= tl_lim; i += tl_step) {
		cout << setprecision(4) << i << "\t";
		cout << sin(i, 5) << endl;
	}
	cout << endl;
	/* ~ combinations ~ */
	cout << "k" << "\t" << "C(k, " << comb_n << ")" << endl;
	for (int i = 1; i <= 10; i++)
		cout << i << "\t" << comb(i, comb_n) << endl;
}