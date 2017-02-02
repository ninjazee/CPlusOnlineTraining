#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int contaminatedMilk(int n, int m, const vector<vector<int>> &milkRecord, const vector<int> &sickRecord) {
	int highest = 0;
	for (int i = 0; i < m; ++i) {
		int count = 0;
		for (int j = 0; j < n; ++j) {
			int time = milkRecord[j][i];
			if (sickRecord[j] <= time) {
				count = 0;
				break;
			}
			else {
				if (sickRecord[j] < numeric_limits<int>::max() && time == 0) {
					count = 0;
					break;
				}
				else if (time != 0) {
					count += 1;
				}
			}
		}

		if (count > highest) {
			highest = count;
		}
	}

	return highest;
}

int main() {
	ofstream fout("badmilk.out");
	ifstream fin("badmilk.in");
	int n, m, d, s;
	fin >> n >> m >> d >> s;
	vector<vector<int>> milkRecord(n, vector<int>(m));
	for (int a = 0; a < d; ++a) {
		int p, m, t;
		fin >> p >> m >> t;
		if (milkRecord[p - 1][m - 1] == 0) {
			milkRecord[p - 1][m - 1] = t;
		}
		else {
			if (t < milkRecord[p - 1][m - 1]) {
				milkRecord[p - 1][m - 1] = t;
			}
		}
	}

	vector<int> sickRecord(n,numeric_limits<int>::max());
	for (int b = 0; b < s; ++b) {
		int p, t;
		fin >> p >> t;
		sickRecord[p - 1] = t;
	}
	fout << contaminatedMilk(n, m, milkRecord, sickRecord) << endl;
	return 0;
}