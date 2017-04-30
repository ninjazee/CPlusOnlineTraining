/*
ID: kml111
PROG: cowtour
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;

void printMatrix(const vector<vector<double>> &matrix) {
	int n = (int)matrix.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (matrix[i][j] > numeric_limits<double>::max()/20) {
				cout << "inf\t";
			}
			else {
				cout << matrix[i][j] << "\t";
			}
		}
		cout << endl;
	}
	cout << "---------------------------------------" << endl;
}

void floydWarshall(vector<vector<double>> &matrix) {
	int n = (int)matrix.size();
	for (int k = 0; k < n; ++k) {
		//printMatrix(matrix);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
			}
		}
	}
	//printMatrix(matrix);
}

int main() {
	ofstream fout("cowtour.out");
	ifstream fin("cowtour.in");
	int n;
	fin >> n;
	vector<tuple<int, int>> pastures(n);
	for (int a = 0; a < n; ++a) {
		int x, y;
		fin >> x >> y;
		pastures[a] = make_tuple(x, y);
	}
	vector<vector<int>> connectivity(n, vector<int>(n));
	for (int b = 0; b < n; ++b) {
		string row;
		fin >> row;
		for (int c = 0; c < n; ++c) {
			connectivity[b][c] = row[c] - '0';
		}
	}

	vector<vector<double>> matrix(n, vector<double>(n, numeric_limits<double>::max()/10));
	for (int d = 0; d < n; ++d) {
		for (int e = 0; e < n; ++e) {
			if (connectivity[d][e] == 1) {
				int dx = get<0>(pastures[d]) - get<0>(pastures[e]);
				int dy = get<1>(pastures[d]) - get<1>(pastures[e]);
				matrix[d][e] = sqrt(dx * dx + dy * dy);
			}
			else if (d == e) {
				matrix[d][e] = 0;
			}
		}
	}

	floydWarshall(matrix);
	
	// calculate biggest diameter in old field
	double olddiam = 0;
	for (int g = 0; g < n; ++g) {
		for (int h = 0; h < n; ++h) {
			if (matrix[g][h] < numeric_limits<double>::max() / 20 && matrix[g][h] > olddiam) {
				olddiam = matrix[g][h];
			}
		}
	}

	double newdiam = numeric_limits<double>::max();
	// for every connection
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (matrix[i][j] > numeric_limits<double>::max() / 20) { // no connection
				// connect these two pastures
				// find farthest away pasture from pasture i, find farthest away pasture from pasture j, add distance of i to j
				int distx = get<0>(pastures[i]) - get<0>(pastures[j]);
				int disty = get<1>(pastures[i]) - get<1>(pastures[j]);
				double distij = sqrt(distx * distx + disty * disty); // distance of pasture i to pasture j

				double farthesti = 0;
				for (int x = 0; x < n; ++x) {
					if (matrix[i][x] < numeric_limits<double>::max()/20 && matrix[i][x] > farthesti) {
						farthesti = matrix[i][x];
					}
				}

				double farthestj = 0;
				for (int y = 0; y < n; ++y) {
					if (matrix[j][y] < numeric_limits<double>::max() / 20 && matrix[j][y] > farthestj) {
						farthestj = matrix[j][y];
					}
				}

				double totalDist = distij + farthesti + farthestj;
				if (totalDist < newdiam) {
					newdiam = totalDist;
				}
			}
		}
	}

	double best = max(newdiam, olddiam);

	fout.precision(6);
	fout << fixed << best << endl;
	return 0;
}