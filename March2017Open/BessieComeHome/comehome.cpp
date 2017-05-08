/*
ID: kml111
PROG: comehome
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

int code(const char c) {
	if (c >= 'a' && c <= 'z') { // c is lowercase
		return c - 'a';
	}
	else { // c is uppercase
		return c - 'A' + 26;
	}
}

void printMatrix(const vector<vector<int>> &matrix, const vector<bool> &pastures) {
	int n = (int)matrix.size();
	for (int i = 0; i < n; ++i) {
		if (pastures[i]) {
			for (int j = 0; j < n; ++j) {
				if (pastures[j]) {
					if (matrix[i][j] > numeric_limits<int>::max() / 20) {
						cout << "inf\t";
					}
					else {
						cout << matrix[i][j] << "\t";
					}
				}
			}
			cout << endl;
		}
	}
	cout << "---------------------------------------" << endl;
}

void floydWarshall(vector<vector<int>> &matrix, const vector<bool> &pastures) {
	int n = (int)matrix.size();
	for (int k = 0; k < n; ++k) {
		//printMatrix(matrix, pastures);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
			}
		}
	}
	//printMatrix(matrix, pastures);
}

int main() {
	ofstream fout("comehome.out");
	ifstream fin("comehome.in");
	int p;
	fin >> p;
	vector<bool> pastures(52);
	vector<vector<int>> matrix(52, vector<int>(52, numeric_limits<int>::max()/10));
	for (int a = 0; a < p; ++a) {
		char c1, c2;
		fin >> c1 >> c2;
		
		int dist;
		fin >> dist;

		int code1 = code(c1);
		int code2 = code(c2);
		dist = min(dist, matrix[code1][code2]);
		matrix[code1][code2] = dist;
		matrix[code2][code1] = dist;
		pastures[code(c1)] = true;
		pastures[code(c2)] = true;
	}
	
	for (int x = 0; x < 52; ++x) {
		matrix[x][x] = 0;
	}

	floydWarshall(matrix, pastures);

	char bestc = 0;
	int bestd = numeric_limits<int>::max();
	for (int b = 0; b < 25; ++b) { // for all capital letters
		if (pastures[26 + b]) { // there is a pasture with a cow in it
			if (matrix[26 + b]['Z' - 'A' + 26] < bestd) {
				bestd = matrix[26 + b]['Z' - 'A' + 26];
				bestc = 'A' + b;
			}
		}
	}

	fout << bestc << " " << bestd << endl;
	return 0;
}