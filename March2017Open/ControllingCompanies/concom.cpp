/*
ID: kml111
PROG: concom
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void controllingCompanies(const vector<vector<int>> &percents, vector<vector<bool>> &ownings, const int i) {
	int n = (int)percents.size();
	for (int j = 0; j < n; ++j) {
		if (i != j) {
			if (percents[i][j] > 50) { // this company directly owns this company
				ownings[i][j] = true;
				/*
				int t = 0;
				for (int k = 0; k < n; ++k) { // for every company that company owns
					// repeat the process
					controllingCompanies(percents, ownings, j, k, acti, t);
				}
				if (t > 50) {
					ownings[acti][j] = true;
				}
				*/
			}
			else {
				int total = 0;
				for (int k = 0; k < 100; ++k) { // for every company that owns a part of this company
					if (percents[i][k] > 50) { // if we own this company
						total += percents[k][j];
					}
				}
				if (total > 50) {
					ownings[i][j] = true;
				}
			}
		}
	}
	
}

int main() {
	ofstream fout("concom.out");
	ifstream fin("concom.in");
	int n;
	fin >> n;
	vector<vector<int>> percents(n, vector<int>(n));
	for (int a = 0; a < n; ++a) {
		int i, j, p;
		fin >> i >> j >> p;
		percents[i - 1][j - 1] = p;
	}

	for (int b = 0; b < n; ++b) {
		percents[b][b] = 100;
	}

	vector<vector<bool>> ownings(n, vector<bool>(n, false));
	for (int i = 0; i < n; ++i) { // for every company owning another comapny
		for (int j = 0; j < n; ++j) { // for every company owned
			if (percents[i][j] > 50) { // this company directly owns this company
				ownings[i][j] = true;
				if (i != j) {
					fout << i + 1 << ' ' << j + 1 << endl;
				}
			}
			else { // this company does not directly own this company
				int total = 0;
				for (int k = 0; k < n; ++k) { // for every company that owns a part of this company
					if (j != k && percents[i][k] > 50) {
						total += percents[k][j];
					}
				}
				if (total > 50) {
					ownings[i][j] = true;
					fout << i + 1 << ' ' << j + 1 << endl;
				}
			}
			/*
			if (i == j) {
				ownings[i][j] = true;
			}
			else {
				int total = 0;
				controllingCompanies(percents, ownings, i, j, i, total);
			}
			*/
		}
	}
	/*
	for (int x = 0; x < 100; ++x) {
		for (int y = 0; y < 100; ++y) {
			if (x != y) {
				if (ownings[x][y]) {
					cout << x + 1 << ' ' << y + 1 << endl;
				}
			}
		}
	}
	*/
	return 0;
}