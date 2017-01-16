#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

void cowTipping(vector<string> &cowgrid, int &count) {
	int n = (int)cowgrid.size();
	int lrd = 0;
	int lrr = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (cowgrid[i][j] == '1') {
				lrd = i;
				lrr = j;
			}
		}
	}

	for (int a = 0; a < (lrd + 1); ++a) {
		for (int b = 0; b < (lrr + 1); ++b) {
			if (cowgrid[a][b] == '0') {
				cowgrid[a][b] = '1';
			}
			else {
				cowgrid[a][b] = '0';
			}
		}
	}

	for (int x = 0; x < n; ++x) {
		for (int y = 0; y < n; ++y) {
			if (cowgrid[x][y] == '1') {
				count += 1;
				cowTipping(cowgrid, count);
			}
		}
	}
}

int main() {
	ofstream fout("cowtip.out");
	ifstream fin("cowtip.in");
	int n;
	fin >> n;
	vector<string> cowgrid(n);
	for (int x = 0; x < n; ++x) {
		string line;
		fin >> line;
		cowgrid[x] = line;
	}
	int count = 1;
	cowTipping(cowgrid, count);
	fout << count << endl;
	return 0;
}