#ifndef vercetti
#define vercetti
#include "factorial.h"
int comb(int k, int n) {
	return factor(n) / factor(k) / factor(n - k);
}
#endif