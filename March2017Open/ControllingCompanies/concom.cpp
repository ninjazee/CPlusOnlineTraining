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
	vector<vector<int>> percents(100, vector<int>(100));
	for (int a = 0; a < n; ++a) {
		int i, j, p;
		fin >> i >> j >> p;
		percents[i - 1][j - 1] = p;
	}

	for (int b = 0; b < 100; ++b) {
		percents[b][b] = 100;
	}

	vector<vector<bool>> ownings(100, vector<bool>(100, false));
	for (int i = 0; i < 100; ++i) { // for every company owning another comapny
		for (int j = 0; j < 100; ++j) { // for every company owned
			if (percents[i][j] > 50) { // this company directly owns this company
				ownings[i][j] = true;
				/*
				if (i != j) {
					fout << i + 1 << ' ' << j + 1 << endl;
				}
				*/
			}
			
		}
	}
	
	bool bChange = true;
	while (bChange) {
		bChange = false;
		for (int i = 0; i < 100; ++i) { // for every company owning another comapny
			for (int j = 0; j < 100; ++j) { // for every company owned
				if (!ownings[i][j]) { // this company does not directly own this company
					int total = 0;
					for (int k = 0; k < 100; ++k) { // for every company that owns a part of this company
						if (j != k && ownings[i][k]) {
							total += percents[k][j];
						}
					}
					if (total > 50) {
						ownings[i][j] = true;
						bChange = true;
						//fout << i + 1 << ' ' << j + 1 << endl;
					}
				}
			}
		}
	}
	
	for (int x = 0; x < 100; ++x) {
		for (int y = 0; y < 100; ++y) {
			if (ownings[x][y] && x != y) {
				fout << x + 1 << ' ' << y + 1 << endl;
			}
		}
	}
	return 0;
}