#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

char cowcode(vector<char> &s, const long long n) {
	long long lstring = (long long)s.size();
	int recursions = 1;
	while (lstring < n) {
		lstring *= 2;
		recursions += 1;
	}

	for (int i = 0; i < recursions; ++i) {
		long long size = (long long)s.size();
		for (int a = 0; a < size; ++a) {
			char c;
			if (a == 0) {
				c = s[size - 1];
			}
			else {
				c = s[a - 1];
			}
			s.push_back(c);
		}
	}

	return s[n - 1];
}

int main() {
	ofstream fout("cowcode.out");
	ifstream fin("cowcode.in");
	string is;
	fin >> is;
	long long n;
	fin >> n;

	vector<char> s ((int)is.size());
	for (int x = 0; x < (int)is.size(); ++x) {
		s[x] = is[x];
	}
	fout << cowcode(s, n) << endl;
	return 0;
}