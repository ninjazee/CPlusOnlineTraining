#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int numTiles(const vector<string> &figure) {
	int n = (int)figure.size();
	int count = 0;
	for (int a = 0; a < n; ++a) {
		for (int b = 0; b < n; ++b) {
			if (figure[a][b] == '#') {
				count += 1;
			}
		}
	}
	return count;
}

void numSame(const vector<string> &originalFig, const vector<vector<string>> &pieces, tuple<int, int> &samesize) {
	int originalSize = numTiles(originalFig);
	vector<int> pieceSizes(k);
	for (int z = 0; z < k; ++z) {
		int size = numTiles(pieces[z]);
		pieceSizes[z] = size;
	}

	for (int y = 0; y < k - 1; ++y) {
		for (int x = y + 1; x < k; ++x) {
			if (pieceSizes[x] + pieceSizes[y] == originalSize) {
				fout << y + 1 << ' ' << x + 1 << endl;
				return 0;
			}
		}
	}
}

void boundingBox(const vector<string> &figure, int &farthestRight, int &farthestLeft, int &farthestUp, int &farthestDown) {
	int n = (int)figure.size();
	farthestRight = 0;
	farthestLeft = n-1;
	farthestUp = n-1;
	farthestDown = 0;
	for (int a = 0; a < n; ++a) {
		for (int b = 0; b < n; ++b) {
			if (figure[a][b] == '#') {
				if (a > farthestDown) {
					farthestDown = a;
				}
				if (b > farthestRight) {
					farthestRight = b;
				}
				if (a < farthestUp) {
					farthestUp = a;
				}
				if (b < farthestLeft) {
					farthestLeft = b;
				}
			}
		}
	}
}

int main() {
	ofstream fout("bcs.out");
	ifstream fin("bcs.in");
	int n, k;
	fin >> n >> k;
	vector<string> originalFig(n);
	for (int i = 0; i < n; ++i) {
		string line;
		fin >> line;
		originalFig[i] = line;
	}
	vector<vector<string>> pieces(k);
	for (int j = 0; j < k; ++j) {
		vector<string> piece(n);
		for (int h = 0; h < n; ++h) {
			string line;
			fin >> line;
			piece[h] = line;
		}
		pieces[j] = piece;
	}
	int originalSize = numTiles(originalFig);
	vector<int> pieceSizes(k);
	for (int z = 0; z < k; ++z) {
		int size = numTiles(pieces[z]);
		pieceSizes[z] = size;
	}

	for (int y = 0; y < k-1; ++y) {
		for (int x = y+1; x < k; ++x) {
			if (pieceSizes[x] + pieceSizes[y] == originalSize) {
				fout << y+1 << ' ' << x+1 << endl;
				return 0;
			}
		}
	}

	
}