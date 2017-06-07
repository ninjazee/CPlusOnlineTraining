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
#include <unordered_set>

using namespace std;

int code(const vector<int> &v) {
	return v[0] * 10000000 + v[1] * 1000000 + v[2] * 100000 + v[3] * 10000 + v[4] * 1000 + v[5] * 100 + v[6] * 10 + v[7];
}

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
	unordered_set<int> seen;
	// Push first node in 
	exam.push(make_tuple(initial, ""));
	auto cur_tuple = exam.front();
	seen.insert(code(initial));

	while (!(equal(target.begin(), target.begin() + 8, get<0>(cur_tuple).begin()))) {
		cur_tuple = exam.front();
		exam.pop();

		vector<int> curr = get<0>(cur_tuple);
		string sequence = get<1>(cur_tuple);

		// Add next nodes to queue. 
		// Transformation A
		vector<int> nexta(8);
		for (int i = 0; i < 8; ++i) {
			nexta[i] = curr[-1 * i + 7];
		}
		int ca = code(nexta);
		auto ita = seen.find(ca);
		if (ita == seen.end()) { // we have not already seen this
			exam.push(make_tuple(nexta, sequence + 'A'));
			seen.insert(ca);
		}
		// Transformation B
		vector<int> nextb(8);
		for (int i = 0; i < 8; ++i) {
			if (i == 0) { // switch with 4 place
				nextb[i] = curr[3];
			}
			else if (i >= 1 && i <= 3) { // 2nd to 4th place, use the one behind it
				nextb[i] = curr[i - 1];
			}
			else if (i >= 4 && i <= 6) { // 5th to 7th place, use the one in front of it
				nextb[i] = curr[i + 1];
			}
			else if (i == 7) { // switch with 5th place
				nextb[i] = curr[4];
			}
		}
		int cb = code(nextb);
		auto itb = seen.find(cb);
		if (itb == seen.end()) { // we have not already seen this
			exam.push(make_tuple(nextb, sequence + 'B'));
			seen.insert(cb);
		}
		// Transformation C
		vector<int> nextc(8);
		for (int i = 0; i < 8; ++i) {
			if (i == 1) { // switch with 7 place
				nextc[i] = curr[6];
			}
			else if (i == 2) { // switch with 2 place
				nextc[i] = curr[1];
			}
			else if (i == 5) { // switch with 3 place
				nextc[i] = curr[2];
			}
			else if (i == 6) { // switch with 6 place
				nextc[i] = curr[5];
			}
			else { // normal
				nextc[i] = curr[i];
			}
		}
		int cc = code(nextc);
		auto itc = seen.find(cc);
		if (itc == seen.end()) { // we have not already seen this
			exam.push(make_tuple(nextc, sequence + 'C'));
			seen.insert(cc);
		}
	}

	fout << (int)get<1>(cur_tuple).length() << endl << get<1>(cur_tuple) << endl;
	return 0;
}