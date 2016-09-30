#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int speedingTicket(const vector<int> &seg, const vector<int> &speed, const vector<int> &bSeg, const vector<int> &bSpeed) {
	int count = 0;
	int bCount = 0;
	int m = (int)bSpeed.size();
	while (m > 0) {
		if (seg[count] >= bSpeed[bCount]) {

		}
	}
}

int main() {
	ofstream fout("speeding.out");
	ifstream fin("speeding.in");
	int n, m;
	fin >> n >> m;
	vector<int> segments(n);
	vector<int> speedLimits(n);
	for (int a = 0; a < n; ++a) {
		int s, l;
		fin >> s >> l;
		segments[a] = s;
		speedLimits[a] = l;
	}
	vector<int> bSegments(m);
	vector<int> bSpeed(m);
	for (int b = 0; b < m; ++b) {
		int c, d;
		fin >> c >> d;
		bSegments[b] = c;
		bSpeed[b] = d;
	}
	fout << speedingTicket(segments, speedLimits, bSegments, bSpeed) << endl;
	return 0;
}