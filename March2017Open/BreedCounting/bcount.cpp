/*
ID: kml111
PROG: bcount
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

int main() {
	ofstream fout("bcount.out");
	ifstream fin("bcount.in");
	int n, q;
	fin >> n >> q;
	vector<int> cowrow(n);
	for (int x = 0; x < n; ++x) {
		int cow; 
		fin >> cow;
		cowrow[x] = cow;
	}

	vector<tuple<int, int>> queries(q);
	for (int y = 0; y < q; ++y) {
		int a, b;
		fin >> a >> b;
		queries[y] = make_tuple(a - 1, b - 1);
	}

	vector<tuple<int, int, int>> cowTally(n);
	for (int i = 0; i < n; ++i) {
		if (i != 0) {
			cowTally[i] = cowTally[i - 1];
		}
		
		if (cowrow[i] == 1) {
			get<0>(cowTally[i]) += 1;
		}
		else if (cowrow[i] == 2) {
			get<1>(cowTally[i]) += 1;
		}
		else {
			get<2>(cowTally[i]) += 1;
		}
	}

	for (int j = 0; j < q; ++j) {
		int startnum = get<0>(queries[j]);
		int endnum = get<1>(queries[j]);
		if (startnum == 0) { // this one is at the beginning, no subtraction necessary
			fout << get<0>(cowTally[endnum]) << ' ' << get<1>(cowTally[endnum]) << ' ' << get<2>(cowTally[endnum]) << endl;
		}
		else {
			fout << get<0>(cowTally[endnum]) - get<0>(cowTally[startnum - 1]) << ' ' << get<1>(cowTally[endnum]) - get<1>(cowTally[startnum - 1]) << ' ' << get<2>(cowTally[endnum]) - get<2>(cowTally[startnum - 1]) << endl;
		}
	}
	return 0;
}