/*
ID: kml111
PROG: skidesign
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int skiCourseDesign(vector<int> &hills) {
	int n = (int)hills.size();

	sort(hills.begin(), hills.end());

	if (hills[n - 1] - hills[0] <= 17) { // check if distance is already less than 17
		// no changes need to be made
		return 0;
	}
	else { // distance is larger than 17
		int best = 2147483647;

		for (int i = 0; i < (hills[n - 1] - 17); ++i) { // test each possible placing of 17
			int count = 0;
			for (int j = 0; j < n; ++j) { // for each hill
				if (hills[j] < i) { // on the left side of the placing
									// add the amount of money it costs to raise the hill (difference^2)
					count += (i - hills[j]) * (i - hills[j]);
				}
				else if (hills[j] > (i + 17)) { // on the right side of the placing
												// add the amount of money it costs to lower the hill (difference^2)
					count += (hills[j] - (i + 17)) * (hills[j] - (i + 17));
				}
				// else do nothing because it is already in bounds and does not need changing
			}

			if (count < best) {
				best = count;
			}
		}

		return best;
	}
}

int main() {
	ofstream fout("skidesign.out");
	ifstream fin("skidesign.in");
	int n;
	fin >> n;
	vector<int> hills(n);
	for (int x = 0; x < n; ++x) {
		int hill;
		fin >> hill;
		hills[x] = hill;
	}

	fout << skiCourseDesign(hills) << endl;
	return 0;
}