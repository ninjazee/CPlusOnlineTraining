/*
ID: kml111
PROG: butter
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

void printMatrix(const vector<vector<int>> &matrix) {
	int n = (int)matrix.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (matrix[i][j] > numeric_limits<int>::max() / 20) {
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

void floydWarshall(vector<vector<int>> &matrix) {
	int p = (int)matrix.size();
	for (int k = 0; k < p; ++k) {
		//printMatrix(matrix);
		for (int i = 0; i < p; ++i) {
			for (int j = 0; j < p; ++j) {
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
			}
		}
	}
	//printMatrix(matrix);
}

int main() {
	ofstream fout("butter.out");
	ifstream fin("butter.in");
	int n, p, c;
	fin >> n >> p >> c;
	vector<int> cows(p, 0);
	for (int a = 0; a < n; ++a) {
		int cowPasture;
		fin >> cowPasture;
		cows[cowPasture - 1] += 1;
	}
	vector<vector<int>> matrix(p, vector<int>(p, numeric_limits<int>::max() / 10));
	for (int b = 0; b < c; ++b) {
		int p1, p2, length;
		fin >> p1 >> p2 >> length;
		matrix[p1 - 1][p2 - 1] = length;
		matrix[p2 - 1][p1 - 1] = length;
	}

	for (int d = 0; d < p; ++d) {
		matrix[d][d] = 0;
	}

	floydWarshall(matrix);

	int best = numeric_limits<int>::max();
	for (int i = 0; i < p; ++i) { // for each pasture which could have the sugar cube
		int count = 0;
		for (int j = 0; j < p; ++j) { // for every pasture
			count += matrix[i][j] * cows[j];
		}

		if (count < best) {
			best = count;
		}
	}

	fout << best << endl;
	return 0;
}