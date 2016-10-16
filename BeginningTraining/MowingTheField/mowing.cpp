#include <unordered_map>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

//int mowing(int steps, unordered_map<int, int> record) {
//	for (int m = 0; m < steps; ++m) {
//
//	}
//}

int main() {
	ofstream fout("mowing.out");
	ifstream fin("mowing.in");
	int n;
	fin >> n;

	unordered_map<int, int> record;
	int currx = 1000;
	int curry = 1000;
	int start = (currx * 10000) + curry;
	record[start] = 0;

	int time = 1;

	int steps = 0;

	int least = numeric_limits<int>::max();

	for (int i = 0; i < n; ++i) {
		char d;
		int s;
		fin >> d >> s;
		steps += s;

		for (int j = 0; j < s; ++j) {
			int coord;
			if (d == 'N') {
				curry += 1;
			}
			else if (d == 'S') {
				curry -= 1;
			}
			else if (d == 'E') {
				currx += 1;
			}
			else if (d == 'W') {
				currx -= 1;
			}

			coord = (currx * 10000) + curry;
			auto pnt = record.find(coord);
			if (pnt == record.end()) {
				// Not find
				record[coord] = time;
			}
			else {
				int gap = time - pnt->second;
				cout << currx << " " << curry << " " << gap << endl;
				if (gap < least) {
					least = gap;
				}
				record[coord] = time;
			}
			time += 1;
		}
	}

	if (least == numeric_limits<int>::max()) {
		least = -1;
	}

	fout << least << endl;
	return 0;
}