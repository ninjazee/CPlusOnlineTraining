#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int count_digits(long long num) {
	int count = 0;
	while (num != 0) {
		count++;
		num /= 10;
	}
	return count;
}

int power(const int base, const int power) {
	int b = base;
	for (int i = 0; i < power - 1; ++i) {
		b *= base;
	}
	return b;
}

void reverseVector(vector<int> &v) {
	vector<int> temp(v);
	int vsize = (int)v.size();
	for (int i = 0; i < vsize; ++i) {
		v[i] = temp[vsize - 1 - i];
	}
}

void longlongToVector(const long long x, vector<int> &v) { // convert integer to vector
	int totalNotUsing = 0;
	for (int i = 1; i < count_digits(x) + 1; ++i) {
		int digitwTens = (x % (power(10, i)) - totalNotUsing);
		int digit = digitwTens / power(10, i - 1);
		v.push_back(digit);
		totalNotUsing += digitwTens;
	}
	//reverseVector(v);
}

bool isTidy(const long long n) {
	int d = count_digits(n);
	if (d == 1) { // only one digit; automatically tidy
		return true;
	}
	else { // more than one digit
		int alreadycounted = 0;
		for (int i = 1; i < d; ++i) { // for each digit
			int digit, digit2;
			if (i == 1) { // ones digit
				int p = power(10, i);
				digit = n % p;
				alreadycounted = digit;
				digit2 = (n % power(10, i + 1) - alreadycounted) / p;
			}
			else {
				int p = power(10, i);
				int digitwTens = (n % p - alreadycounted);
				digit = digitwTens / power(10, i - 1);
				alreadycounted += digitwTens;
				digit2 = (n % power(10, i + 1) - alreadycounted) / p;
			}
			if (digit2 > digit) { // digits not in non-decreasing order
				return false;
			}
		}
		return true;
	}
}

long long tidyNumbers(const long long n) {
	long long num = n;
	while (isTidy(num) == false) {
		num -= 1;
	}
	return num;
}

bool isTidyV(const vector<int> &v) {
	int d = (int)v.size();
	if (d == 1) { // only one digit; automatically tidy
		return true;
	}
	else { // more than one digit
		for (int i = 0; i < d - 1; ++i) { // for each digit
			if (v[i + 1] > v[i]) { // digits not in non-decreasing order
				return false;
			}
		}
		return true;
	}
}

vector<int> tidyNumbersV(const long long n) {
	vector<int> v;
	longlongToVector(n, v);
	int num = n;
	while (isTidyV(v) == false) {
		num -= 1;
		longlongToVector(num, v);
	}
	return v;
}

int main() {
	int t;
	cin >> t;
	for (int a = 0; a < t; ++a) {
		long long n;
		cin >> n;
		cout << "Case #" << a + 1 << ": " << tidyNumbers(n) << endl;
		/*
		for (int b = 0; b < (int)v.size(); ++b) {
			cout << v[b];
		}
		cout << endl;
		*/
	}
	return 0;
}