#ifndef dantes
#define dantes
#include "factorial.h"
#include <iostream>
double powex(double x, double j, double k) {
	for (int i = 1; i <= k; i++)
		x *= j;
	return x;
}
double sin(double x, int k) {
	double sin = 0;
	double powx = 1;
	double factx, term = 1;
	for (int i = 1; i <= k; i++) {
		powx = powex(powx, x, (i == 1) ? 1 : 2);
		factx = factor(i * 2 - 1);
		term = powx / factx;
		if (i % 2 == 0)
			term = -term;
		sin = sin + term;
	}
	return sin;
}
#endif