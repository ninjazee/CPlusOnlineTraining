/*
ID: kml111
PROG: fence9
LANG: C++11
*/

#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ofstream fout("fence9.out");
	ifstream fin("fence9.in");
	int n, m, p;
	fin >> m >> n >> p;

	int count = 0;
	for (int i = 1; i < n; ++i) {
		int borderCount1 = m * i / n;
		int borderCount2 = (( p * n) - (p - m) * i )/ n;
		if ((p - m)*i % n == 0)
			borderCount2--;
		count += borderCount2 - borderCount1;
		// cout << borderCount1 << "\t" << borderCount2 << endl;
	}

	fout << count << endl;
	return 0;
}