/*
ID: kml111
PROG: runround
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int count_digits(int num) { // count number of digits in number
	int count = 0;
	while (num != 0) {
		count++;
		num /= 10;
	}
	return count;
}

int power(const int base, const int power) { // exponent function
	if (power == 0) {
		return 1;
	}
	else {
		int b = base;
		for (int i = 0; i < power - 1; ++i) {
			b *= base;
		}
		return b;
	}
}

void reverseVector(vector<int> &v) {
	vector<int> temp(v);
	for (int i = 0; i < (int)v.size(); ++i) {
		v[i] = temp[(int)v.size() - 1 - i];
	}
}

void intToVector(const int x, vector<int> &v) { // convert integer to vector
	int totalNotUsing = 0;
	for (int i = 1; i < count_digits(x) + 1; ++i) {
		int digit = (x % (power(10, i)) - totalNotUsing) / power(10, i - 1);
		v.push_back(digit);
		totalNotUsing += x % (power(10, i)) - totalNotUsing;
	}
	reverseVector(v);
}

bool distinctDigits(const vector<int> &x) {
	vector<bool> seen(128);
	for (int i = 0; i < (int)x.size(); ++i) {
		if (seen[x[i]]) {
			return false;
		}
		if (x[i] == 0) {
			return false;
		}
		seen[x[i]] = true;
	}
	return true;
}

bool isRunaround(const vector<int> &n) { // check if int is runaround number
	vector<bool> seen(10);
	if (distinctDigits(n) == false) {
		return false;
	}
	int len = (int)n.size();
	int curr = 0;
	seen[n[0]] = true;
	for (int j = 1; j < len + 1; ++j) {
		int compare = n[curr];
		for (int i = 0; i < compare; ++i) {
			if (curr == len - 1) {
				curr = 0;
			}
			else {
				curr += 1;
			}
		}
		if (seen[n[curr]] && j != len) {
			return false;
		}
		seen[n[curr]] = true;
	}
	if (n[curr] == n[0]) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	ofstream fout("runround.out");
	ifstream fin("runround.in");
	int m;
	fin >> m;
	m += 1;
	vector<int> mvect;
	intToVector(m, mvect);
	//cout << isRunaround(mvect) << endl;
	while (isRunaround(mvect) == false) {
		m += 1;
		mvect.clear();
		intToVector(m, mvect);
	}
	fout << m << endl;
	return 0;
}