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
#include <unordered_map>

using namespace std;

#define MAXITEMS 6

int main() {
	ofstream fout("shopping.out");
	ifstream fin("shopping.in");
	int s;
	fin >> s;
	vector<tuple<int, vector<tuple<int, int>>>> salesRecord(s); // tuple of price and vector of item code and number of items
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
		salesRecord[x] = make_tuple(p, items);
	}

	int b;
	fin >> b;
	vector<tuple<int, int, int>> items(MAXITEMS, make_tuple(0, 0, 0));
	unordered_map<int, int> codes(b);
	for (int z = 0; z < b; ++z) {
		int c, k, p;
		fin >> c >> k >> p;
		items[z] = make_tuple(c, k, p);
		codes[c] = z;
	}

	vector<tuple<int, vector<int>>> sales(s, make_tuple(0, vector<int>(MAXITEMS, 0)));
	for (int a = 0; a < s; ++a) {
		vector<int> included(MAXITEMS, 0);
		int currprice = get<0>(salesRecord[a]);
		vector<tuple<int, int>> currVect = get<1>(salesRecord[a]);
		for (int d = 0; d < (int)currVect.size(); ++d) {
			included[codes[get<0>(currVect[d])]] = get<1>(currVect[d]);
		}
		sales[a] = make_tuple(currprice, included);
	}

	vector<int> wanted(MAXITEMS, 0);
	for (int e = 0; e < b; ++e) {
		wanted[codes[get<0>(items[e])]] = get<1>(items[e]);
	}

	int matrix[MAXITEMS][MAXITEMS][MAXITEMS][MAXITEMS][MAXITEMS];

	// fill with non-sale prices
	for (int i = 0; i < MAXITEMS; ++i) {
		for (int j = 0; j < MAXITEMS; ++j) {
			for (int k = 0; k < MAXITEMS; ++k) {
				for (int l = 0; l < MAXITEMS; ++l) {
					for (int m = 0; m < MAXITEMS; ++m) {
						matrix[i][j][k][l][m] = (get<2>(items[0]) * i) + (get<2>(items[1]) * j) + (get<2>(items[2]) * k) + (get<2>(items[3]) * l) + (get<2>(items[4]) * m);
						//cout << "Items " << i << "," << j << "," << k << "," << l << "," << m << "=" << matrix[i][j][k][l][m] << endl; 
					}
				}
			}
		}
	}

	// go through and check the sale prices
	for (int i = 0; i < MAXITEMS; ++i) {
		for (int j = 0; j < MAXITEMS; ++j) {
			for (int k = 0; k < MAXITEMS; ++k) {
				for (int l = 0; l < MAXITEMS; ++l) {
					for (int m = 0; m < MAXITEMS; ++m) {
						int best = matrix[i][j][k][l][m];
						for (int n = 0; n < s; ++n) {
							vector<int> &salesnums = get<1>(sales[n]);
							if (i >= salesnums[0] && j >= salesnums[1] && k >= salesnums[2] && l >= salesnums[3] && m >= salesnums[4]) { // works
								int newnum = matrix[i - salesnums[0]][j - salesnums[1]][k - salesnums[2]][l - salesnums[3]][m - salesnums[4]] + get<0>(sales[n]);
								if (newnum < best) {
									best = newnum;
								}
							}
						}
						matrix[i][j][k][l][m] = best;
					}
				}
			}
		}
	}

	fout << matrix[wanted[0]][wanted[1]][wanted[2]][wanted[3]][wanted[4]] << endl;
	return 0;
}