#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char cowcode(const string is, const long long n) {
	int l = (int)is.length();
	string s (is);
	long long lstring = n + (l - (n % l));

	for (int i = 1; i < (lstring - l) / l + 1; ++i) {
		string storage;
		storage.resize(l, 'a');
		for (int a = 0; a < l; ++a) {
			if (a + (i % l) >= l) {
				storage[a] = is[a + (i % l) - l];
			}
			else {
				storage[a] = is[a + (i % l)];
			}
		}
		s.insert(((int)s.length()), storage);
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
	
	fout << cowcode(is, n) << endl;
	return 0;
}