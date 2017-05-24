/*
ID: kml111
PROG: fact4
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

void primeFactorization(const int a, vector<int> &primeFactors) {
	int num = a;
	
	// add how many 2s are in this number
	while (num % 2 == 0) {
		primeFactors.push_back(2);
		num /= 2;
	}

	// n is now odd, we can jump over even factors
	for (int i = 3; i < sqrt(num); i += 2) {
		// add how many is are in this number
		while (num % i == 0) {
			primeFactors.push_back(i);
			num /= i;
		}
	}

	// if the number left is a prime number greater than 2, add it
	if (num > 2) {
		primeFactors.push_back(num);
	}
}

int power(const int base, const int power) {
	int b = base;
	for (int i = 0; i < power - 1; ++i) {
		b *= base;
		b %= 10;
	}
	return b;
}

int factorials(const int n) {
	int twos = 0;
	int fives = 0;
	vector<int> factors;
	for (int i = 2; i <= n; ++i) { // for every factor of n!
		int num = i;
		while (num % 2 == 0) { // add how many twos there are
			twos += 1;
			num /= 2;
		}
		while (num % 5 == 0) { // add how many fives there are
			fives += 1;
			num /= 5;
		}
		if (num > 2) {
			factors.push_back(num); // add remaining number to the factors.
		}
	}

	long long total25 = 1;
	if (twos > fives) { // there are more twos than fives, only add the twos
		total25 = power(2, (twos - fives));
	}
	else if (fives > twos) { // there are more fives than twos, only add the fives
		total25 = power(5, (fives - twos));
	}
	else { // there are the same number, they cancel each other out
		total25 = 1;
	}

	long long total = 1;
	for (int j = 0; j < (int)factors.size(); ++j) {
		total *= factors[j];
		total %= 10;
	}
	return (total * total25) % 10;
}

int main() {
	ofstream fout("fact4.out");
	ifstream fin("fact4.in");
	int n;
	fin >> n;
	fout << factorials(n) << endl;
	return 0;
}