/*
ID: kml111
PROG: nocows
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int pedigrees(const int n, const int k) {
	switch (k) {
	case 0:
		return 0;
	case 1:
		return (n != 1 ? 0 : 1);
	default:
		int total = 0;
		//cout << "Calculating " << n << ' ' << k << endl;
		for (int i = 1; i < n; ++i) {
			// calculate the left side of the equation
			int left = pedigrees(i, k - 1);
			int ladd = 0;
			for (int j = 1; j < k; ++j) {
				ladd += pedigrees(n - 1 - i, j);
			}
			left = left * ladd;

			// calculate the right side of the equation
			int right = pedigrees(n - 1 - i, k - 1);
			int radd = 0;
			for (int l = 1; l < k - 1; ++l) {
				radd += pedigrees(i, l);
			}
			right = right * radd;

			// add them together
			total += (left + right);
		}
		//cout << n << ' ' << k << ' ' << total << endl;
		return total;
	}
}

int pedigrees2(const int n, const int k, vector<vector<int>> &graph) {
	switch (k) {
	case 0:
		return 0;
	case 1:
		return (n != 1 ? 0 : 1);
	default:
		if (graph[k][n] != -1) {
			return graph[k][n];
		}
		int total = 0;
		//cout << "Calculating " << n << ' ' << k << endl;
		for (int i = 1; i < n; ++i) {
			// calculate the left side of the equation
			int left = pedigrees2(i, k - 1, graph);
			int ladd = 0;
			for (int j = 1; j < k; ++j) {
				ladd += pedigrees2(n - 1 - i, j, graph);
			}
			ladd %= 9901;
			left = left * ladd;

			// calculate the right side of the equation
			int right = pedigrees2(n - 1 - i, k - 1, graph);
			int radd = 0;
			for (int l = 1; l < k - 1; ++l) {
				radd += pedigrees2(i, l, graph);
			}
			radd %= 9901;
			right = right * radd;

			// add them together
			total += (left + right);
			total %= 9901;
		}
		//cout << n << ' ' << k << ' ' << total << endl;
		graph[k][n] = total % 9901;
		return total % 9901;
	}
}


int main2() {
	ofstream fout("nocows.out");
	ifstream fin("nocows.in");
	int n, k;
	fin >> n >> k;
	vector<vector<int>> graph(k + 1, vector<int>(n + 1, -1));
	fout << pedigrees2(n, k, graph) << endl;
	return 0;
}

int main() {
	ofstream fout("nocows.out");
	ifstream fin("nocows.in");
	int N, K;
	fin >> N >> K;
	vector<vector<int>> graph(K + 1, vector<int>(N + 1, 0));
	graph[1][1] = 1;

	for (int k = 2; k <= K; ++k) {
		for (int n = 0; n <= N; ++n) {
			int total = 0;
			//cout << "Calculating " << n << ' ' << k << endl;
			for (int i = 1; i < n; ++i) {
				// calculate the left side of the equation
				int left = graph[k - 1][i];
				int ladd = 0;
				for (int j = 1; j < k; ++j) {
					ladd += graph[j][n - 1 - i];
				}
				ladd %= 9901;
				left = left * ladd;

				// calculate the right side of the equation
				int right = graph[k - 1][n - 1 - i];
				int radd = 0;
				for (int l = 1; l < k - 1; ++l) {
					radd += graph[l][i];
				}
				radd %= 9901;
				right = right * radd;

				// add them together
				total += (left + right);
				total %= 9901;
			}
			//cout << n << ' ' << k << ' ' << total << endl;
			graph[k][n] = total % 9901;
		}
	}

	fout << graph[K][N] << endl;
	return 0;
}