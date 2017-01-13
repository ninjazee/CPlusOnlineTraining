/*
ID: kml111
PROG: crypt1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void digitsprint(int n, vector<int> &digitsn) {
	if (n >= 10) {
		digitsprint(n / 10, digitsn);
	}
	int digit = n % 10;
	digitsn.push_back(digit);
}

bool isPrime(int n) {
	for (int i = 2; i <= n / 2; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

int primeCryptarithm(vector<int> &digits) {
	vector<int> products;
	int z = (int)digits.size();
	sort(digits.begin(), digits.end());
	for (int a = 0; a < z; ++a) {
		for (int b = 0; b < z; ++b) {
			for (int c = 0; c < z; ++c) {
				for (int d = 0; d < z; ++d) {
					for (int e = 0; e < z; ++e) {
						bool works = true;
						/*
						if (isPrime(digits[a]) == false) {
							works = false;
						}
						else if (isPrime(digits[b]) == false) {
							works = false;
						}
						else if (isPrime(digits[c]) == false) {
							works = false;
						}
						else if (isPrime(digits[d]) == false) {
							works = false;
						}
						else if (isPrime(digits[e]) == false) {
							works = false;
						}
						*/
						vector<int> digitsn;
						int product = (digits[a] * 100 + digits[b] * 10 + digits[c]) * (digits[d] * 10 + digits[e]);
						digitsprint(product, digitsn);
						for (int i : digitsn) {
							auto it = find(digits.begin(), digits.end(), i);
							if (it == digits.end()) {
								works = false;
								break; break;
							}
						}
						vector<int> digitse;
						int en = (digits[e] * (digits[a] * 100 + digits[b] * 10 + digits[c]));
						digitsprint(en, digitse);
						for (int j : digitse) {
							auto it = find(digits.begin(), digits.end(), j);
							if (it == digits.end()) {
								works = false;
								break; break;
							}
						}
						vector<int> digitsd;
						int dn = (digits[d] * (digits[a] * 100 + digits[b] * 10 + digits[c]));
						digitsprint(dn, digitsd);
						for (int k : digitsd) {
							auto it = find(digits.begin(), digits.end(), k);
							if (it == digits.end()) {
								works = false;
								break; break;
							}
						}

						if (works == true) {
							if (product / 1000 >= 1 && product / 1000 <= 10) {
								if (en / 100 >= 1 && en / 100 <= 10) {
									if (dn / 100 >= 1 && dn / 100 <= 10) {
										products.push_back(product);
									}
								}

							}
						}
					}
				}
			}
		}
	}

	return (int)products.size();
}

int main() {
	ofstream fout("crypt1.out");
	ifstream fin("crypt1.in");
	int n;
	fin >> n;
	vector<int> digits(n);
	for (int x = 0; x < n; ++x) {
		int digit;
		fin >> digit;
		digits[x] = digit;
	}

	fout << primeCryptarithm(digits) << endl;
	return 0;
}