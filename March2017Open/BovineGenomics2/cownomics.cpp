#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

int bovineGenomics(const int m, const vector<string> &scows, const vector<string> &pcows) {
	int n = (int)scows.size();
	int total = 0;
	for (int i = 0; i < m; ++i) {
		for (int j = i + 1; j < m; ++j) {
			for (int k = j + 1; k < m; ++k) {
				bool isGenome = true;

				for (int a = 0; a < n; ++a) {
					for (int b = 0; b < n; ++b) {
						if (scows[a][i] == pcows[b][i] && scows[a][j] == pcows[b][j] && scows[a][k] == pcows[b][k]) {
							isGenome = false;
						}
					}
				}

				if (isGenome == true) {
					total += 1;
				}
			}
		}
	}
	return total;
}

int main() {
	ofstream fout("cownomics.out");
	ifstream fin("cownomics.in");
	int n, m;
	fin >> n >> m;

	vector<string> scows(n);
	vector<string> pcows(n);
	for (int a = 0; a < n; ++a) {
		string sc;
		fin >> sc;
		scows[a] = sc;
	}
	for (int b = 0; b < n; ++b) {
		string pc;
		fin >> pc;
		pcows[b] = pc;
	}

	fout << bovineGenomics(m, scows, pcows) << endl;
	return 0;
}