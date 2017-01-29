#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

char cowcode(vector<char> &s, const long long n) {
	long long lstring = (long long)s.size();
	while (lstring < n) {
		lstring *= 2;
	}

	long long p = n;
	long long l = lstring;
	while (l > (long long)s.size()) {
		l = lstring / 2;
		if (p < l) {

		}
		else {
			p = (p - 1) % l;
		}
		lstring = l;
	}

	return s[p];
}

int main() {
	ofstream fout("cowcode.out");
	ifstream fin("cowcode.in");
	string is;
	fin >> is;
	long long n;
	fin >> n;

	vector<char> s((int)is.size());
	for (int x = 0; x < (int)is.size(); ++x) {
		s[x] = is[x];
	}
	fout << cowcode(s, (n - 1)) << endl;
	return 0;
}