#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <limits>
#include <cmath>

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

void printMatrix(const vector<vector<double>> &matrix) {
	int n = (int)matrix.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (matrix[i][j] > numeric_limits<double>::max() / 20) {
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

void ponyExpress(int caseNumber) {
	int n, q;
	cin >> n >> q;
	vector<tuple<int, int>> horses(n); // distance and speed of all horses
	for (int b = 0; b < n; ++b) {
		int e, s;
		cin >> e >> s;
		horses[b] = make_tuple(e, s);
	}

	vector<vector<double>> shortestPath(n, vector<double>(n)); // distance between different cities
	for (int a = 0; a < n; ++a) {
		for (int b = 0; b < n; ++b) {
			double d;
			cin >> d;
			if (a == b) {
				shortestPath[a][b] = 0;
			}
			else {
				if (d == -1) {
					shortestPath[a][b] = numeric_limits<double>::max() / 10;
				}
				else {
					shortestPath[a][b] = d;
				}
			}
		}
	}

	vector<tuple<int, int>> citypairs(q); // cities I need to know the time between
	for (int c = 0; c < q; ++c) {
		int u, k;
		cin >> u >> k;
		citypairs[c] = make_tuple(u, k);
	}

	floydWarshall(shortestPath);

	vector<vector<double>> timeGraph(n, vector<double>(n)); // time it takes for horse to go to city
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == j) { // same city, takes no time
				timeGraph[i][j] = 0;
			}
			else {
				if (shortestPath[i][j] <= get<0>(horses[i])) { // horse can reach this place without tiring out along the way
					timeGraph[i][j] = (double)shortestPath[i][j] / get<1>(horses[i]); // it takes distance/speed time 
				}
				else {
					timeGraph[i][j] = numeric_limits<double>::max() / 10;
				}
			}
		}
	}

	floydWarshall(timeGraph);

	cout << "Case #" << caseNumber << ":";
	cout.precision(10);
	for (int x = 0; x < q; ++x) {
		cout << ' ' << fixed << timeGraph[get<0>(citypairs[x]) - 1][get<1>(citypairs[x]) - 1];
	}

	cout << endl;
}

int main() {
	int t;
	cin >> t;
	
	for (int a = 1; a <= t; ++a) { // for every test case
		ponyExpress(a);
	}

	return 0;
}