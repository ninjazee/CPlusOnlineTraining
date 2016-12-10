#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void checkDigits2(string base2, vector<int> &base2nums) {
	base2nums[0] = strtol(base2.data(), NULL, 2);
	for (int c = 0; c < base2.length(); ++c) {
		string s = base2;
		if (base2[c] == '0') {
			s[c] = '1';
		}
		else {
			s[c] = '0';
		}
		base2nums[c+1] = strtol(s.data(), NULL, 2);
	}
}

void checkDigits3(string base3, vector<int> &base3nums) {
	base3nums[0] = strtol(base3.data(), NULL, 3);
	for (int c = 0; c < base3.length(); ++c) {
		string s = base3;
		if (base3[c] == '0') {
			string s = base3;
			s[c] = '1';
			base3nums[c * 2] = strtol(s.data(), NULL, 3);
			string t = base3;
			t[c] = '2';
			base3nums[c * 2 + 1] = strtol(t.data(), NULL, 3);
		}
		else if (s[c] == '1') {
			string s = base3;
			s[c] = '0';
			base3nums[c * 2] = strtol(s.data(), NULL, 3);
			string t = base3;
			t[c] = '2';
			base3nums[c * 2 + 1] = strtol(t.data(), NULL, 3);
		}
		else {
			string s = base3;
			s[c] = '0';
			base3nums[c * 2] = strtol(s.data(), NULL, 3);
			string t = base3;
			t[c] = '1';
			base3nums[c * 2 + 1] = strtol(t.data(), NULL, 3);
		}
	}
}

int main() {
	ofstream fout("digits.out");
	ifstream fin("digits.in");
	string base2, base3;
	fin >> base2;
	fin >> base3;
	int n2 = base2.length() + 1;
	int n3 = base3.length() * 2 + 1;
	vector<int> base2nums(n2);
	vector<int> base3nums(n3);
	checkDigits2(base2, base2nums);
	checkDigits3(base3, base3nums);
	for (int x = 0; x < n2; ++x) {
		for (int y = 0; y < n3; ++y) {
			if (base2nums[x] == base3nums[y]) {
				cout << base2nums[x];
			}
		}
	}
	return 0;
}