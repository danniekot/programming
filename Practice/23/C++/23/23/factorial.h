#pragma once
long long factor(int n) {
	long long fact = 1;
	for (int i = 1; i <= n; i++)
		fact *= i;
	return fact;
}