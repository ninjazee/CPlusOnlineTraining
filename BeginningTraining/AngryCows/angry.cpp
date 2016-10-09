#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int hayBales(int n, vector<int> &bales) {
	sort(bales.begin(), bales.end());
	int highest = 0;
	int nOB = n - 1;
	for (int i = 0; i < n; ++i) {
		int ltime = 1;
		int rtime = 1;
		int left = i;
		int right = i;
		bool lExploding = true;
		bool rExploding = true;
		while (lExploding) {
			if (left < 0) {
				left = 0;
				lExploding = false;
			}
			else {
				int leftBound = bales[left] - ltime;
				lExploding = false;
				while (left > 0 && bales[left - 1] >= leftBound) {
					left -= 1;
					lExploding = true;
				}
				ltime += 1;
			}
		}
		while (rExploding) {
			if (right > nOB) {
				right = nOB;
				rExploding = false;
			}
			else {
				int rightBound = bales[right] + rtime;
				rExploding = false;
				while (right < nOB && bales[right + 1] <= rightBound) {
					right += 1;
					rExploding = true;
				}
				rtime += 1;
			}
		}
		int c = (right - left) + 1;
		
		if (c > highest) {
			highest = c;
		}
	}
	return highest;
}

int main() {
	ofstream fout("angry.out");
	ifstream fin("angry.in");
	int n;
	fin >> n;
	vector<int> bales(n);
	for (int b = 0; b < n; ++b) {
		int h;
		fin >> h;
		bales[b] = h;
	}
	fout << hayBales(n, bales) << endl;
	return 0;
}