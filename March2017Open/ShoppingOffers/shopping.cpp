/*
ID: kml111
PROG: shopping
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

#define MAXITEMS 6

int main() {
	ofstream fout("shopping.out");
	ifstream fin("shopping.in");
	int s;
	fin >> s;
	vector<tuple<int, vector<tuple<int, int>>>> sales(s); // tuple of price and vector of item code and number of items
	for (int x = 0; x < s; ++x) {
		int n;
		fin >> n;
		vector<tuple<int, int>> items(n); // vector of item code and number of items
		for (int y = 0; y < n; ++y) {
			int c, k;
			fin >> c >> k;
			items[y] = make_tuple(c, k);
		}
		int p; // price
		fin >> p;
		sales[x] = make_tuple(p, items);
	}

	int b;
	fin >> b;
	vector<tuple<int, int, int>> items(b);
	for (int z = 0; z < b; ++z) {
		int c, k, p;
		fin >> c >> k >> p;
		items[z] = make_tuple(c, k, p);
	}

	int matrix[MAXITEMS][MAXITEMS][MAXITEMS][MAXITEMS][MAXITEMS];

	return 0;
}