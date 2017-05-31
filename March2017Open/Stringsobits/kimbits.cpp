/*
ID: kml111
PROG: kimbits
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int power(const int base, const int power) {
	int b = base;
	for (int i = 0; i < power - 1; ++i) {
		b *= base;
	}
	return b;
}

int main() {
	ofstream fout("kimbits.out");
	ifstream fin("kimbits.in");
	long long n, l, I;
	fin >> n >> l >> I;

	vector<vector<long long>> combinations(n + 1, vector<long long>(l + 1, 0));
	for (int a = 0; a <= n; ++a) {
		combinations[a][0] = 1;
	}
	for (int b = 0; b <= l; ++b) {
		combinations[0][b] = 1;
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= l; ++j) {
			if (j < i) { // there are less 1s than bits, possible
				combinations[i][j] = combinations[i - 1][j - 1] + combinations[i - 1][j];
			}
			else if (i == j) { //  // the number of ones is the same as the number of bits
				combinations[i][j] = combinations[i - 1][j - 1] * 2;
			}
			else { // there are more 1s than bits, just repeat the one before it
				combinations[i][j] = combinations[i][j - 1];
			}
		}
	}
	/*
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= l; ++j) {
			cout << combinations[i][j] << "\t";
		}
		cout << endl;
	}
	*/

	//cout << combinations[n][l] << endl;
	vector<int> stringobit(n, 1);
	long long currentl = l;
	long long currenti = I;
	for (int currbit = 0; currbit < n; ++currbit) {
		long long cur = combinations[n - 1 - currbit][currentl];
		int curdigit = 0; 
		if (currenti > cur)
		{
			curdigit = 1; 
			currenti -= cur;
			currentl -= 1;
		}
		stringobit[currbit] = curdigit; 
	}

	for (int b = 0; b < n; ++b) {
		fout << stringobit[b];
	}
	fout << endl;
	return 0;
}