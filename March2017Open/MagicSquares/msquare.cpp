/*
ID: kml111
PROG: msquare
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;


int main() {
	ofstream fout("msquare.out");
	ifstream fin("msquare.in");
	vector<int> target(8);
	for (int a = 0; a < 8; ++a) {
		int integer;
		fin >> integer;
		target[a] = integer;
	}
	
	vector<int> initial(8);
	for (int b = 0; b < 8; ++b) {
		initial[b] = b + 1;
	}

	queue<tuple<vector<int>, string>> exam;
	// Push first node in 
	exam.push(make_tuple(initial, ""));
	auto curr = exam.front();

	while (!(equal(target.begin(), target.begin() + 8, get<0>(curr).begin()) {
		auto curr = exam.front();
		exam.pop();

		int cur = get<0>(cur_tuple);
		int size = get<1>(cur_tuple);
		int highest = get<2>(cur_tuple);
		vector<int> &vitamincount = get<3>(cur_tuple);
		bool satisfies = true;
		for (int k = 0; k < v; ++k) {
			if (vitamincount[k] < vitamins[k]) {
				satisfies = false;
				break;
			}
		}
		if (satisfies) {
			fout << size;
			for (int i = 0; i < g; i++) {
				if ((cur & (1 << i)) != 0) {
					fout << ' ' << i + 1;
				}
			}
			fout << endl;
			break;
		}

		// Add a node to queue. 
		for (int i = highest + 1; i < g; ++i) {
			int next = (cur | (1 << i));
			vector<int> nextvitamin(vitamincount);
			for (int j = 0; j < v; j++)
			{
				nextvitamin[j] += feeds[i][j];
			}
			exam.push(make_tuple(next, size + 1, i, nextvitamin));
		}
	}

	return 0;
}