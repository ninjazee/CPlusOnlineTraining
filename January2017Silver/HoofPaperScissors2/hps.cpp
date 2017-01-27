#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int hps(vector<int> fgestures) {
	int n = (int)fgestures.size();
	int best = 0;
	vector<vector<int>> record(n, vector<int>(3));
	for (int a = 0; a < n; ++a) {
		if (a > 0) {
			record[a][0] = record[a - 1][0];
			record[a][1] = record[a - 1][1];
			record[a][2] = record[a - 1][2];
		}
		record[a][fgestures[a]] += 1;
	}

	for (int i = 0; i < 3; ++i) {
		int wins = 0;
		char cgesture = i;
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < 3; ++k) {
				int winfront = record[j][(i + 2) % 3];
				int winback = record[n - 1][(k + 2) % 3] - record[j][(k + 2) % 3];
				wins = winfront + winback;
				if (wins > best) {
					best = wins;
				}
			}
		}
	}
	return best;
}

int main() {
	ofstream fout("hps.out");
	ifstream fin("hps.in");
	int n;
	fin >> n;
	vector<int> fgestures(n);
	for (int x = 0; x < n; ++x) {
		char gesture;
		fin >> gesture;
		int y;
		if (gesture == 'H') {
			y = 0;
		}
		else if (gesture == 'P') {
			y = 1;
		}
		else {
			y = 2;
		}
		fgestures[x] = y;
	}
	fout << hps(fgestures) << endl;
	return 0;
}