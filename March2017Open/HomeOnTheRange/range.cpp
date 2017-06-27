/*
ID: kml111
PROG: range
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void printGrid(const vector<vector<int>> &grid) {
	int n = (int)grid.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << grid[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl << "-----------------------------------------" << endl;
}

int main() {
	ofstream fout("range.out");
	ifstream fin("range.in");
	int n;
	fin >> n;
	vector<vector<bool>> ravagedReady(n, vector<bool>(n));
	for (int a = 0; a < n; ++a) {
		for (int b = 0; b < n; ++b) {
			char square;
			fin >> square;
			if (square == '1') { // it is ready for eating
				ravagedReady[a][b] = true;
			}
			else { // it is ravaged
				ravagedReady[a][b] = false;
			}
		}
	}

	vector<vector<int>> horizontal(n, vector<int>(n));
	for (int i = n - 1; i >= 0; --i) {
		for (int j = 0; j < n; ++j) {
			if (ravagedReady[j][i] == false) { // this square is ravaged
				horizontal[j][i] = 0;
			}
			else if (i == n - 1) { // this square is on the edge
				horizontal[j][i] = 1; 
			}
			else {
				horizontal[j][i] = horizontal[j][i + 1] + 1;
			}
		}
	}

	//printGrid(horizontal);

	/*
	vector<vector<int>> squares(n, vector<int>(n));
	for (int i = n - 1; i >= 0; --i) {
		for (int j = 0; j < n; ++j) {
			if (ravagedReady[i][j] == false) { // this square is ravaged
				squares[i][j] = 0;
			}
			else if (i == n - 1) { // this square is on the edge
				squares[i][j] = 1;
			}
			else {
				int countDown = 1;
				vector<int> hist(n+1);
				while (i + countDown <= n - 1 && countDown < horizontal[i][j] && horizontal[i + countDown][j] >= countDown + 1) {
					countDown += 1;
				}
				squares[i][j] = countDown;
			}
		}
	}

	*/
	vector<int> numValues(n + 1);
	vector<vector<int>> vertical(n, vector<int>(n, 0));
	vector<vector<int>> histRecord(n, vector<int>(n + 1));
	for (int i = n - 1; i >= 0; --i) { // row		
		for (int j = n - 1; j >= 0; --j) { 
			for (int k = 0; k <= n; ++k) {
				if (k <= horizontal[i][j]) {
					histRecord[j][k] += 1;
				}
				else {
					histRecord[j][k] = 0;
				}
			}
			for (int m = 0; m <= n; ++m) {
				if (histRecord[j][m] >= m) { // there is a this size square
											 // add it to the values
					numValues[m] += 1;
					vertical[i][j] = m; 
				}
				else
				{
					break;
				}
			}

		}

	}
	//printGrid(vertical);

	//printGrid(squares);

	for (int i = 2; i < n + 1; ++i) {
		if (numValues[i] >= 1) {
			fout << i << " " << numValues[i] << endl;
		}
	}
	return 0;
}