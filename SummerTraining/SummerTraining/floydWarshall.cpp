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