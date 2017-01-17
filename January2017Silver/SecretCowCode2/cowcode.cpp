#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char cowcode(const string is, const long long n) {
	int l = (int)is.length();
	string s(is);
	long long lstring = n + (l - (n % l));

	for (int i = 1; i < (n / l) + 1; ++i) {
		string storage;
		storage.resize((int)s.length(), 'a');
		for (int a = 0; a < (int)s.length(); ++a) {
			if (a - (i % l) < 0) {
				storage[a] = is[a - (i % l) + l];
			}
			else {
				storage[a] = is[a - (i % l)];
			}
		}
		s.insert(((int)s.length()), storage);
	}

	return s[n];
}

int main() {
	ofstream fout("cowcode.out");
	ifstream fin("cowcode.in");
	string is;
	fin >> is;
	long long n;
	fin >> n;

	fout << cowcode(is, n) << endl;
	return 0;
}